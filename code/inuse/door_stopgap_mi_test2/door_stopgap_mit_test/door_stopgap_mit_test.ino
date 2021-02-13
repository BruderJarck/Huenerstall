#include <Wire.h>5
#include "RTClib.h"

DS3231 rtc;

int togglebutton;
int endswitch;
int fitbutton;
int zaunbutton;

bool debug = true;

int m11 = 6;
int m12 = 7;
int endpin = 5;//12;
int togglepin = 2;//A0;
int fitpin = 3;//A1;
int zaunpin = 4;//;A2;
int relaispin = A3;

int uptimeH = 7;   //oclock
int uptimeM = 30;   //minutes
int downtimeH = 18; //oclock
int downtimeM = 16; //minutes

int downtraveltime = 1200; //ms
bool doorstate = false; //0=closed, 1=opened
bool zaunstate = false;

void stopp() {
  digitalWrite(m11, LOW);
  digitalWrite(m12, LOW);
}

void up() {
  while (true) {

    endswitch = !digitalRead(endpin);
    digitalWrite(m11, HIGH);
    digitalWrite(m12, LOW);

    if (endswitch == HIGH) {
      stopp();
      doorstate = true;
      break;
    }
  }
}

void down() {
  digitalWrite(m11, LOW);
  digitalWrite(m12, HIGH);
  delay(downtraveltime);
  stopp();
  doorstate = false;
}

void setup() {

  pinMode(m11, OUTPUT);
  pinMode(m12, OUTPUT);
  pinMode(relaispin, OUTPUT);
  pinMode(togglepin, INPUT_PULLUP);
  pinMode(fitpin, INPUT_PULLUP);
  pinMode(endpin, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);

  digitalWrite(relaispin, HIGH);

  Wire.begin();
  rtc.begin();
  //rtc.adjust(DateTime(2021, 2, 2, 22, 00, 00));

  if (debug == true) {
    Serial.begin(9600);
  }
}


void loop() {
  togglebutton = !digitalRead(togglepin);
  fitbutton = !digitalRead(zaunpin);
  //zaunbutton = LOW;
  endswitch = !digitalRead(endpin);



  DateTime now = rtc.now();

  //--------------------------------------check debugmode--------------------------------------------------------------

  if (debug == true) {

    Serial.print(now.hour());
    Serial.print(":");
    Serial.print(now.minute());
    Serial.print(":");
    Serial.print(now.second());
    Serial.print(" ");
    Serial.print(doorstate);
    Serial.print(" ");
    Serial.print(togglebutton);
    Serial.print(" ");
    Serial.print(fitbutton);
    Serial.print(" ");
    Serial.print(endswitch);
    Serial.println(" ");
    //Serial.println(zaunbutton);
  }

  else {
    //--------------------------------------check fitbutton--------------------------------------------------------------

    if (fitbutton == HIGH) {
      if (now.hour() < downtimeH and now.hour() >= uptimeH) {

        digitalWrite(relaispin, HIGH);  //Zaun an
        zaunstate = true;

        if (doorstate == false) {
          up();
        }
      }

      else {

        digitalWrite(relaispin, LOW); //Zaun
        zaunstate = false;

        if (doorstate == true) {
          down();
        }
      }
    }
    //--------------------------------------check togglebutton--------------------------------------------------------------

    if (togglebutton == HIGH) {

      if (doorstate == false) {
        up();
      }
      else {
        down();
      }
    }

    /*  //--------------------------------------check zaunbutton--------------------------------------------------------------

      if (zaunbutton == HIGH) {

        if (zaunstate == true) {
          digitalWrite(relaispin, LOW);
          zaunstate = false;
        }
        else {
          digitalWrite(relaispin, HIGH);
          zaunstate = true;

        }
      }
    */
    //--------------------------------------check rtctime--------------------------------------------------------------
    if (now.hour() == uptimeH and now.minute() == uptimeM) {

      digitalWrite(relaispin, HIGH);  //Zaun an
      zaunstate = true;

      if (doorstate == false) {
        up();
      }
    }

    if (now.hour() == downtimeH and now.minute() == downtimeM) {

      digitalWrite(relaispin, LOW); //Zaun
      zaunstate = false;

      if (doorstate == true) {
        down();
      }
    }
  }
}
