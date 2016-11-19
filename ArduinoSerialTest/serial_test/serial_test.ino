void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int intBytesRead = 0;
  int intBufferSize = 100;
  byte bytBuffer[intBufferSize];
  for (int i=0; i<intBufferSize; i++) bytBuffer[i] = 254;
  
  while (intBytesRead < intBufferSize)
  {
    if (Serial.available() > 0){
      bytBuffer[intBytesRead++] = Serial.read();
    }
  }

  //delay(2000);

  for(int i=0; i<intBufferSize; i++){
    Serial.write(bytBuffer[i]);
  }
}
