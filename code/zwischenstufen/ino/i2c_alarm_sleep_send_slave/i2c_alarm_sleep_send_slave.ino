#include <lmic.h>
#include <hal/hal.h>
#include <SPI.h>
#include <Wire.h>
#include "RTClib.h"
#include <avr/sleep.h>

static const PROGMEM u1_t NWKSKEY[] = { 0xBA, 0xC2, 0xD6, 0x4E, 0xDE, 0x38, 0x82, 0x06, 0xB6, 0xC7, 0x92, 0x59, 0x21, 0x4A, 0x30, 0xF0 };
static const u1_t PROGMEM APPSKEY[] = { 0xA2, 0xC1, 0x76, 0xD1, 0xAE, 0x25, 0xF9, 0xE0, 0x22, 0x99, 0xC0, 0xEF, 0xC0, 0x01, 0x08, 0x9E };
static const u4_t DEVADDR = 0x26011FDD; // <-- Change this address for every node!
void os_getArtEui (u1_t* buf) { }
void os_getDevEui (u1_t* buf) { }
void os_getDevKey (u1_t* buf) { }
static osjob_t sendjob;

uint8_t received_measurements[3];
unsigned char last_received;
int index = 0;

const int alarmPin = 2;
int statepin = 3;

const lmic_pinmap lmic_pins = {
  .nss = 10,
  .rxtx = LMIC_UNUSED_PIN,
  .rst = 9,
  .dio = {2, 6, 7},
};

void setup() {
  Serial.begin(9600);
  Wire.begin(5);
  Wire.onReceive(on_receiveEvent);
  Serial.println(F("Starting"));

  pinMode(statepin, INPUT_PULLUP);

  Wire.begin(); 

  os_init();
  LMIC_reset();

#ifdef PROGMEM
  uint8_t appskey[sizeof(APPSKEY)];
  uint8_t nwkskey[sizeof(NWKSKEY)];
  memcpy_P(appskey, APPSKEY, sizeof(APPSKEY));
  memcpy_P(nwkskey, NWKSKEY, sizeof(NWKSKEY));
  LMIC_setSession (0x1, DEVADDR, nwkskey, appskey);
#else
  LMIC_setSession (0x1, DEVADDR, NWKSKEY, APPSKEY);
#endif
  LMIC_setupChannel(0, 868100000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
  LMIC_setupChannel(1, 868300000, DR_RANGE_MAP(DR_SF12, DR_SF7B), BAND_CENTI);      // g-band
  LMIC_setupChannel(2, 868500000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
  LMIC_setupChannel(3, 867100000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
  LMIC_setupChannel(4, 867300000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
  LMIC_setupChannel(5, 867500000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
  LMIC_setupChannel(6, 867700000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
  LMIC_setupChannel(7, 867900000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
  LMIC_setupChannel(8, 868800000, DR_RANGE_MAP(DR_FSK,  DR_FSK),  BAND_MILLI);      // g2-band

  LMIC_setLinkCheckMode(0);

  LMIC_setDrTxpow(DR_SF7, 14);

  do_send(&sendjob);

  enter_sleep();
}
void enter_sleep() {
  sleep_enable();                       // Enabling sleep mode
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);  // Setting the sleep mode, in this case full sleep

  noInterrupts();                       // Disable interrupts
  attachInterrupt(digitalPinToInterrupt(alarmPin), on_alarm, RISING);

  Serial.println("Going to sleep!");    // Print message to serial monitor
  Serial.flush();                       // Ensure all characters are sent to the serial monitor

  interrupts();                         // Allow interrupts again
  sleep_cpu();                          // Enter sleep mode

  /* The program will continue from here when it wakes */


  Serial.println("I'm back!");          // Print message to show we're back
}


void on_alarm() {
  sleep_disable();
  detachInterrupt(digitalPinToInterrupt(alarmPin));
  Serial.println("i'm back");
}

void on_receiveEvent(int howMany) {
  while (Wire.available())
  {
    last_received = Wire.read();
    received_measurements[index] = last_received;
    index++;
    Serial.print("receiving: ");
    Serial.println(last_received);
  }
  Serial.println("receiving sens data done, view received_measurements:");
  for (int i = 0; i <= sizeof(received_measurements) - 1; i++) {
    Serial.println(received_measurements[i]);
  }
  index = 0;
  os_setCallback(&sendjob, do_send);
  
}

void onEvent (ev_t ev) {
  Serial.print(os_getTime());
  Serial.print(": ");
  switch (ev) {
    case EV_SCAN_TIMEOUT:
      Serial.println(F("EV_SCAN_TIMEOUT"));
      break;
    case EV_BEACON_FOUND:
      Serial.println(F("EV_BEACON_FOUND"));
      break;
    case EV_BEACON_MISSED:
      Serial.println(F("EV_BEACON_MISSED"));
      break;
    case EV_BEACON_TRACKED:
      Serial.println(F("EV_BEACON_TRACKED"));
      break;
    case EV_JOINING:
      Serial.println(F("EV_JOINING"));
      break;
    case EV_JOINED:
      Serial.println(F("EV_JOINED"));
      break;
    case EV_RFU1:
      Serial.println(F("EV_RFU1"));
      break;
    case EV_JOIN_FAILED:
      Serial.println(F("EV_JOIN_FAILED"));
      break;
    case EV_REJOIN_FAILED:
      Serial.println(F("EV_REJOIN_FAILED"));
      break;
      break;
    case EV_TXCOMPLETE:
      Serial.println(F("EV_TXCOMPLETE (includes waiting for RX windows)"));
      enter_sleep();
      if (LMIC.dataLen) {
        // data received in rx slot after tx
        Serial.print(F("Data Received: "));
        Serial.write(LMIC.frame + LMIC.dataBeg, LMIC.dataLen);
        Serial.println();
      }
      break;
    case EV_LOST_TSYNC:
      Serial.println(F("EV_LOST_TSYNC"));
      break;
    case EV_RESET:
      Serial.println(F("EV_RESET"));
      break;
    case EV_RXCOMPLETE:
      // data received in ping slot
      Serial.println(F("EV_RXCOMPLETE"));
      break;
    case EV_LINK_DEAD:
      Serial.println(F("EV_LINK_DEAD"));
      break;
    case EV_LINK_ALIVE:
      Serial.println(F("EV_LINK_ALIVE"));
      break;
    default:
      Serial.println(F("Unknown event"));
      break;
  }
}

void do_send(osjob_t* j) {
/*
  int _minutes = 57;
  int batVoltage = map(1259, 1100, 1400, 0, 255);
  measurement[0] = _minutes;
  measurement[1] = batVoltage;
  measurement[2] = !digitalRead(statepin);
*/
  if (LMIC.opmode & OP_TXRXPEND) {
    Serial.println(F("OP_TXRXPEND, not sending"));
  } else {
    LMIC_setTxData2(1, (uint8_t*) received_measurements, sizeof(received_measurements), 0);
    Serial.println(F("Packet queued"));
  }

}
void loop() {
  os_runloop_once();
}
