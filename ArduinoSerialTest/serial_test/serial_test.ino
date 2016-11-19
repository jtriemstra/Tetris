void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int intBytesRead = 0;
  int intBufferSize = 1;
  byte bytBuffer[intBufferSize];
  
  while (intBytesRead < intBufferSize)
  {
    if (Serial.available() > 0){
      bytBuffer[intBytesRead++] = Serial.read();
    }
  }

  delay(1000);

  Serial.write(bytBuffer[0]);
}
