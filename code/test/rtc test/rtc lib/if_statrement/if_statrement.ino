#include <Wire.h>
#include "RTClib.h"

DS3231 rtc;

void setup () {
  Wire.begin();
  rtc.begin();
  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);


}

void loop () {
  DateTime now = rtc.now();
  Serial.print(now.second(), DEC);
  Serial.println();
}
