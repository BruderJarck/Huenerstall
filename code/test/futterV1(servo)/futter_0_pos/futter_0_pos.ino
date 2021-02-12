#include <Servo.h>
int endfutter;
int x = 0;
int m1 = A1;
int m2 = A0;
int in2 = A2;

Servo myservo;

void setup() {
  pinMode(in2, INPUT_PULLUP);
  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
  myservo.attach(3);
  myservo.write(10);

}

void loop() {

  endfutter = !digitalRead(in2);
  while ((endfutter == LOW) and (x == 0)) { //solange endfutter nicht gedrückt ist zu fahren
    digitalWrite(m2, HIGH);
    digitalWrite(m1, LOW);
    endfutter = !digitalRead(in2);


    if (endfutter == HIGH) {//wenn endfutter btn erreicht ist dann anhalten
      x = 1;
      digitalWrite(m2, HIGH);
      digitalWrite(m1, HIGH);
      break;
    }

  }
}
