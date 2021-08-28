int pin1 = A0;
int pin2 = A1;
int pin3 = A3;
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

  Serial.print("0: ");
  Serial.print(bt1);
  Serial.print(" 1: ");
  Serial.print(bt2);
  Serial.print(" 2: ");
  Serial.print(bt3);
  Serial.print(" 12: ");
  Serial.println(bt4);
}
