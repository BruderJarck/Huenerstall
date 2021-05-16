#include <lmic.h>
#include <hal/hal.h>
#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include "RTClib.h"
#include <avr/sleep.h>

static const PROGMEM u1_t NWKSKEY[] = { 0xBA, 0xC2, 0xD6, 0x4E, 0xDE, 0x38, 0x82, 0x06, 0xB6, 0xC7, 0x92, 0x59, 0x21, 0x4A, 0x30, 0xF0 };
static const u1_t PROGMEM APPSKEY[] = { 0xA2, 0xC1, 0x76, 0xD1, 0xAE, 0x25, 0xF9, 0xE0, 0x22, 0x99, 0xC0, 0xEF, 0xC0, 0x01, 0x08, 0x9E };
static const u4_t DEVADDR = 0x26011FDD; //Change this address for every node!
void os_getArtEui (u1_t* buf) { }
void os_getDevEui (u1_t* buf) { }
void os_getDevKey (u1_t* buf) { }
static osjob_t sendjob;

char received_measurements[20];
unsigned char last_received;
int index = 0;

const int alarmPin = 2;
int statepin = 3;

String DATALOG = "log.txt";

const lmic_pinmap lmic_pins = {
  .nss = 10,
  .rxtx = LMIC_UNUSED_PIN,
  .rst = 9,
  .dio = {2, 6, 7},
};

void setup() {
  write_to_log("11Starting", 9, false);
  Serial.begin(9600);
  Wire.begin(5);
  Wire.onReceive(on_receiveEvent);
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
}

void on_receiveEvent(int howMany) {
  for (int i = 0; i <= howMany; i++)
  {
    last_received = Wire.read();
    received_measurements[i] = last_received;
    Serial.print("receiving[");
    Serial.print(i);
    Serial.print("]: ");
    Serial.println(received_measurements[i]);
  }
  Serial.println("receiving sens data done");

  if (int(received_measurements[0]) == 0) {
    Serial.println("lora send");
    write_to_log(received_measurements, sizeof(received_measurements), true);
    memset(received_measurements, "", sizeof(received_measurements));
  }

  else if (int(received_measurements[0] == 1)) {
    Serial.println("log");
    write_to_log(received_measurements, sizeof(received_measurements), false);
    memset(received_measurements, "", sizeof(received_measurements));
  }
  else {
    Serial.println("undefined");
    write_to_log("11undefined log bool", 20, false);
  }
}


void onEvent (ev_t ev) {
  Serial.print(os_getTime());
  Serial.print(": ");
  switch (ev) {
    case EV_SCAN_TIMEOUT:
      Serial.println(F("EV_SCAN_TIMEOUT"));
      write_to_log("11EV_SCAN_TIMEOUT", sizeof("11EV_SCAN_TIMEOUT"), false);
      break;

    case EV_BEACON_FOUND:
      Serial.println(F("EV_BEACON_FOUND"));
      write_to_log("11EV_BEACON_FOUND", sizeof("11EV_BEACON_FOUND"), false);
      break;

    case EV_BEACON_MISSED:
      Serial.println(F("EV_BEACON_MISSED"));
      write_to_log("11EV_BEACON_MISSED", sizeof("11EV_BEACON_MISSED"), false);
      break;

    case EV_BEACON_TRACKED:
      Serial.println(F("EV_BEACON_TRACKED"));
      write_to_log("11EV_BEACON_TRACKED", sizeof("11EV_BEACON_TRACKED"), false);
      break;

    case EV_JOINING:
      Serial.println(F("EV_JOINING"));
      write_to_log("11EV_JOINING", sizeof("11EV_JOINING"), false);
      break;

    case EV_JOINED:
      Serial.println(F("EV_JOINED"));
      write_to_log("11EV_JOINED", sizeof("11EV_JOINED"), false);
      break;

    case EV_RFU1:
      Serial.println(F("EV_RFU1"));
      write_to_log("11EV_RFU1", sizeof("11EV_RFU1"), false);
      break;

    case EV_JOIN_FAILED:
      Serial.println(F("EV_JOIN_FAILED"));
      write_to_log("11EV_JOIN_FAILED", sizeof("11EV_JOIN_FAILED"), false);
      break;

    case EV_REJOIN_FAILED:
      Serial.println(F("EV_REJOIN_FAILED"));
      write_to_log("11EV_REJOIN_FAILED", sizeof("11EV_REJOIN_FAILED"), false);
      break;

    case EV_TXCOMPLETE:
      Serial.println(F("EV_TXCOMPLETE (includes waiting for RX windows)"));
      //enter_sleep();
      if (LMIC.dataLen) {
        // data received in rx slot after tx
        Serial.print(F("Data Received: "));
        Serial.write(LMIC.frame + LMIC.dataBeg, LMIC.dataLen);
        Serial.println();
        write_to_log("11EV_TXCOMPLETE", sizeof("11EV_TXCOMPLETE"), false);
      }
      break;

    case EV_LOST_TSYNC:
      Serial.println(F("EV_LOST_TSYNC"));
      write_to_log("11EV_LOST_TSYNC", sizeof("11EV_LOST_TSYNC"), false);
      break;

    case EV_RESET:
      Serial.println(F("EV_RESET"));
      write_to_log("11EV_RESET", sizeof("11EV_RESET"), false);
      break;

    case EV_RXCOMPLETE:
      // data received in ping slot
      Serial.println(F("EV_RXCOMPLETE"));
      write_to_log("11EV_RXCOMPLETE", sizeof("11EV_RXCOMPLETE"), false);
      break;

    case EV_LINK_DEAD:
      Serial.println(F("EV_LINK_DEAD"));
      write_to_log("11EV_LINK_DEAD", sizeof("11EV_LINK_DEAD"), false);
      break;

    case EV_LINK_ALIVE:
      Serial.println(F("EV_LINK_ALIVE"));
      write_to_log("11EV_LINK_ALIVE", sizeof("11EV_LINK_ALIVE"), false);
      break;

    default:
      Serial.println(F("Unknown event"));
      write_to_log("11Unknown event", sizeof("11Unknown event"), false);
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
    write_to_log("11OP_TXRXPEND, not sending", sizeof("11OP_TXRXPEND, not sending"), false);

  } else {
    LMIC_setTxData2(1, (uint8_t*) received_measurements, sizeof(received_measurements), 0);
    Serial.println(F("Packet queued"));
    write_to_log("11Packet queued", sizeof("Packet queued"), false);
  }
}

void write_to_log(char content[], int _sizeof, bool data) {
  File outputFile = SD.open("log_data.txt", FILE_WRITE);

  if (outputFile) {
    outputFile.seek(EOF);

    for (int i = 1; i <= _sizeof; i++) {

      if (data) {
        switch (i) {
          case 1:
            outputFile.print("device: 0 ");
          case 2:
            outputFile.print("doorstate: ");
            break;
          case 3:
            outputFile.print("voltage: ");
            break;
          case 6:
            outputFile.print("uptime:");
            break;
          case 7:
            outputFile.print("time: ");
            break;
        }
        outputFile.print(content[i]);
        outputFile.print(" ");
      }
      else {
        if (i == 1) {
          outputFile.print("device: ");
          outputFile.print(int(content[1]));
          outputFile.print(" ");
        }
        else {
          outputFile.print(content[i]);
        }
      }
      //Serial.print(content[i]);
    }
    outputFile.println(" ");
    //Serial.println("");
    Serial.println("writing to log");
    outputFile.close();
  }

  else {
    Serial.println("error opening datalog.txt");
  }
}
void loop() {
  os_runloop_once();
}
