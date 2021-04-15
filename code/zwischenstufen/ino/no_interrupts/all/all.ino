#include <Wire.h>
#include "RTClib.h"
#include <avr/sleep.h>

const int wake_pin = 3;
const int wake_slave_pin = A7;
const int voltage_pin = A2;
const int door_btn_pin = A0;
const int zaun_btn_pin = A1;
const int end_btn_pin = 12;
const int send_bt_pin = 2;
const int zaun_relais_pin = A3;
const int m11 = 6;
const int m12 = 7;

int uptime_h = 10;
int uptime_m = 0;   //minutes
int downtime_h = 15;
int downtime_m = 0; //minutes
int old_month;

bool send_btn;
bool door_btn;
bool zaun_btn;
bool end_btn ;
int downtraveltime = 1100; //ms
bool door_state;
bool zaun_state = false;
bool interrupt_triggered = false;

int voltage;
RTC_DS3231 rtc;

void _stop() {
  digitalWrite(m11, LOW);
  digitalWrite(m12, LOW);
}

void up() {
  while (true) {

    end_btn = !digitalRead(end_btn_pin);
    digitalWrite(m11, HIGH);
    digitalWrite(m12, LOW);
    Serial.println("up started");

    if (end_btn == HIGH) {
      _stop();
      door_state = true;
      Serial.println("up ended");
      break;
    }
  }
}

void down() {
  Serial.println("dowb started");
  digitalWrite(m11, LOW);
  digitalWrite(m12, HIGH);
  delay(downtraveltime);
  _stop();
  Serial.println("down stoped");
  door_state = false;
}

void zaun(bool state) {
  digitalWrite(zaun_relais_pin, state);
  zaun_state = state;
}
void setup () {
  Serial.begin(9600);
  Wire.begin();

  pinMode(voltage_pin, INPUT);
  pinMode(wake_pin, INPUT_PULLUP);
  pinMode(end_btn_pin, INPUT_PULLUP);
  pinMode(wake_slave_pin, OUTPUT);
  pinMode(door_btn_pin, INPUT_PULLUP);
  pinMode(zaun_btn_pin, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    abort();
  }

  up();
  //down();
  Serial.println("Starting");
  DateTime now = rtc.now();
  old_month = now.month();
  for (int i = 0; i <= 12; i++) {
    Serial.println(i);

    if (i <= 12 and i >= 7) {
      uptime_h = uptime_h + 0.8;
      downtime_h = downtime_h - 1.2;
    }
    else {
      uptime_h = uptime_h - 0.8;
      downtime_h = downtime_h + 1.2;
    }
    if (i == now.month()) {
      break;
    }
  }
  Serial.print(now.month());
  Serial.print(" ");
  Serial.print(int(uptime_h));
  Serial.print(":");
  Serial.print(int(uptime_m));
  Serial.print("/");
  Serial.print(int(downtime_h));
  Serial.print(":");
  Serial.println(int(downtime_m));
}


void do_send() {

  voltage = map(analogRead(voltage_pin), 0, 1023, 0, 218);
  /*//door_state = !digitalRead(door_pin);
    Serial.print(voltage);
    Serial.print(" V,  ");
    Serial.println(door_state);

    Wire.beginTransmission(5);
    delay(500);
    Wire.write(door_state);
    Serial.println("sending: doorstate");
    delay(1000);
    Wire.write(zaun_state);
    Serial.println("sending: zaunstate");
    delay(1000);
    Wire.write(voltage);
    Serial.println("sending: voltage");
    delay(1000);
    Wire.endTransmission();
  */

  Wire.beginTransmission(5);
  Wire.write(door_state);
  Wire.write(zaun_state);
  Wire.write(voltage);
  Wire.write(int(uptime_h));
  Wire.write(int(uptime_m));
  Wire.write(int(downtime_h));
  Wire.write(int(downtime_m));
  Wire.endTransmission();
  
}


void loop () {

  DateTime now = rtc.now();

  door_btn = !digitalRead(send_bt_pin);
  zaun_btn = !digitalRead(zaun_btn_pin);
  //send_btn = !digitalRead(send_bt_pin);

  //------------------------------------------------------------------------------------------------------------- -
  
  if ((now.hour() >= int(uptime_h)) and (now.hour() < int(downtime_h))) {
    if (door_state == false) {
      up();
      zaun(true);
      do_send();
    }
  }
  else {
    if (door_state == true) {
      down();
      zaun(false);
      do_send();

    }
  }
  //---------------------------------------------------------------------------------------------------------------
  /*
  if (send_btn == HIGH) {
    do_send();
    delay(400);
  }
  */
  //---------------------------------------------------------------------------------------------------------------
  
  if (door_btn == HIGH) {
    delay(400);
    if (door_state == true) {
      Serial.println("door down");
      down();
      do_send();

    }
    else {
      Serial.println("door up");
      up();
      do_send();

    }
    delay(400);
  }
  //-------------------------------------------------------------------------------------------------------------- -
  if (zaun_btn == HIGH) {
    if (zaun_state == false) {
      zaun(true);
      Serial.println("zaun on");
      do_send();
    }
    else {
      Serial.println("zaun off");
      zaun(false);
      do_send();
    }
    delay(400);
  }
  if (old_month != now.month()) {
    if (now.month() <= 12 and now.month() >= 7) {
      uptime_h = uptime_h + 0.8;
      downtime_h = downtime_h - 1.2;
    }
    else {
      uptime_h = uptime_h - 0.8;
      downtime_h = downtime_h + 1.2;
    }
    old_month = now.month();
  }
}
