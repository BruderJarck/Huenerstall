#include <Wire.h>

void setup() {
  Serial.begin(9600);
  Wire.begin();

  Wire.beginTransmission(5);
  Wire.write(0);
    delay(1000);
  Wire.write("hi");

  Serial.println("sending: hi");
  delay(1000);
  Wire.write(125);
  Serial.println("sending: 125");
  delay(1000);
  Wire.endTransmission();
}

void loop() {

}
