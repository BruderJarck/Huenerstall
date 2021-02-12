#include <Servo.h>

Servo myservo;
void setup() {
  myservo.attach(3);
}

void loop() {
  myservo.write(170);
  delay(5000);
  myservo.write(10);
  delay(5000);
}
