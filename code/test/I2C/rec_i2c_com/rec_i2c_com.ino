#include <Wire.h>
#include "RTClib.h"

RTC_DS3231 rtc;
bool trig_btn;
void setup() {
  Serial.begin(9600);
  Wire.begin();

  pinMode(A0, INPUT_PULLUP);


  rtc.begin();
  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

void loop () {
  trig_btn = !digitalRead(A0);
  if (trig_btn == HIGH) {
    Wire.beginTransmission(5);
    Wire.write(1);
    Serial.println("sending: 1");
    delay(1000);
    Wire.write(125);
    Serial.println("sending: 125");
    delay(1000);
    Wire.endTransmission();
    DateTime now = rtc.now();
    Serial.print(now.second(), DEC);
    Serial.print(" ");
    Serial.println("sec");
  }
}
