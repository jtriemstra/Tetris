#include "game.cpp"
#include "constants.h"
// Credit: https://wp.josh.com/2014/05/13/ws2812-neopixels-are-not-so-finicky-once-you-get-to-know-them/
// These values depend on which pins your 8 strings are connected to and what board you are using 
// More info on how to find these at http://www.arduino.cc/en/Reference/PortManipulation

// PORTD controls Digital Pins 0-7 on the Uno

// You'll need to look up the port/bit combination for other boards. 

// Note that you could also include the DigitalWriteFast header file to not need to to this lookup.

#define PIXEL_PORT  PORTD  // Port of the pin the pixels are connected to
#define PIXEL_PORT2  PORTB  // Port of the pin the pixels are connected to
#define PIXEL_DDR   DDRD   // Port of the pin the pixels are connected to
#define PIXEL_DDR2   DDRB

// These are the timing constraints taken mostly from the WS2812 datasheets 
// These are chosen to be conservative and avoid problems rather than for maximum throughput 

#define T1H  900    // Width of a 1 bit in ns
#define T1L  600    // Width of a 1 bit in ns

#define T0H  400    // Width of a 0 bit in ns
#define T0L  900    // Width of a 0 bit in ns

#define RES 6000    // Width of the low gap between bits to cause a frame to latch

// Here are some convience defines for using nanoseconds specs to generate actual CPU delays

#define NS_PER_SEC (1000000000L)          // Note that this has to be SIGNED since we want to be able to check for negative values of derivatives

#define CYCLES_PER_SEC (F_CPU)

#define NS_PER_CYCLE ( NS_PER_SEC / CYCLES_PER_SEC )

#define NS_TO_CYCLES(n) ( (n) / NS_PER_CYCLE )

const byte PIN_LATCH = A0;
const byte PIN_CLOCK = A2;
const byte PIN_DATA = A1;

const byte BYTES_PER_ROW = 2;
const byte BITS_PER_COLOR = 24;

bool m_blnIsPlaying = false;
bool m_blnIsWaitAscending = true;

Game* m_objGame;

// Actually send the next set of 8 WS2812B encoded bits to the 8 pins.
// We must to drop to asm to enusre that the complier does
// not reorder things and make it so the delay happens in the wrong place.

static inline __attribute__ ((always_inline)) void sendBitX8( uint8_t bits, uint8_t bits2 ) {

    const uint8_t onBits = 0xff;          // We need to send all bits on on all pins as the first 1/3 of the encoded bits
            
    asm volatile (
      
      "out %[port1], %[onBits] \n\t"           // 1st step - send T0H high 
      "out %[port2], %[onBits] \n\t"
      
      ".rept %[T0HCycles] \n\t"               // Execute NOPs to delay exactly the specified number of cycles
        "nop \n\t"
      ".endr \n\t"
      
      "out %[port1], %[bits] \n\t"             // set the output bits to thier values for T0H-T1H
      "out %[port2], %[bits2] \n\t"
      ".rept %[dataCycles] \n\t"               // Execute NOPs to delay exactly the specified number of cycles
      "nop \n\t"
      ".endr \n\t"
      
      "out %[port1],__zero_reg__  \n\t"        // last step - T1L all bits low
      "out %[port2],__zero_reg__  \n\t"
      
      // Don't need an explicit delay here since the overhead that follows will always be long enough
    
      ::
      [port1]    "I" (_SFR_IO_ADDR(PIXEL_PORT)),
      [port2]    "I" (_SFR_IO_ADDR(PIXEL_PORT2)),
      [bits]   "d" (bits),
      [bits2]   "d" (bits2),
      [onBits]   "d" (onBits),
      
      [T0HCycles]  "I" (NS_TO_CYCLES(T0H) - 3),           // 1-bit width less overhead  for the actual bit setting, note that this delay could be longer and everything would still work
      
      [dataCycles]   "I" (NS_TO_CYCLES((T1H-T0H)) - 3)     // Minimum interbit delay. Note that we probably don't need this at all since the loop overhead will be enough, but here for correctness

    );
                                  

    // Note that the inter-bit gap can be as long as you want as long as it doesn't exceed the reset timeout (which is A long time)
    
}  

static inline void __attribute__ ((always_inline)) sendWhiteRow( uint8_t row ) {
  uint8_t bit=24;       

  while (bit--) {
      sendBitX8( row, row );
  }
}
    
static inline void __attribute__ ((always_inline)) sendGreenRow( uint8_t row ) {
  uint8_t bit=24;       

  while (bit--) {
      if (bit > 16) sendBitX8( row, row );
      else sendBitX8(0b00000000, 0b00000000) ;
  }
}

static inline void __attribute__ ((always_inline)) sendRedRow( uint8_t row ) {
  uint8_t bit=24;       

  while (bit--) {
      if (bit <= 16 && bit > 8) sendBitX8( row, row );
      else sendBitX8(0b00000000, 0b00000000) ;
  }
}

