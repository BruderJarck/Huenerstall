#include <Wire.h>
#include "RTClib.h"

DS3231 rtc;

int togglebutton;
int endswitch;
int testbutton;
int zaunbutton;

bool debug = false;

int m11 = 6;
int m12 = 7;
int endpin = 12;
int togglepin = A0;
int testpin = A1;
int zaunpin = A2;
int relaispin = A3;

int uptimeH = 7;   //oclock
//int uptimeM = 30;   //minutes
int downtimeH = 18; //oclock
//int downtimeM = 30; //minutes

int downtraveltime = 1200; //ms
bool doorstate = false; //0=closed, 1=opened
bool zaunstate = false;

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
void stopp() {
  digitalWrite(m11, LOW);
  digitalWrite(m12, LOW);
}


void setup() {

  pinMode(m11, OUTPUT);
  pinMode(m12, OUTPUT);
  pinMode(relaispin, OUTPUT);
  pinMode(togglepin, INPUT_PULLUP);
  pinMode(testpin, INPUT_PULLUP);
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
  testbutton = !digitalRead(testpin);
  zaunbutton = !digitalRead(zaunpin);


  DateTime now = rtc.now();

  if (debug == true) {

    Serial.print(now.hour());
    Serial.print(":");
    Serial.print(now.minute());
    Serial.print(":");
    Serial.print(now.second());
    Serial.print(" ");
    Serial.print(doorstate);
    Serial.print(" ");
    Serial.println(togglebutton);
  }

  else {
/*
 * 
 */
    if (testbutton == HIGH) {
      up();
      delay(3000);
      down();
      digitalWrite(relaispin, HIGH);
      delay(5000);
      digitalWrite(relaispin, LOW);
    }
    /*
          if ( zaunbutton == HIGH) {

          if (zaunstate == true) {
            digitalWrite(relaispin, LOW);
          }
          else {
            digitalWrite(relaispin, HIGH);
          }
          }
    */
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
/*
    if (togglebutton == HIGH) {

      if (doorstate == false) {
        up();
      }
      else {
        down();
      }
    }
*/
  }
}
