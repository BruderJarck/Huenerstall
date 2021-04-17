#include <Wire.h>
#include "RTClib.h"

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

float uptime_h = 12;
float uptime_m = 0;   //minutes
float downtime_h = 15;
float downtime_m = 0; //minutes
int old_month;
String status_code = "00";

bool send_btn;
bool door_btn;
bool zaun_btn;
bool end_btn ;
bool door_btn_triggered = false;
int downtraveltime = 1100; //ms
int door_up_timeout = 3000; //ms
int refit_door_time = 60000; //ms
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
  up_started_time = millis();
  while (true) {
    if ( door_timed_out == false) {
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
      if (millis() - up_started_time >= door_up_timeout) {
        Serial.println("door timedout");
        status_code.concat(01);
        door_timed_out = true;
        _stop();
        break;
      }
    }
    else {
      Serial.println("door timed out!");
    }
  }
}

void down() {
  if (door_timed_out == false) {
    Serial.println("down started");
    digitalWrite(m11, LOW);
    digitalWrite(m12, HIGH);
    delay(downtraveltime);
    _stop();
    Serial.println("down stoped");
    door_state = false;
  }
  else {
    Serial.println("door timed out!!");
    _stop();
  }
}

void zaun(bool state) {
  digitalWrite(zaun_relais_pin, state);
  zaun_state = state;
  Serial.print("zaunstate: ");
  Serial.println(zaun_state);
}

void setup () {
  Serial.println("Starting");

  Serial.begin(9600);
  Wire.begin();

  pinMode(voltage_pin, INPUT);
  pinMode(wake_pin, INPUT_PULLUP);
  pinMode(end_btn_pin, INPUT_PULLUP);
  pinMode(wake_slave_pin, OUTPUT);
  pinMode(door_btn_pin, INPUT_PULLUP);
  pinMode(zaun_btn_pin, INPUT_PULLUP);
  pinMode(send_bt_pin, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);


  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    abort();
    status_code.concat(02);
  }

  DateTime now = rtc.now();

  old_month = now.month();
  for (int i = 0; i <= 12; i++) {

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

  if ((now.hour() >= int(uptime_h)) and (now.hour() < int(downtime_h))) {
    up();
    zaun(true);
    do_send();
  }
  else {
    up();
    down();
    zaun(false);
    do_send();
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
  
  Serial.println("send data I2C");
  Wire.beginTransmission(5);
  Wire.write(status_code.toInt());
  Wire.write(door_state);
  Wire.write(zaun_state);
  Wire.write(voltage);
  Wire.write(int(uptime_h));
  Wire.write(int(uptime_m));
  Wire.write(int(downtime_h));
  Wire.write(int(downtime_m));
  Wire.endTransmission();
  Serial.println("done sending data I2C");
}


void loop () {

  DateTime now = rtc.now();

  door_btn = !digitalRead(send_bt_pin);
  zaun_btn = !digitalRead(zaun_btn_pin);
  //send_btn = !digitalRead(send_bt_pin);

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
        zaun(true);
        do_send();
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
        zaun(false);
        do_send();
      }
    }
  }

  //-------------------------------------------------------------------------------------------------------------- -
  /*if (send_btn == HIGH) {
    do_send();
    delay(400);
    }
  */
  //-------------------------------------------------------------------------------------------------------------- -
  
  if (door_btn == HIGH) {
    if (door_state == true) {
      Serial.println("door down");
      down();
    }
    else {
      Serial.println("door up");
      up();
    }
    door_btn_triggered = true;
    door_btn_triggered_time = millis();
    do_send();
    delay(400);
  }
  //-------------------------------------------------------------------------------------------------------------- -
  if (zaun_btn == HIGH) {
    if (zaun_state == false) {
      zaun(true);
      do_send();
    }
    else {
      zaun(false);
      do_send();
    }
    delay(400);
  }
  //-------------------------------------------------------------------------------------------------------------- -

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
