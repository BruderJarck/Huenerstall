#include <Wire.h>
#include "RTClib.h"

RTC_DS3231 rtc;

void setup () {
  Wire.begin();
  rtc.begin();
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);


}

void loop () {
  DateTime now = rtc.now();

  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(" ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();

  if (now.second() < 20) {
    pinMode(LED_BUILTIN, HIGH);
  }
  else{
    pinMode(LED_BUILTIN, LOW);

  }
}
