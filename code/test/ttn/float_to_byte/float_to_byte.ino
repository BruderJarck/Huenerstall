/**
  Communicates float data over serial without loss of precision
*/
byte a;
byte b;
byte c[1];
byte d = 255;
void setup() {
  Serial.begin(9600); // setup serial connection speed

}

void loop() {

  float a = 12.59;
  serialFloatPrint(a);

  delay(1000);
}


void serialFloatPrint(float f) {
  /*
    byte * b = (byte *) &f;
    Serial.print(f);
    Serial.print(" ");
    Serial.print(c, BIN);
    Serial.print(" ");
    Serial.print(b[0], BIN);
    Serial.print(" ");
    Serial.print(b[1], BIN);
    Serial.print(" ");
    Serial.print(b[2], BIN);
    Serial.print(" ");
    Serial.println(b[3], BIN);
  */
  
  a = map(1259, 1100, 1400, 0, 255);
  b = map(a, 0, 255, 1100, 1400);
  c[0] = a;
  c[1] = b;
  Serial.print("8bit dec: ");
  Serial.print(a);
  Serial.print(" 8bit bin: ");
  Serial.print(byte(a));
  Serial.print(" back convert: ");
  Serial.print(b);
  Serial.print(" ");
  Serial.println(d);
  //Serial.print(" ");
  //Serial.println(c[1], Bin);

}
