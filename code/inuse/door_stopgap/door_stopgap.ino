#include <Wire.h>
#include "RTClib.h"

DS3231 rtc;

int togglebutton;
int endswitch;


int m11 = 2;
int m12 = 3;
int endpin = A1;
int togglepin = 4;
int relaispin = 5;

int uptimeH = 7;   //oclock
int uptimeM = 30;   //minutes
int downtimeH = 18; //oclock
int downtimeM = 30; //minutes

int downtraveltime = 1200; //ms
int doorstate = 0; //0=closed, 1=opened

void up() {

  while (true) {

    endswitch = !digitalRead(endpin);
    digitalWrite(m11, HIGH);
    digitalWrite(m12, LOW);

    if (endswitch == HIGH) {
      stopp();
      doorstate = 1;
      break;
    }
  }
}

void down() {

  digitalWrite(m11, LOW);
  digitalWrite(m12, HIGH);
  delay(downtraveltime);
  stopp();
  doorstate = 0;
}

void stopp() {
  digitalWrite(m11, LOW);
  digitalWrite(m12, LOW);
}



void setup() {

  pinMode(m11, OUTPUT);
  pinMode(m12, OUTPUT);
  pinMode(relaispin, OUTPUT);
  pinMode(togglepin, INPUT_PULLUP);
  pinMode(endpin, INPUT_PULLUP);

  Wire.begin();
  rtc.begin();
  rtc.adjust(DateTime(2021, 1, 31, 22,12, 00)); 
  //pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}


void loop() {
  togglebutton = !digitalRead(togglepin);

  DateTime now = rtc.now();
  ///*
  Serial.print(now.hour());
  Serial.print(":");
  Serial.print(now.minute());
  Serial.print(":");
  Serial.print(now.second());
  Serial.print(" ");
  Serial.print(doorstate);
  Serial.print(" ");
  Serial.println(togglebutton);
  //*/

  if (uptimeH == now.hour() and uptimeM == now.minute()) {

    digitalWrite(relaispin, HIGH);  //Zaun an

    if (doorstate == 0) {
      up();
    }
  }

  if (downtimeH == now.hour() and downtimeM == now.minute()) {

    digitalWrite(relaispin, LOW); //Zaun aus

    if (doorstate == 1) {
      down();
    }
  }

  if (togglebutton == HIGH) {

    if (doorstate == 0) {
      up();
    }
    else {
      down();
    }

  }
}
