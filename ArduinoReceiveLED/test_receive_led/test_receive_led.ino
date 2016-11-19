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

const int TETRIS_LENGTH = 20;
const int TETRIS_WIDTH = 10;
const int STRING_LENGTH = 40;

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


// Each string is one bit in "row" represening on or off

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

static inline void __attribute__ ((always_inline)) sendColorRow( uint8_t row, uint8_t red, uint8_t green, uint8_t blue ) {
  if (row == 0) 
  {
    uint8_t bit=24;   
    while (bit--) {
      sendBitX8(0b00000000, 0) ;
    }    
  }
  else
  {
    unsigned int bitMask = 128;
    for (int i=0; i<8; i++){
      if (green & bitMask) sendBitX8(row, row);
      else sendBitX8(0b00000000, 0);
      bitMask = bitMask >> 1;
    }
    bitMask = 128;
    for (int i=0; i<8; i++){
      if (red & bitMask) sendBitX8(row, row);
      else sendBitX8(0b00000000, 0);
      bitMask = bitMask >> 1;
    }
    bitMask = 128;
    for (int i=0; i<8; i++){
      if (blue & bitMask) sendBitX8(row, row);
      else sendBitX8(0b00000000, 0);
      bitMask = bitMask >> 1;
    }
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

void decodeTetrisColor(uint8_t color, byte &red, byte &green, byte &blue){
  switch(color){
    case 0:
      red = 0;      green = 0;      blue = 0;      break;
     case 1:
      red = 127;      green = 0;      blue = 0;      break;
     case 2:
      red = 0;       green = 127;      blue = 0;      break;
     case 3:
      red = 0;      green = 0;      blue = 127;      break;
     case 4:
      red = 127;      green = 127;      blue = 0;      break;
     case 5:
      red = 127;      green = 0;      blue = 127;      break;
     case 6:
      red = 0;      green = 127;      blue = 127;      break;
     default:
      red = 255; green = 255; blue = 255; break;
  }
}

void sendTetrisBits(uint8_t oneColorPerRow[]){
  uint8_t bits1, bits2;
  
  for(int j=0; j<8; j++){
    bits1 = 0;
    bits2 = 0;
    for(int i=0; i<TETRIS_WIDTH; i++){      
      if (i >= 4){
        bits1 = bits1 << 1;
        bits1 = bits1 | ((1 << j) & oneColorPerRow[i]);
      }
      else {
        bits2 = bits2 << 1;
        bits2 = bits2 | ((1 << j) & oneColorPerRow[i]);
      }
    }
    sendBitX8(bits1,bits2);
  }
}

void showTetrisRow(uint8_t codedColors[]){
  uint8_t decodedGreen[TETRIS_WIDTH];
  uint8_t decodedRed[TETRIS_WIDTH];
  uint8_t decodedBlue[TETRIS_WIDTH];
  uint8_t bits1arr[24];
  uint8_t bits2arr[24];
  uint8_t bits1, bits2;
  
  for(int i=0; i<TETRIS_WIDTH; i++){
    uint8_t red, green, blue;
    decodeTetrisColor(codedColors[i], red, green, blue);
    decodedGreen[i] = green;
    decodedRed[i] = red;
    decodedBlue[i] = blue;
  }

  for (int j=0; j<8; j++){
    bits1 = 0;
    bits2 = 0;
    for(int i=0; i<TETRIS_WIDTH; i++){      
      if (i >= 4){
        bits1 = bits1 << 1;
        bits1 = bits1 | ((1 << j) & decodedGreen[i]);
      }
      else {
        bits2 = bits2 << 1;
        bits2 = bits2 | ((1 << j) & decodedGreen[i]);
      }
    }
    bits1arr[j] = bits1 << 2;
    bits2arr[j] = bits2;
  }
  for (int j=0; j<8; j++){
    bits1 = 0;
    bits2 = 0;
    for(int i=0; i<TETRIS_WIDTH; i++){      
      if (i >= 4){
        bits1 = bits1 << 1;
        bits1 = bits1 | ((1 << j) & decodedRed[i]);
      }
      else {
        bits2 = bits2 << 1;
        bits2 = bits2 | ((1 << j) & decodedRed[i]);
      }
    }
    bits1arr[j+8] = bits1 << 2;
    bits2arr[j+8] = bits2;
  }
  for (int j=0; j<8; j++){
    bits1 = 0;
    bits2 = 0;
    for(int i=0; i<TETRIS_WIDTH; i++){      
      if (i >= 4){
        bits1 = bits1 << 1;
        bits1 = bits1 | ((1 << j) & decodedBlue[i]);
      }
      else {
        bits2 = bits2 << 1;
        bits2 = bits2 | ((1 << j) & decodedBlue[i]);
      }
    }
    bits1arr[j+16] = bits1 << 2;
    bits2arr[j+16] = bits2;
  }

  for (int j=0; j<24; j++){
    sendBitX8(bits1arr[j], bits2arr[j]);
  }
   
}

void uncompressTetrisRow(uint8_t compressedColors[], uint8_t uncompressedColors[]){
  for(int i=0; i<TETRIS_WIDTH; i=i+2){
    uncompressedColors[i+1] = compressedColors[i / 2] & 0b00001111;
    uncompressedColors[i] = (compressedColors[i / 2] & 0b11110000) >> 4;
  }
}

void flashSpecificRow(int row){
  clearAll();
  delay(1000);
  cli();
  for(int i=0; i<STRING_LENGTH; i++){
    if (i == row){
      sendRedRow(255);
    }
    else {
      sendRedRow(0);
    }    
  }
  sei();
  delay(1000);
}

int loopCount = 0;
bool blnIncrement = true;
bool blnRunning = false;

void setup() {
  PIXEL_DDR = 0xff;    // Set all row pins to output
  PIXEL_DDR2 = 0xff;    // Set all row pins to output
  
  clearAll();
  delay(500);

  Serial.begin(9600);
}



void loop() {
  int intCommandRead = 0;
  int intBufferSize = TETRIS_LENGTH * (TETRIS_WIDTH / 2);
  byte bytCommand[intBufferSize];

  while(true){
    if (Serial.available() > 0 && intCommandRead < 1){
      byte b = Serial.read();
      intCommandRead++;
      byte b1[5];
      byte b2[10];
      for (int i=0; i< 5; i++) b1[i] = 0;
      for (int i=0; i<10; i++) b2[i] = 0;
      b1[0] = b;
      uncompressTetrisRow(b1,b2);

      /*byte green, red, blue;
      green = 255;
      red = 0;
      blue = 0;
      cli();
      decodeTetrisColor(b2[0], red, green, blue);
      sendColorRow(255, red, green, blue);   
      decodeTetrisColor(b2[1], red, green, blue);
      sendColorRow(255, red, green, blue); 
      decodeTetrisColor(b2[2], red, green, blue);
      sendColorRow(255, red, green, blue);  
      decodeTetrisColor(b2[3], red, green, blue);
      sendColorRow(255, red, green, blue);  
      decodeTetrisColor(b2[4], red, green, blue);
      sendColorRow(255, red, green, blue);  
      decodeTetrisColor(b2[5], red, green, blue);
      sendColorRow(255, red, green, blue);  
      decodeTetrisColor(b2[6], red, green, blue);
      sendColorRow(255, red, green, blue);  
      decodeTetrisColor(b2[7], red, green, blue);
      sendColorRow(255, red, green, blue);  
      decodeTetrisColor(b2[8], red, green, blue);
      sendColorRow(255, red, green, blue);  
      decodeTetrisColor(b2[9], red, green, blue);
      sendColorRow(255, red, green, blue);    
      sei();*/

      
      cli();     
      sendBitX8(0,0);
      sendBitX8(0,0);
      sendBitX8(0,0);
      sendBitX8(0,0);
      sendBitX8(0,0);
      sendBitX8(0,0);
      sendBitX8(0,0);
      sendBitX8(0,0);
      sendBitX8(0,0);
      sendBitX8(0,12);
      sendBitX8(0,12);
      sendBitX8(0,12);
      sendBitX8(0,12);
      sendBitX8(0,12);
      sendBitX8(0,12);
      sendBitX8(0,12);
      sendBitX8(0,0);
      sendBitX8(0,0);
      sendBitX8(0,0);
      sendBitX8(0,0);
      sendBitX8(0,0);
      sendBitX8(0,0);
      sendBitX8(0,0);
      sendBitX8(0,0);
      
      sendBitX8(0,0);
      sendBitX8(0,0);
      sendBitX8(0,0);
      sendBitX8(0,0);
      sendBitX8(0,0);
      sendBitX8(0,0);
      sendBitX8(0,0);
      sendBitX8(0,0);
      sendBitX8(0,0);
      sendBitX8(0,12);
      sendBitX8(0,12);
      sendBitX8(0,12);
      sendBitX8(0,12);
      sendBitX8(0,12);
      sendBitX8(0,12);
      sendBitX8(0,12);
      sendBitX8(0,0);
      sendBitX8(0,0);
      sendBitX8(0,0);
      sendBitX8(0,0);
      sendBitX8(0,0);
      sendBitX8(0,0);
      sendBitX8(0,0);
      sendBitX8(0,0);
      sei();

      /*cli();
      for (int i=0; i<24; i++){
        if (i < 9 || i > 15) sendBitX8(0,0);
        else sendBitX8(0,12);
      }
      sei();*/

      
      /*cli();
      showTetrisRow(b2);
      showTetrisRow(b2);
      sei();*/
      delay(1000);
    }
  }

  
  /*while (intCommandRead < intBufferSize)
  {
    if (Serial.available() > 0){
      bytCommand[intCommandRead++] = Serial.read();
    }
  }
  
  for (int i=0; i<TETRIS_LENGTH; i++){
    uint8_t compressedColors[TETRIS_WIDTH / 2];
    uint8_t uncompressedColors[TETRIS_WIDTH];
    
    for (int j=0; j<TETRIS_WIDTH / 2; j++){
      compressedColors[j] = bytCommand[i*(TETRIS_WIDTH / 2) + j];
    }
    uncompressTetrisRow(compressedColors, uncompressedColors);
        
    cli();
    testTetrisRow(uncompressedColors);
    sei();
  }
delay(100);
  //show();*/
}
