int bt2;
int bt3;
void setup() {
  pinMode(12, INPUT_PULLUP);
  pinMode(A3, OUTPUT);
  digitalWrite(A3, HIGH);
  pinMode(13, OUTPUT);
}

void loop() {
  bt2 = !digitalRead(12);
  bt3 = !digitalRead(A3);

  if ((bt2) or (bt3) == HIGH) {
    digitalWrite(13, HIGH);
  }
  else {
    digitalWrite(13, LOW);
  }
}
