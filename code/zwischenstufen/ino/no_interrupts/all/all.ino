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

char log_message[20];
String log_message_s;
String log_time;
int voltage;
RTC_DS3231 rtc;

void _stop() {
  do_send_log("stop");
  digitalWrite(m11, LOW);
  digitalWrite(m12, LOW);
}

void up() {
  do_send_log("up started");
  up_started_time = millis();
  while (true) {
    if ( door_timed_out == false) {
      end_btn = !digitalRead(end_btn_pin);
      digitalWrite(m11, HIGH);
      digitalWrite(m12, LOW);

      if (end_btn == HIGH) {
        _stop();
        door_state = true;
        break;
      }
      if (millis() - up_started_time >= door_up_timeout) {
        do_send_log("door timedout");
        status_code.concat(01);
        door_timed_out = true;
        _stop();
        break;
      }
    }
  }
}

void down() {
  if (door_timed_out == false) {
    do_send_log("down started");
    digitalWrite(m11, LOW);
    digitalWrite(m12, HIGH);
    delay(downtraveltime);
    _stop();
    door_state = false;
  }
  else {
    do_send_log("door timed out");
    _stop();
  }
}

void zaun(bool state) {
  digitalWrite(zaun_relais_pin, state);
  zaun_state = state;
  do_send_log("door timed out");
  log_message_s = "zaunstate ";
  log_message_s.concat(String(zaun_state));
  do_send_log(log_message_s);
}

void setup () {
  do_send_log("Starting");
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
    do_send_log("cound't find rtc");
    abort();
    status_code.concat(02);
  }

  DateTime now = rtc.now();

  old_month = now.month();
  log_message_s = "old month: ";
  log_message_s.concat(String(old_month));

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
    do_send_log("intial");
    up();
    zaun(true);
    do_send_data();
  }
  else {
    do_send_log("intial");
    up();
    down();
    zaun(false);
    do_send_data();
  }
  log_message_s = String(uptime_h);
  log_message_s.concat("/");
  log_message_s.concat(downtime_h);
  do_send_log("up/down: ");
}

void do_send_data() {

  voltage = map(analogRead(voltage_pin), 0, 1023, 0, 218);
  do_send_log("send data i2c");
  char device_id_array[1];
  char status_code_array[5];
  char door_state_array[1];
  char zaun_state_array[1];
  char voltage_array[3];
  char uptime_h_array[2];
  char downtime_h_array[2];
  char uptime_m_array[2];
  char downtime_m_array[2];

  status_code.toCharArray(status_code_array, 1);
  //int Voltage;
  //voltage.toInt();
  //int(voltage).toCharArray(voltage_array, 3);
  
  Wire.beginTransmission(5);
  Wire.write(0);
  Wire.write(status_code);
  Wire.write(door_state);
  Wire.write(zaun_state);
  Wire.write(Voltage);
  Wire.write(int(uptime_h));
  Wire.write(int(uptime_m));
  Wire.write(int(downtime_h));
  Wire.write(int(downtime_m));
  Wire.endTransmission();
  do_send_log("done sending data i2c");
}

void do_send_log(String text) {
  text.toCharArray(log_message, 20);
  text.concat(relevant_time());
  Wire.beginTransmission(5);
  Wire.write(1);
  Wire.write(log_message);
  Wire.endTransmission();
}

String relevant_time() {
  DateTime now = rtc.now();
  log_time.concat(String(now.month()));
  log_time.concat(String(now.hour()));
  log_time.concat(String(now.minute()));
  return log_time;
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
        do_send_log("outside up");
      }
    }
    else {
      if (door_state == false) {
        do_send_log("timed up");
        up();
        zaun(true);
        do_send_data();

      }
    }
  }
  else {
    if (door_btn_triggered == true) {
      if (millis() - door_btn_triggered_time > refit_door_time) {
        do_send_log("outside down");
        door_btn_triggered = false;
      }
    }
    else {
      if (door_state == true) {
        do_send_log("timed down");
        down();
        zaun(false);
        do_send_data();
      }
    }
  }

  //-------------------------------------------------------------------------------------------------------------- -
  /*if (send_btn == HIGH) {
    do_send_data();
    delay(400);
    }
  */
  //-------------------------------------------------------------------------------------------------------------- -

  if (door_btn == HIGH) {
    if (door_state == true) {
      do_send_log("btn down");
      down();
    }
    else {
      do_send_log("btn up");
      up();
    }
    door_btn_triggered = true;
    door_btn_triggered_time = millis();
    do_send_data();
    delay(400);
  }
  //-------------------------------------------------------------------------------------------------------------- -
  if (zaun_btn == HIGH) {
    if (zaun_state == false) {
      do_send_log("bt zaun an ");
      zaun(true);
      do_send_data();
    }
    else {
      do_send_log("bt zaun aus ");
      zaun(false);
      do_send_data();
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
    log_message_s = "month changed ";
    log_message_s.concat(String(uptime_h));
    log_message_s.concat("/");
    log_message_s.concat(String(uptime_m));
    do_send_log(log_message_s);
  }
}
