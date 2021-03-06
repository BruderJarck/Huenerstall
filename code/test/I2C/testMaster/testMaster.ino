
void setup() {
  Serial.begin(9600);
  Wire.begin(); //I2C-Aktivierung
}

void loop() {
  Wire.beginTransmission(5);
  Wire.write(10125);
  Wire.endTransmission();
}
