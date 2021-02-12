#include <SPI.h>
#include "Ucglib.h"

int in1 = 7;
int in2 = 6;
int triggerd = 0;
int old;
int btn1;
int page = 0;
int old2;
int btn2;

Ucglib_ST7735_18x128x160_SWSPI ucg(/*sclk=*/ 13, /*data=*/ 4, /*cd=*/ 9, /*cs=*/ 10, /*reset=*/ 8);

void setup() {
  Serial.begin(9600);
  pinMode(in1, INPUT_PULLUP);
  pinMode(in2, INPUT_PULLUP);

  delay(1000);
  ucg.begin(UCG_FONT_MODE_TRANSPARENT);
  ucg.setRotate90();
  ucg.setFont(ucg_font_ncenR12_tr);
  ucg.setColor(255, 255, 255);
}

void loop() {
  Serial.println(triggerd);
  btn1 = !digitalRead(in1);
  btn2 = !digitalRead(in2);

  if(triggerd > 5){

    triggerd = 0;
  }

  if((btn1 == HIGH) and (old != btn1)){
    
    ucg.clearScreen();
    triggerd = triggerd + 1;
   
    
  }
  
  old = btn1;
  

  if(page > 1){

    page = 0;
  }

  
  if((btn2 == HIGH) and (old2 != btn2)){
    
    ucg.clearScreen();
    page = page + 1;
 
   }
  
  old2 = btn2;
  

switch(page){

  case 0:
    ucg.setPrintPos(80, 22);
    ucg.print(triggerd);
    ucg.setPrintPos(10, 22);
    ucg.print("value1:");
    ucg.setPrintPos(80, 54);
    ucg.print(triggerd);
    ucg.setPrintPos(10, 54);
    ucg.print("value2:");
    ucg.setPrintPos(80, 86);
    ucg.print(triggerd);
    ucg.setPrintPos(10, 86);
    ucg.print("value3:");
    ucg.setPrintPos(80, 118);
    ucg.print(triggerd);
    ucg.setPrintPos(10, 118);
    ucg.print("value4:");
    ucg.setPrintPos(150, 22);    
    ucg.print(page);
    break;
    

    
  case 1:
  
    ucg.setPrintPos(80, 22);
    ucg.print(triggerd);
    ucg.setPrintPos(10, 22);
    ucg.print("value5:");
    ucg.setPrintPos(80, 54);
    ucg.print(triggerd);
    ucg.setPrintPos(10, 54);
    ucg.print("value6:");
    ucg.setPrintPos(80, 86);
    ucg.print(triggerd);
    ucg.setPrintPos(10, 86);
    ucg.print("value7:");
    ucg.setPrintPos(80, 118);
    ucg.print(triggerd);
    ucg.setPrintPos(10, 118);
    ucg.print("value8:");
    ucg.setPrintPos(150, 22);    
    ucg.print(page);
    break;
    
  }
}
