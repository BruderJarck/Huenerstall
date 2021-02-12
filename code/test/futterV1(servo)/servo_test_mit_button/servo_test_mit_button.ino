#include <Servo.h>
int in1 = 4;
int in2 = 5;
int btn2;
int btn1;

Servo myservo;
void setup() {
  myservo.attach(3);
  pinMode(in1, INPUT_PULLUP);
  myservo.write(10);

}

void loop() {
  btn1 = !digitalRead(in1);
  if (btn1 == HIGH) {
    delay(2000);
    myservo.write(170);
    delay(5000);
    myservo.write(10);
    
  }
}
