#include <Wire.h>
#include "RTClib.h"

DS3231 rtc;

int togglebutton;
int endswitch;


int m11 = 2;
int m12 = 3;
int endpin = A1;
int togglepin = A0;

int uptime = 9;   //oclock
int downtime = 11; //oclock
int downtraveltime = 5000; //ms
int doorstate = 0; //0=closed, 1=opened

bool up(bool val) {

  while (true) {

    endswitch = !digitalRead(endpin);
    Serial.print(" ");
    Serial.println(endswitch);
    digitalWrite(m11, HIGH);
    digitalWrite(m12, LOW);

    if (endswitch == HIGH) {
      stopp();
      doorstate = 1;
      if (val == true) {
        delay(61000);
      }
      break;
    }
  }
}

bool down(bool val) {

  digitalWrite(m11, LOW);
  digitalWrite(m12, HIGH);
  delay(downtraveltime);
  stopp();
  if (val == true) {
    delay(61000);
  }
  doorstate = 0;
}

void stopp() {
  digitalWrite(m11, LOW);
  digitalWrite(m12, LOW);
}



void setup() {

  pinMode(m11, OUTPUT);
  pinMode(m12, OUTPUT);
  pinMode(togglepin, INPUT_PULLUP);
  pinMode(endpin, INPUT_PULLUP);

  Wire.begin();
  rtc.begin();
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}


void loop() {
  togglebutton = !digitalRead(togglepin);

  DateTime now = rtc.now();
  Serial.print(uptime);
  Serial.print(" ");
  Serial.print(downtime);
  Serial.print(" ");
  Serial.print(now.hour());
  Serial.print(":");
  Serial.print(now.minute());
  Serial.print(":");
  Serial.print(now.second());
  Serial.print(" ");
  Serial.print(doorstate);
  Serial.print(" ");
  Serial.println(togglebutton);


  if (uptime == now.minute()) {

    if (doorstate == 0) {
      up(true);
    }
  }

  if (downtime == now.minute()) {

    if (doorstate == 1) {
      down(true);
    }
  }

  if (togglebutton == HIGH) {

    if (doorstate == 0) {
      up(false);
    }
    else {
      down(false);
    }

  }
}
