/*
  Connections
  -----------
  SDA -> Arduino Analog (SDA pin)
  SCL -> Arduino Analog (SCL pin)
  VCC -> Arduino 5V
  GND -> Arduino GND
  SQW -> Arduino D2 (Needs to be an interrupt capable pin)
*/

#include <Wire.h>
#include "RTClib.h"
#include <avr/sleep.h>

const int alarm_pin = 2;
const int wake_slave_pin = 4;
const int voltage_pin = A1;
const int door_pin = 5;

bool door_state;
bool _send = false;

int voltage;
RTC_DS3231 rtc;

void setup () {
  Serial.begin(9600); // Start serial port for monitoring
  Wire.begin();

  pinMode(voltage_pin, INPUT);
  pinMode(alarm_pin, INPUT_PULLUP); // Set alarm pin as pullup
  pinMode(wake_slave_pin, OUTPUT);
  pinMode(door_pin, INPUT_PULLUP);

  digitalWrite(wake_slave_pin, LOW);

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    abort();
  }

  // If required set time
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // To compiled time

  rtc.disableAlarm(1);
  rtc.disableAlarm(2);
  rtc.clearAlarm(1);
  rtc.clearAlarm(2);

  rtc.writeSqwPinMode(DS3231_OFF); // Place SQW pin into alarm interrupt mode

  Serial.println("Starting");
}
void enterSleep() {
  sleep_enable();
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);

  noInterrupts();
  attachInterrupt(digitalPinToInterrupt(alarm_pin), on_alarm, LOW);

  Serial.println("Going to sleep!");
  Serial.flush();                       // Ensure all characters are sent to the serial monitor

  interrupts();                         // Allow interrupts again
  sleep_cpu();

  /* The program will continue from here when it wakes */

  rtc.disableAlarm(1);
  rtc.disableAlarm(2);
  rtc.clearAlarm(1);
  rtc.clearAlarm(2);

  digitalWrite(wake_slave_pin, LOW);
  delay(200);
  digitalWrite(wake_slave_pin, HIGH);
  delay(200);
  digitalWrite(wake_slave_pin, LOW);
  Serial.println("I'm back!, waking slave");          // Print message to show we're back
}

void on_alarm() {
  sleep_disable(); // Disable sleep mode
  detachInterrupt(digitalPinToInterrupt(alarm_pin)); // Detach the interrupt to stop it firing
  _send = true;
}

void do_send() {

  voltage = map(analogRead(voltage_pin), 0, 1023, 0, 164);
  door_state = !digitalRead(door_pin);
  Serial.print(voltage);
  Serial.print(" V,  ");
  Serial.println(door_state);

  Wire.beginTransmission(5);
  delay(500);
  Wire.write(door_state);
  Serial.println("sending: doorstate");
  delay(1000);
  Wire.write(voltage);
  Serial.println("sending: voltage");
  delay(1000);
  Wire.endTransmission();
  _send = false;
}

void loop () {

  DateTime now = rtc.now();
  rtc.setAlarm1(DateTime(2021, 3, 06, 21, 8, 30), DS3231_A1_Minute);
  rtc.setAlarm2(DateTime(2021, 3, 06, 21, 9, 0), DS3231_A2_Minute);


  if (_send == true) {
    do_send();
  }
  else {
    enterSleep();
  }
}
