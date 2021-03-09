#include <Wire.h>

void setup(){
  Serial.begin(9600);
  Wire.begin(5);
  Wire.onReceive(receiveEvent);
}

void receiveEvent(int howMany){
  while(Wire.available())
  {
    Serial.println(Wire.read());
  }
}
void loop(){}
