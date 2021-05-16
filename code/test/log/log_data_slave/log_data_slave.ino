#include <Wire.h>
#include "RTClib.h"

bool door_state = true;
int Voltage = 125;
int uptime_h = 7;

String log_time;
String data_s;

char message[20];

RTC_DS3231 rtc;

String relevant_time() {
  DateTime now = rtc.now();
  log_time = "";
  log_time.concat(String(now.month()));
  log_time.concat(",");
  log_time.concat(String(now.hour()));
  log_time.concat(":");
  log_time.concat(String(now.minute()));
  //Serial.println(log_time);
  return log_time;
}

void do_send_data() {
  data_s.concat(door_state);
  data_s.concat(Voltage);
  data_s.concat(uptime_h);
  data_s.concat(relevant_time());
  data_s.toCharArray(message, 20);
  Serial.println(data_s);
  Wire.beginTransmission(5);
  Wire.write(0);//log bool
  Wire.write(0);//device id
  Wire.write(message);
  Wire.endTransmission();
  memset(message, " ", sizeof(message));
}

void do_send_log(String text) {
  text.concat(relevant_time());
  text.toCharArray(message, 20);
  Serial.println(text);
  Wire.beginTransmission(5);
  Wire.write(1);//log bool
  Wire.write(0);//device id
  Wire.write(message, sizeof(message));
  Wire.endTransmission();
  memset(message, " ", sizeof(message));
}

void setup() {
  Wire.begin();
  Serial.begin(9600);
  do_send_log("hallo log ");
  delay(1000);
  Serial.println("send log");
  do_send_data();
  Serial.println("send data");

}

void loop() {
  // put your main code here, to run repeatedly:

}
