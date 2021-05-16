#include <SPI.h>
#include <SD.h>

const int chipSelect = 10;
const int integer = 125;
String integer_s = "hallo ";
char message[20];

void write_to_log(String content) {
  File outputFile = SD.open("log.txt", FILE_WRITE);

  if (outputFile) {
    Serial.println("writing to log");
    outputFile.seek(EOF);
    outputFile.println(content);
    outputFile.close();
    Serial.println(content);
  }

  else {
    Serial.println("error opening datalog.txt");
  }
}

void setup() {


  Serial.begin(9600);


  while (!Serial);

  Serial.print("Initializing SD card...");

  while (!SD.begin(chipSelect)) {

    Serial.println("initialization failed");

    
  }

  Serial.println("initialization done.");
  write_to_log("hallo"); 
  integer_s.concat(String(integer));
  integer_s.concat(String(integer));
  integer_s.concat(String(integer));
  integer_s.toCharArray(message,20);
  write_to_log(message);
}

void loop() {

}
