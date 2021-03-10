#include <Wire.h>

void setup() {
  Serial.begin(9600);
  Wire.begin();
}

void loop() {

  Wire.beginTransmission(5);
  Wire.write(1);
  Serial.println("sending: 1");
  delay(1000);
  Wire.write(125);
  Serial.println("sending: 125");
  delay(1000);
  Wire.endTransmission();
}
