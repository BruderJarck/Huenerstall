int pin1 = A0;
int pin2 = A1;
int pin3 = 2;
int pin4 = 12;

bool bt1;
bool bt2;
bool bt3;
bool bt4;

void setup() {
  pinMode(pin1, INPUT_PULLUP);
  pinMode(pin2, INPUT_PULLUP);
  pinMode(pin3, INPUT_PULLUP);
  pinMode(pin4, INPUT_PULLUP);
  Serial.begin(9600);
  pinMode(13, OUTPUT);
}

void loop() {
  bt1 = !digitalRead(pin1);
  bt2 = !digitalRead(pin2);
  bt3 = !digitalRead(pin3);
  bt4 = !digitalRead(pin4);

  Serial.print("1: ");
  Serial.print(bt1);
  Serial.print(" 2: ");
  Serial.print(bt2);
  Serial.print(" 3: ");
  Serial.print(bt3);
  Serial.print(" 4: ");
  Serial.println(bt4);
  if (bt1 or bt2 or bt3 or bt4 == HIGH) {
    digitalWrite(13, HIGH);
  }
  else {
    digitalWrite(13, LOW);
  }
}
