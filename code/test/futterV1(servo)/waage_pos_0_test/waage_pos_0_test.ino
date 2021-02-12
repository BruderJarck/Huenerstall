#include <Servo.h>
int in1 = 4;
int waage ;
Servo myservo;
void setup() {
  myservo.attach(3);
  pinMode(13, OUTPUT);
}

void loop() {
  waage = !digitalRead(in1);

  if (waage == HIGH) {
    digitalWrite(13, HIGH);
    delay(1000);
    digitalWrite(13, LOW);
  }
  myservo.write(5);
  delay(2000);
  if (waage == HIGH) {
    digitalWrite(13, HIGH);
    delay(1000);
    digitalWrite(13, LOW);
  }
  myservo.write(10);
  delay(2000);
  if (waage == HIGH) {
    digitalWrite(13, HIGH);
    delay(1000);
    digitalWrite(13, LOW);
  }

  myservo.write(15);
  delay(2000);
  if (waage == HIGH) {
    digitalWrite(13, HIGH);
    delay(1000);
    digitalWrite(13, LOW);
  }
  myservo.write(20);
  delay(2000);
  if (waage == HIGH) {
    digitalWrite(13, HIGH);
    delay(1000);
    digitalWrite(13, LOW);
  }


}