static inline void __attribute__ ((always_inline)) sendBlueRow( uint8_t row ) {
  uint8_t bit=24;       

  while (bit--) {
      if (bit <= 8) sendBitX8( row, row );
      else sendBitX8(0b00000000, 0b00000000) ;
  }
}

// Just wait long enough without sending any bits to cause the pixels to latch and display the last sent frame
void show() {
  _delay_us( (RES / 1000UL) + 1);       // Round up since the delay must be _at_least_ this long (too short might not work, too long not a problem)
}

void clearAll(){
  cli();                        // No time for interruptions!
  for (int i=0; i<STRING_LENGTH; i++) sendWhiteRow(0b00000000);
  sei();
  show();
}

void decodeTetrisColor(uint8_t color, uint8_t &red, uint8_t &green, uint8_t &blue){
  switch(color){
    case 0:
      red = 0;       green = 0;       blue = 0;      break;
     case 1:
     case 5:
      red = 15;      green = 0;       blue = 0;      break;
     case 2:
      red = 0;       green = 15;      blue = 0;      break;
     case 3:
      red = 0;       green = 0;       blue = 15;      break;
     case 4:
      red = 15;      green = 15;      blue = 0;      break;
     case 6:
      red = 15;      green = 0;       blue = 15;      break;
     case 7:
      red = 0;       green = 15;      blue = 15;      break;
     case 8:
      red = 15;      green = 15;      blue = 15;      break;
  }
}

/// convert an array with one byte per pixel to what amounts to an array of bits to send to LED strips
/// codedColors: the input - each byte is the color of a pixel in the row
/// output: the bits to stream to the entire set of strips. each call to this function modifies a subset of the array. the first two bytes contains the first bit for each strip. the second two bytes contains the second bit for each strip. etc

void makeTetrisRow(uint8_t codedColors[], byte output[], int outputRowIndex){
  uint8_t decodedGreen[TETRIS_WIDTH];
  uint8_t decodedRed[TETRIS_WIDTH];
  uint8_t decodedBlue[TETRIS_WIDTH];
  uint8_t bits1, bits2;
  const uint8_t GREEN_OFFSET = 0;
  const uint8_t RED_OFFSET = 8;
  const uint8_t BLUE_OFFSET = 16;
  const uint8_t BITS_PER_COLOR_COMPONENT = 8;

  for(int i=0; i<TETRIS_WIDTH; i++){
    uint8_t red, green, blue;
    decodeTetrisColor(codedColors[i], red, green, blue);
    decodedGreen[i] = green;
    decodedRed[i] = red;
    decodedBlue[i] = blue;
  }

  for (uint8_t j=0; j<BITS_PER_COLOR_COMPONENT; j++){
    bits1 = 0;
    bits2 = 0;
    for(int i=0; i<TETRIS_WIDTH; i++){      
      if (i >= 4){
        bits1 = bits1 << 1;
        bits1 = bits1 | (((1 << j) & decodedGreen[i]) >> j);
      }
      else {
        bits2 = bits2 << 1;
        bits2 = bits2 | (((1 << j) & decodedGreen[i]) >> j);
      }
    }
    output[(outputRowIndex * BYTES_PER_ROW * BITS_PER_COLOR) + BYTES_PER_ROW * (j + GREEN_OFFSET)] = bits1 << 2;
    output[(outputRowIndex * BYTES_PER_ROW * BITS_PER_COLOR) + BYTES_PER_ROW * (j + GREEN_OFFSET) + 1] = bits2;
  }
  for (uint8_t j=0; j<BITS_PER_COLOR_COMPONENT; j++){
    bits1 = 0;
    bits2 = 0;
    for(int i=0; i<TETRIS_WIDTH; i++){      
      if (i >= 4){
        bits1 = bits1 << 1;
        bits1 = bits1 | (((1 << j) & decodedRed[i]) >> j);
      }
      else {
        bits2 = bits2 << 1;
        bits2 = bits2 | (((1 << j) & decodedRed[i]) >> j);
      }
    }
    output[(outputRowIndex * BYTES_PER_ROW * BITS_PER_COLOR) + BYTES_PER_ROW * (j + RED_OFFSET)] = bits1 << 2;
    output[(outputRowIndex * BYTES_PER_ROW * BITS_PER_COLOR) + BYTES_PER_ROW * (j + RED_OFFSET) + 1] = bits2;
  }
  for (uint8_t j=0; j<BITS_PER_COLOR_COMPONENT; j++){
    bits1 = 0;
    bits2 = 0;
    for(int i=0; i<TETRIS_WIDTH; i++){      
      if (i >= 4){
        bits1 = bits1 << 1;
        bits1 = bits1 | (((1 << j) & decodedBlue[i]) >> j);
      }
      else {
        bits2 = bits2 << 1;
        bits2 = bits2 | (((1 << j) & decodedBlue[i]) >> j);
      }
    }
    output[(outputRowIndex * BYTES_PER_ROW * BITS_PER_COLOR) + BYTES_PER_ROW * (j + BLUE_OFFSET)] = bits1 << 2;
    output[(outputRowIndex * BYTES_PER_ROW * BITS_PER_COLOR) + BYTES_PER_ROW * (j + BLUE_OFFSET) + 1] = bits2;
  }
}

