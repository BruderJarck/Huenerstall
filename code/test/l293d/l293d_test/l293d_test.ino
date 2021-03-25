int m11 = 6;
int m12 = 7;

void setup() {
  pinMode(m11, OUTPUT);
  pinMode(m12, OUTPUT);

}

void loop() {
  digitalWrite(m11, HIGH);
  digitalWrite(m12, LOW);
  delay(2000);
  digitalWrite(m11, LOW);
  digitalWrite(m12, HIGH);
  delay(2000);
  digitalWrite(m11, LOW);
  digitalWrite(m12, LOW);
  delay(2000);
}
