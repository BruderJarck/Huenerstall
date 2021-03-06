#include <Wire.h>
#include "RTClib.h"

DS3231 rtc;

bool stopper = false;
byte readin;
byte readin2;
unsigned char *message[3];

int pin = 5;
int pin2 = 6;

#define TX_RATE 1000
#define TX_CLOCK 3
#define TX_DATA 4

void setup() {
  Wire.begin();
  rtc.begin();
  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  pinMode(pin, INPUT_PULLUP);
  pinMode(pin2, INPUT_PULLUP);
  pinMode(TX_CLOCK, OUTPUT);
  pinMode(TX_DATA, OUTPUT);
  Serial.begin(9600);

}

void loop() {

  DateTime now = rtc.now();
  if (now.second() == 0 and stopper == false) {
    stopper = true;
    readin = digitalRead(pin);
    readin2 = digitalRead(pin2);
    message[0] = readin;
    message[1] = readin2;
    message[2] = 125;
    for (int byte_idx = 0; byte_idx < sizeof(message); byte_idx++) {
      char tx_byte = message[byte_idx];
      Serial.println(tx_byte, BIN);

      for (int bit_idx = 0; bit_idx < 8; bit_idx++) {
        bool tx_bit = tx_byte & (0x80 >> bit_idx);

        digitalWrite(TX_DATA, tx_bit);
        delay((1000 / TX_RATE) / 2);

        //Serial.print(tx_bit ? "1" : "0");;

        // Pulse clock
        digitalWrite(TX_CLOCK, HIGH);
        delay((1000 / TX_RATE) / 2);
        digitalWrite(TX_CLOCK, LOW);
      }
    }
    digitalWrite(TX_DATA, LOW);

  }
  else if(now.second() == 30){
    stopper = false;
  }
  else {
    Serial.print(now.second());
    Serial.println(" else");
  }
}
