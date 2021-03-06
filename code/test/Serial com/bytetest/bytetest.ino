unsigned char message[2];
byte btnstate;
int pin = 5;
void setup() {
  pinMode(pin, INPUT_PULLUP);
  Serial.begin(9600);
  btnstate = !digitalRead(pin);
  message[0] = btnstate;
  message[1] = 125;
  //Serial.print(btnstate, BIN);
  for (int i = 0; i < sizeof(message); i++) {
    Serial.println(message[i], BIN);
  }
}

void loop() {
}
