int measure_pin = A1;
float voltage;
void setup() {
  pinMode(measure_pin, INPUT);
  Serial.begin(9600);

}

void loop() {
  voltage = map(analogRead(measure_pin), 0, 1023, 0, 15);
  Serial.print(voltage);
  Serial.print(" V,  ");
  Serial.println(analogRead(measure_pin));
  

}