void uncompressTetrisRow(uint8_t compressedColors[], uint8_t uncompressedColors[]){
  for(int i=0; i<TETRIS_WIDTH; i=i+2){
    uncompressedColors[i+1] = compressedColors[i / 2] & 0b00001111;
    uncompressedColors[i] = (compressedColors[i / 2] & 0b11110000) >> 4;
  }
}

void showTetris(byte output[]){
  
  cli();
  
  for (int j=0; j<TETRIS_LENGTH; j++){
    //send a row
    for (int i=0; i<BYTES_PER_ROW*BITS_PER_COLOR; i=i+BYTES_PER_ROW){
      sendBitX8(output[j*BYTES_PER_ROW*BITS_PER_COLOR + i], output[j*BYTES_PER_ROW*BITS_PER_COLOR + i+1]);
    }

    //send the row again b/c we display each pixel 4 times - 2 rows and 2 columns. the rows in code and the columns in wiring.
    for (int i=0; i<BYTES_PER_ROW*BITS_PER_COLOR; i=i+BYTES_PER_ROW){
      sendBitX8(output[j*BYTES_PER_ROW*BITS_PER_COLOR + i], output[j*BYTES_PER_ROW*BITS_PER_COLOR + i+1]);
    } 
  }
  
  sei();
  show();
  
}

//credit: https://github.com/joshmarinacci/nespad-arduino/blob/master/NESpad.cpp
byte readNES()
{
  byte ret = 0;
  byte i;
  doLatch();
  for (i = 0; i < 8; i++) {
    ret |= (doButtonRead(i == 7) << i);
    //Serial.print(ret);
  }
  return ~ret;
}

void doLatch()
{
  digitalWrite(PIN_LATCH,HIGH);
  delayMicroseconds(60);
  digitalWrite(PIN_LATCH,LOW);
}

byte doButtonRead(bool last)
{
  byte ret = digitalRead(PIN_DATA);
  if (!last)
  {
  delayMicroseconds(12);
  digitalWrite(PIN_CLOCK,HIGH);
  delayMicroseconds(12);
  digitalWrite(PIN_CLOCK,LOW);
  }
  return ret;
}

void doRefreshDisplay()
{
  uint8_t uncompressedColors[TETRIS_WIDTH];
  byte bytDecodedColorSplits[BYTES_PER_ROW * BITS_PER_COLOR * TETRIS_LENGTH];
  
  for (int j=0; j<TETRIS_WIDTH; j++) uncompressedColors[j] = 0;
  
  for (int i=0; i<TETRIS_LENGTH; i++){
    for (int j=0; j<(TETRIS_WIDTH); j++){
      uncompressedColors[j] = m_objGame->CurrentDisplay(j,i);
    }
         
    makeTetrisRow(uncompressedColors, bytDecodedColorSplits, i);      
  }
  
  showTetris(bytDecodedColorSplits);
}

GridEnums::Command doReceiveInput()
{
  byte bytButton = readNES();
  delay(150);

  switch(bytButton)
  {
    case 0b00000001:
    return GridEnums::CLOCKWISE;
    break;
    case 0b00000010:
    return GridEnums::COUNTERCLOCKWISE;
    break;
    case 0b00100000:
    return GridEnums::DOWN;
    break;
    case 0b01000000:
    return GridEnums::RIGHT;
    break;
    case 0b10000000:
    return GridEnums::LEFT;
    break;
  }
  return GridEnums::NONE;
}

void setup() {
  PIXEL_DDR = 0xff;    // Set all row pins to output
  PIXEL_DDR2 = 0xff;    // Set all row pins to output

  pinMode(PIN_LATCH, OUTPUT);
  pinMode(PIN_CLOCK, OUTPUT);
  pinMode(PIN_DATA, INPUT);
  
  clearAll();
  delay(500);

  m_objGame = new Game(doRefreshDisplay, doReceiveInput);  

  sendRedRow(255);
  delay(500);
  clearAll();
  delay(500);

  Serial.begin(9600);
}

void loop() {
  int intWaitCounter = 0;
  while (!m_blnIsPlaying)
  {
    cli();
    for(int i=0; i<STRING_LENGTH; i++){
        if (i == intWaitCounter) sendWhiteRow(255);
        else sendWhiteRow(0);
    }
    sei();
    show();
  
    if (m_blnIsWaitAscending) intWaitCounter++;
    else intWaitCounter--;
  
    if (intWaitCounter >= 39) m_blnIsWaitAscending = false;
    if (intWaitCounter <= 1) m_blnIsWaitAscending = true;

    delay(100);

    if (doReceiveInput() == GridEnums::LEFT) m_blnIsPlaying = true;
  }
  
  delay(500);
  m_objGame->play();

  m_blnIsPlaying = false;
}
