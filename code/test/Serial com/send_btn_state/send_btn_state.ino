#include <Wire.h>
#include "RTClib.h"

DS3231 rtc;
int inpin = 4;
int readval;

void setup() {
  pinMode(inpin, INPUT_PULLUP);
  Wire.begin();
  rtc.begin();
  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  Serial.begin(9600);

}

void loop() {

  DateTime now = rtc.now();
  if(now.second() == 0){
  Serial.write(1);
  Serial.write(0);
  Serial.write(map(1250, 1100, 1400, 0, 255 ));
  Serial.write(1);
  }
  else{
    Serial.write(0);
  }


}
