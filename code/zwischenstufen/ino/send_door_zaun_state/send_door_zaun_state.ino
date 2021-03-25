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

int uptimeH = 7;   //oclock
int uptimeM = 0   ;   //minutes
int downtimeH = 19; //oclock
int downtimeM = 0; //minutes

bool send_bt;
bool door_btn;
bool zaun_btn;
bool end_btn ;
int downtraveltime = 1200; //ms
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
  attachInterrupt(digitalPinToInterrupt(send_bt_pin), on_alarm, RISING);

  digitalWrite(wake_slave_pin, LOW);

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    abort();
  }

  // If required set time+
  up();
  down();
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
  attachInterrupt(digitalPinToInterrupt(wake_pin), on_alarm, LOW);

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
  detachInterrupt(digitalPinToInterrupt(wake_pin)); // Detach the interrupt to stop it firing
  interrupt_triggered = true;
}

void do_send() {

  voltage = map(analogRead(voltage_pin), 0, 1023, 0, 218);
  //door_state = !digitalRead(door_pin);
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
  interrupt_triggered = false;
}


void loop () {

  DateTime now = rtc.now();
  rtc.setAlarm1(DateTime(2021, 3, 06, uptimeH, uptimeM, 30), DS3231_A1_Hour);
  rtc.setAlarm2(DateTime(2021, 3, 06, downtimeH, downtimeM, 0), DS3231_A2_Hour);

  door_btn = !digitalRead(door_btn_pin);
  zaun_btn = !digitalRead(zaun_btn_pin);

  if (interrupt_triggered == true) {
    Serial.println("alarm triggered");
    if (door_btn == HIGH) {
      Serial.println("door btn");
      if (door_state == true) {
        down();
      }
      else {
        up();
      }
    }
    else if (zaun_btn == HIGH) {
      if (zaun_state == false) {
        zaun(true);
        Serial.println("set zaunstate true");

      }
      else {
        zaun(false);
        Serial.println("set zaunstate false");

      }
    }
    else {
      Serial.println("Alarm");
      if ((now.hour() >= uptimeH) and (now.hour() < downtimeH) and (door_state == false)) { // wenn die tür zu ist wenn sie laut alarm erst zu gehen soll, könnte man das als indikator für eine fehlfunktion benutzen => error code senden
        up();
        zaun(true);
      }
      else {
        if (door_state == true) { // wenn die tür zu ist wenn sie laut alarm erst zu gehen soll, könnte man das als indikator für eine fehlfunktion benutzen => error code senden

          down();
          zaun(false);
        }
      }
    }
    do_send();
  }
  else {
    enterSleep();
  }
}
