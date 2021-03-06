#include <Wire.h>

void setup(){
  Serial.begin(9600);
  Wire.begin(5);
  Wire.onReceive(receiveEvent);
  pinMode(13,OUTPUT); 
  digitalWrite(13,LOW); // Bord-LED
}

void receiveEvent(int howMany){
  while(Wire.available())
  {
    char c = Wire.read();
    Serial.println(c);
  }
}
