/*
  Connections
  -----------
  SDA -> Arduino Analog (SDA pin)
  SCL -> Arduino Analog (SCL pin)
  VCC -> Arduino 5V
  GND -> Arduino GND
  SQW -> Arduino D2 (Needs to be an interrupt capable pin)
*/
//--------------------------------------lib-include-------------------------------------------------

#include "RTClib.h"     // DS3231 library
#include <avr/sleep.h>  // AVR library for controlling the sleep modes

//--------------------------------------var-def-------------------------------------------------

int togglebutton;
int endswitch;
int fitbutton;
int zaunbutton;

bool debug = true;

int m11 = 6;
int m12 = 7;
int endpin = 5;//12;
int togglepin = 3;//A0;
int fitpin = 2;//A1;
int zaunpin = 4;//;A2;
int relaispin = A3;
const int alarmPin = 2;

int uptimeH = 7;   //oclock
int uptimeM = 30;   //minutes
int downtimeH = 18; //oclock
int downtimeM = 16; //minutes

int downtraveltime = 1200; //ms
bool doorstate = false; //0=closed, 1=opened
bool zaunstate = false;

bool Up = false;
bool Down = false;
bool _update = false;
bool open_close = false;

RTC_DS3231 rtc;

//--------------------------------------setup_func-------------------------------------------------

void setup () {
  Serial.begin(9600); // Start serial port for monitoring

  pinMode(alarmPin, INPUT_PULLUP); // Set alarm pin as pullup

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    abort();
  }

  // If required set time
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // To compiled time
  //rtc.adjust(DateTime(2020, 7, 3, 20, 0, 0)); // Or explicitly, e.g. July 3, 2020 at 8pm

  // Disable and clear both alarms
  rtc.disableAlarm(1);
  rtc.disableAlarm(2);
  rtc.clearAlarm(1);
  rtc.clearAlarm(2);

  rtc.writeSqwPinMode(DS3231_OFF); // Place SQW pin into alarm interrupt mode

  pinMode(m11, OUTPUT);
  pinMode(m12, OUTPUT);
  pinMode(relaispin, OUTPUT);
  pinMode(togglepin, INPUT_PULLUP);
  pinMode(fitpin, INPUT_PULLUP);
  pinMode(endpin, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);

  digitalWrite(relaispin, HIGH);

  //if (debug == true) {
  // Serial.begin(9600);
  //}
  Serial.println("Starting");
}

//--------------------------------------door-func-------------------------------------------------

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

//--------------------------------------sleep-func-------------------------------------------------

void enterSleep() {
  sleep_enable();                       // Enabling sleep mode
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);  // Setting the sleep mode, in this case full sleep

  noInterrupts();                       // Disable interrupts
  attachInterrupt(digitalPinToInterrupt(alarmPin), on_alarm_up, LOW);
  attachInterrupt(digitalPinToInterrupt(alarmPin), on_alarm_down, LOW);
  attachInterrupt(digitalPinToInterrupt(togglepin), on_open_close, FALLING);


  Serial.println("Going to sleep!");    // Print message to serial monitor
  Serial.flush();                       // Ensure all characters are sent to the serial monitor

  interrupts();                         // Allow interrupts again
  sleep_cpu();                          // Enter sleep mode

  /* The program will continue from here when it wakes */

  // Disable and clear alarm
  rtc.disableAlarm(1);
  rtc.clearAlarm(1);

  Serial.println("I'm back!");          // Print message to show we're back
}

void on_alarm_up() {
  sleep_disable(); // Disable sleep mode
  detachInterrupt(digitalPinToInterrupt(alarmPin)); // Detach the interrupt to stop it firing
  Up = true;
  _update = true;
}

void on_alarm_down() {
  sleep_disable();
  detachInterrupt(digitalPinToInterrupt(alarmPin));
  Down = true;
  _update = true;
}
void on_open_close() {
  sleep.disable();
  detachInterrupt(digitalPinToInterrupt(alarmPin));
  open_close = true;

}


//--------------------------------------mainloop-------------------------------------------------

void loop () {

  togglebutton = !digitalRead(togglepin);
  fitbutton = !digitalRead(zaunpin);
  //zaunbutton = LOW;
  endswitch = !digitalRead(endpin);

  DateTime now = rtc.now();
  Serial.print(now.minute());
  Serial.print(" ");
  Serial.println(now.second());

  rtc.setAlarm1(DateTime(2021, 3, 06, 22, 52, 0), DS3231_A1_Second);
  rtc.setAlarm2(DateTime(2021, 3, 06, 22, 45, 30), DS3231_A2_Minute);

  enterSleep();

  if (Up = true && _update == true) {
    _update = false;
    Serial.println("there");

    /*
      digitalWrite(relaispin, HIGH);  //Zaun an
      zaunstate = true;
      if (doorstate == false) {
      up();
      }
    */
  }

  else if (open_close == true) {
    if (doorstate == false) {
      up();
    }
    else {
      down();
    }
  }

  else if (Down = true && _update == true) {
    _update = false;
    Serial.println("here");
    /*
      digitalWrite(relaispin, LOW); //Zaun
      zaunstate = false;
      if (doorstate == true) {
      down();
      }
    */
  }
}
