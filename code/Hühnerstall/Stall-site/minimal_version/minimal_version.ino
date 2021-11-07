#include <Wire.h>
#include "RTClib.h"

const unsigned int uphours[] = {10, 10, 8, 7, 5, 4, 4, 5, 6, 7, 8, 9};
const unsigned int upminutes[] = {0, 30, 0, 20, 0, 30, 30, 0, 15, 0, 50, 30};
const unsigned int downhours[] = {16, 17, 18, 19, 20, 20, 21, 20, 19, 18, 18, 18};
const unsigned int downminutes[] = {15, 15, 45, 30, 15, 55, 15, 45, 45, 45, 15, 45};

const int door_btn_pin = A0;
const int end_btn_pin = 12;
const int zaun_relais_pin = A3;
const int m11 = 6;
const int m12 = 7;

unsigned int uptime_h;
unsigned int uptime_m;
unsigned int downtime_h;
unsigned int downtime_m;

bool send_btn;
bool door_btn;
bool end_btn ;
bool door_btn_triggered = false;
int downtraveltime = 1000; //ms
int door_up_timeout = 3000; //ms
unsigned int refit_door_time = 60000; //ms
bool door_state;
bool zaun_state = false;
bool door_timed_out;

unsigned long door_btn_triggered_time = 0;
unsigned long up_started_time = 0;

int voltage;
RTC_DS3231 rtc;

void _stop() {
  digitalWrite(m11, LOW);
  digitalWrite(m12, LOW);
}

void up() {
  Serial.println("up");
  up_started_time = millis();
  while (true) {
    end_btn = !digitalRead(end_btn_pin);

    if ( door_timed_out == false) {
      Serial.println(end_btn);
      digitalWrite(m11, HIGH);
      digitalWrite(m12, LOW);

      if (end_btn == HIGH) {
        Serial.println("stop");
        _stop();
        door_state = true;
        break;
      }
      if (millis() - up_started_time >= door_up_timeout) {
        door_timed_out = true;
        _stop();
        break;
      }
    }
    else {
      Serial.println("timedout");
    }
  }
  delay(2000);
}

void down() {
  Serial.println("down");
  if (door_timed_out == false) {
    digitalWrite(m11, LOW);
    digitalWrite(m12, HIGH);
    delay(downtraveltime);
    _stop();
    door_state = false;
  }
  else {
    _stop();
  }
}

void zaun(bool state) {
  digitalWrite(zaun_relais_pin, !state);
  zaun_state = state;
}

void setup () {
  Wire.begin();
  Serial.begin(9600);

  pinMode(end_btn_pin, INPUT_PULLUP);
  pinMode(door_btn_pin, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);


  if (! rtc.begin()) {
    abort();
  }

  DateTime now = rtc.now();
  Serial.print(now.hour());
  Serial.println(now.minute());

  refit_up_down_times();

  if ((now.hour() >= int(uptime_h)) and (now.hour() <= int(downtime_h))) {
    if (now.hour() == int(uptime_h) or now.hour() == int(downtime_h)) {
      if ((now.minute() <= int(uptime_m))) {
        Serial.println("in hour up");
        up();
        zaun(true);
      }
      else {
        Serial.println("in hour down");
        down();
        zaun(false);
      }
    }
    else {
      Serial.println("out hour up");
      up();
      zaun(true);
    }
  }
  else {
    Serial.println("out hour down");
    down();
    zaun(false);
  }
}

void refit_up_down_times() {
  DateTime now = rtc.now();
  uptime_h = uphours[now.month() - 1];
  uptime_m = upminutes[now.month() - 1];
  downtime_h = downhours[now.month() - 1];
  downtime_m = downminutes[now.month() - 1];
  Serial.print(uptime_h);
  Serial.print(uptime_m);
  Serial.print(downtime_h);
  Serial.println(downtime_m);
}

void loop () {

  DateTime now = rtc.now();

  door_btn = !digitalRead(door_btn_pin);
  Serial.println("loop");

  //---------------------------------------------------------------------------------------------------------------

  if ((now.hour() == int(uptime_h)) and (now.minute() == int(uptime_m))) {
    if (door_state == false) {
      Serial.println("regular up");
      up();
      zaun(true);
      refit_up_down_times();
    }
  }

  if ((now.hour() == int(downtime_h)) and (now.minute() == int(downtime_m))) {
    if (door_state == true) {
      Serial.println("regular down");
      down();
      zaun(false);
      refit_up_down_times();
    }
  }

  if (door_btn == HIGH) {
    Serial.println("door_btn triggered");
    if (door_state == true) {
      down();
    }
    else {
      up();
    }
    door_btn_triggered = true;
    door_btn_triggered_time = millis();
    delay(400);
  }


  }

  //-------------------------------------------------------------------------------------------------------------- -
