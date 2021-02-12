void setup() {
  pinMode(2, INPUT_PULLUP);
}

void loop() {
  if (!(digitalRead(2)) == HIGH) {
    digitalWrite(13, HIGH);
  }
  else {
    digitalWrite(13, LOW);
  }
}
