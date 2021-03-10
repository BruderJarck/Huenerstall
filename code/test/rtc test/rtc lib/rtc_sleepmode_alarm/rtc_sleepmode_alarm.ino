/*
  Connections
  -----------
  SDA -> Arduino Analog (SDA pin)
  SCL -> Arduino Analog (SCL pin)
  VCC -> Arduino 5V
  GND -> Arduino GND
  SQW -> Arduino D2 (Needs to be an interrupt capable pin)
*/

#include "RTClib.h"     // DS3231 library
#include <avr/sleep.h>  // AVR library for controlling the sleep modes

const int alarmPin = 2; // The number of the pin for monitoring alarm status on DS3231

RTC_DS3231 rtc;

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

  Serial.println("Starting");
}
void enterSleep() {
  sleep_enable();                       // Enabling sleep mode
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);  // Setting the sleep mode, in this case full sleep

  noInterrupts();                       // Disable interrupts
  attachInterrupt(digitalPinToInterrupt(alarmPin), on_alarm, LOW);

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


void on_alarm() {
  // This runs when SQW pin is low. It will wake up the µController

  sleep_disable(); // Disable sleep mode
  detachInterrupt(digitalPinToInterrupt(alarmPin)); // Detach the interrupt to stop it firing
}
void loop () {

  //delay(10000);  // Wait 10 seconds before going to sleep

  // Get current time and set alarm to a time to wake
  DateTime now = rtc.now();  // Get current time
  Serial.println(now.minute());
  rtc.setAlarm1(DateTime(2021, 3, 10, 22, 31, 0), DS3231_A1_Second); // Or can be set explicity

  enterSleep();  // Go to sleep
}
