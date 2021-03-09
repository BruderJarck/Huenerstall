#include <Wire.h>

void setup() {
  Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(5);
  Wire.write(1);
  Wire.write(0);
  Wire.write(125);
  Serial.println("sending");
  Wire.endTransmission();
}

void loop() {

}
