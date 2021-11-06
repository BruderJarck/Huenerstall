#include <Wire.h>
#include "RTClib.h"

const unsigned int uphours[] = {10, 10, 8, 7, 5, 4, 4, 5, 6, 7, 8, 9};
const unsigned int upminutes[] = {0, 30, 0, 20, 0, 30, 30, 0, 15, 0, 50, 30};
const unsigned int downhours[] = {15, 16, 18, 18, 19, 20, 20, 20, 19, 18, 16, 15};
const unsigned int downminutes[] = {30, 30, 0, 45, 30, 10, 30, 0, 0, 0, 20, 30};

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

  if ((now.hour() >= int(uptime_h)) and (now.hour() < int(downtime_h))) {
    up();
    zaun(false);
  }
  else {
    up();
    down();
    zaun(true);
  }
}

void refit_up_down_times() {
  DateTime now = rtc.now();

  uptime_h = uphours[now.month()];
  uptime_m = upminutes[now.month()];
  downtime_h = downhours[now.month()];
  downtime_m = downminutes[now.month()];
}

void loop () {

  DateTime now = rtc.now();

  door_btn = digitalRead(door_btn_pin);
  Serial.println("loop");

  //---------------------------------------------------------------------------------------------------------------

  if ((now.hour() >= int(uptime_h)) and (now.hour() < int(downtime_h))) {
    if (door_btn_triggered == true) {
      if (millis() - door_btn_triggered_time > refit_door_time) {
        door_btn_triggered = false;
      }
    }
    else {
      if (door_state == false) {
        up();
        zaun(false);
        refit_up_down_times();
      }
    }
  }
  else {
    if (door_btn_triggered == true) {
      if (millis() - door_btn_triggered_time > refit_door_time) {
        door_btn_triggered = false;
      }
    }
    else {
      if (door_state == true) {
        down();
        zaun(true);
        refit_up_down_times(); 
      }
    }
  }

  //-------------------------------------------------------------------------------------------------------------- -

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
