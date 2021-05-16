#include <SPI.h>
#include <SD.h>
#include <Wire.h>

char received_measurements[20];
char last_received;

void setup() {
  Serial.begin(9600);
  Wire.begin(5);
  Wire.onReceive(on_receiveEvent);
  Serial.print("Initializing SD card...");

  while (!SD.begin(10)) {
    Serial.println("initialization failed");
  }
  Serial.println("initialization done.");
  write_to_log("11hallo", 7, false);
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
        else{
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
}
