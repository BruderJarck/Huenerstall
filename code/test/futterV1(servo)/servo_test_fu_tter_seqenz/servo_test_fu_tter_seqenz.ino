#include <Servo.h>
int in1 = 4;
int in2 = A2;
int m1 = A1;
int m2 = A0;
int waage;
int endfutter;
int  x = 0;
int x2 = 0;
int x3  = 0;
Servo myservo;
void setup() {
  myservo.attach(3);
  pinMode(in1, INPUT_PULLUP);
  pinMode(in2, INPUT_PULLUP);
  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
  myservo.write(25);

}

void loop() {
  waage = !digitalRead(in1);
  endfutter = !digitalRead(in2);

  delay(2000); //warten dann prg beginnu
  while ((endfutter == HIGH) and (x2 == 0)) { //solange schieber zu auf machen bis von end futzter weg + 2sek

    digitalWrite(m1, HIGH); //schieber auf für 2sek
    digitalWrite(m2, LOW);
    endfutter = !digitalRead(in2);

    if (endfutter == LOW) {
      delay(10000);
      digitalWrite(m1, LOW);//anhalten
      digitalWrite(m2, LOW);
    }
  }

  while ((waage == LOW) and (x3 = 0)) { // wenn futter portion erreicht ist dann zumachen
    if (waage == HIGH) {
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
  }
  delay(1000); // wegen restkörtner warten

  myservo.write(170); //auskippen
  delay(2000);

  myservo.write(10);//zurück in ausgangs pos

}
x = 0;
x2 = 0;
}
