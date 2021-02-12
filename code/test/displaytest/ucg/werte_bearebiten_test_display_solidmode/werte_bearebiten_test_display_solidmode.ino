#include <SPI.h>      //spi lib
#include "Ucglib.h"   //display lib


// pin zuweisung
int in1 = 7;
int in2 = 6;
int in3 = 5;

// old fur flanke
int old;
int old2;
int old3;

//button pins
int up;
int btnpage;
int btn3;

//zustaende
int wasserlvl;
int futterlvl;
int huehner;
int change;
int start;

//button zuweiungen
int dwn;
int ok;
int page;

//redeninierbare zeiten
int licht;
int essen;


int triggerd;

Ucglib_ST7735_18x128x160_SWSPI ucg(/*sclk=*/ 13, /*data=*/ 4, /*cd=*/ 9, /*cs=*/ 10, /*reset=*/ 8);

void setup() {

  Serial.begin(9600);

  // button setup
  pinMode(in1, INPUT_PULLUP);
  pinMode(in2, INPUT_PULLUP);
  pinMode(in3, INPUT_PULLUP);


  //display setup
  ucg.begin(UCG_FONT_MODE_SOLID);
  ucg.setRotate90();
  ucg.setFont(ucg_font_ncenR12_tr);
  ucg.clearScreen();

  ucg.setColor(0, 255, 150);
  ucg.setPrintPos(10, 64);
  ucg.print("HUHNER-O-MAT");
  ucg.setPrintPos(10, 84);
  ucg.print("V1.0");

  delay(2000);
  ucg.clearScreen();
  ucg.setColor(255, 255, 255);


}

void loop() {

  Serial.print("change:");
  Serial.print(change);
  Serial.print("page:");
  Serial.println(page);
  up = !digitalRead(in1);
  btnpage = !digitalRead(in2);
  btn3 = !digitalRead(in3);

  if (triggerd > 5) {

    triggerd = 0;
  }


  if (page > 1) {

    page = 0;
  }


  if ((btnpage == HIGH) and (old2 != btnpage)) {

    page = page + 1;

  }
  if (start = 0) {
    ucg.clearScreen();
    start = start + 1;

  }
  old2 = btnpage;


  switch (page) {     // seite einstellen

    case 1:   //erste seite

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
      ucg.setPrintPos(105, 22);
      ucg.print("Page:");
      ucg.setPrintPos(150, 22);
      ucg.print(page);
      break;



    case 0:    // zweite seite

      if (change > 1) {    //werte bearbeiten begrenzung

        ucg.clearScreen();
        change = 0;
      }

      if ((btn3 == HIGH) and (btn3 != old3)) {   //flanke um zubearbeitenden wert aus zu wählen

        ucg.clearScreen();
        change = change + 1;
      }
      old3 = btn3;


      switch (change) {

        case 0:                      // licht anzeit bearbeiten

          if (licht == 3) {          //lichtzeit begrenzung

            ucg.clearScreen();
            licht = 0;
          }


          if ((up == HIGH) and (old != up)) {

            licht = licht + 1;
            ucg.clearScreen();
          }

          ucg.drawHLine(0, 30, 160);

          ucg.setPrintPos(120, 62);
          ucg.print(licht);


          ucg.setPrintPos(120, 94);
          ucg.print(essen);

          ucg.setColor(0, 255, 150);
          ucg.setPrintPos(10, 94);
          ucg.print("E1. e/t zeit:");
          ucg.setPrintPos(10, 62);
          ucg.print("E0. lichtzeit:");
          ucg.setPrintPos(10, 22);
          ucg.print("Edit:");

          ucg.setColor(255, 255, 255);


          ucg.setPrintPos(70, 22);
          ucg.print("Page:");
          ucg.setPrintPos(120, 22);
          ucg.print(page);

          ucg.setPrintPos(50, 22);
          ucg.print(change);
          old = up;
          break;



        case 1:       // essens und trinkens zeit bearbeiten

          if (essen == 3) {      //essenszeit begrenzng

            ucg.clearScreen();
            essen = 0;
          }


          if ((up == HIGH) and (old != up)) {

            essen = essen + 1;
            ucg.clearScreen();
          }

          ucg.drawHLine(0, 30, 160);

          ucg.setPrintPos(120, 62);
          ucg.print(licht);


          ucg.setPrintPos(120, 94);
          ucg.print(essen);

          ucg.setColor(0, 255, 150);
          ucg.setPrintPos(10, 94);
          ucg.print("E1. e/t zeit:");
          ucg.setPrintPos(10, 62);
          ucg.print("E0. lichtzeit:");
          ucg.setPrintPos(10, 22);
          ucg.print("Edit:");

          ucg.setColor(255, 255, 255);


          ucg.setPrintPos(70, 22);
          ucg.print("Page:");
          ucg.setPrintPos(120, 22);
          ucg.print(page);

          ucg.setPrintPos(50, 22);
          ucg.print(change);
          old = up;
          break;

      }
  }
}
