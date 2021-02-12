#define TFT_PIN_CS   10 // Arduino-Pin an Display CS   
#define TFT_PIN_DC   9  // Arduino-Pin an 
#define TFT_PIN_RST  8  // Arduino Reset-Pin

#include <SPI.h>
#include <Adafruit_GFX.h>    // Adafruit Grafik-Bibliothek
#include <Adafruit_ST7735.h> // Adafruit ST7735-Bibliothek

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_PIN_CS, TFT_PIN_DC, TFT_PIN_RST);  // Display-Bibliothek Setup

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
int edit;
int start;

//button zuweiungen
int dwn;
int ok;
int page;

//redefinierbare zeiten
int licht;
int essen;


int triggerd;


void setup() {

  //Serial.begin(9600);

  // button setup
  pinMode(in1, INPUT_PULLUP);
  pinMode(in2, INPUT_PULLUP);
  pinMode(in3, INPUT_PULLUP);


  //display setup
  tft.initR(INITR_BLACKTAB);   // ST7735-Chip initialisieren
  tft.fillScreen(ST7735_BLACK);
  tft.setRotation(1);
  tft.setTextSize(1);
  tft.setTextWrap(false);
  tft.setCursor(10, 64);
  tft.print("HUHNER-O-MAT");
  tft.setCursor(10, 84);
  tft.print("V1.0");

  delay(2000);
  tft.fillScreen(ST7735_BLACK);



}

void loop() {

  //Serial.print("edit:");
  //Serial.print(edit);
  //Serial.print("page:");
  //Serial.println(page);
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

    tft.fillScreen(ST7735_BLACK);

    page = page + 1;

  }
  if (start = 0) {

    tft.fillScreen(ST7735_BLACK);
    start = start + 1;

  }
  old2 = btnpage;


  switch (page) {     // seite einstellen

    case 1:   //zweite seite


      tft.setCursor(80, 12);
      tft.print(triggerd);

      tft.setCursor(10, 12);
      tft.print("value1:");

      tft.setCursor(80, 44);
      tft.print(triggerd);

      tft.setCursor(10, 44);
      tft.print("value2:");

      tft.setCursor(80, 76);
      tft.print(triggerd);

      tft.setCursor(10, 76);
      tft.print("value3:");

      tft.setCursor(80, 108);
      tft.print(triggerd);

      tft.setCursor(10, 108);
      tft.print("value4:");

      tft.setCursor(120, 12);
      tft.print("Page:");

      tft.setCursor(150, 12);
      tft.print(page);
      break;



    case 0:    // erste seite

      if (edit > 1) {    //werte bearbeiten begrenzung

        edit = 0;
      }

      if ((btn3 == HIGH) and (btn3 != old3)) {   //flanke um zubearbeitenden wert aus zu wählen

        tft.fillRect(50, 22, 10, 10, ST7735_BLACK);
        edit = edit + 1;

      }
      old3 = btn3;


      switch (edit) {

        case 0:                      // licht anzeit bearbeiten

          if (licht >= 3) {          //lichtzeit begrenzung
  
            tft.fillRect(120, 62, 10, 10, ST7735_BLACK);
            licht = 0;
          }


          if ((up == HIGH) and (old != up)) {

            tft.fillRect(120, 62, 10, 10, ST7735_BLACK);
            licht = licht + 1;
          }

          tft.drawFastHLine(0, 30, 160, ST7735_GREEN);

          tft.setCursor(120, 62);
          tft.print(licht);



          tft.setCursor(120, 94);
          tft.print(essen);


          tft.setTextColor(ST7735_GREEN);

          tft.setCursor(10, 94);
          tft.print("E1. e/t zeit:");

          tft.setCursor(10, 62);
          tft.print("E0. lichtzeit:");

          tft.setCursor(10, 12);
          tft.print("Edit:");


          tft.setTextColor(ST7735_WHITE);



          tft.setCursor(120, 12);
          tft.print("Page:");

          tft.setCursor(150, 12);
          tft.print(page);

          tft.setCursor(50, 12);
          tft.print(edit);
          old = up;

          break;



        case 1:       // essens und trinkens zeit bearbeiten

          if (essen >= 3) {      //essenszeit begrenzng
            
            tft.fillRect(120, 94, 10, 10, ST7735_BLACK);
            essen = 0;
          }


          if ((up == HIGH) and (old != up)) {

            tft.fillRect(120, 94, 10, 10, ST7735_BLACK);
            essen = essen + 1;
          }

          tft.drawFastHLine(0, 30, 160, ST7735_GREEN);


          tft.setCursor(120, 62);
          tft.print(licht);


          tft.setCursor(120, 94);
          tft.print(essen);

          tft.setTextColor(ST7735_GREEN);

          tft.setCursor(10, 94);
          tft.print("E1. e/t zeit:");

          tft.setCursor(10, 62);
          tft.print("E0. lichtzeit:");

          tft.setCursor(10, 22);
          tft.print("Edit:");

          tft.setTextColor(ST7735_WHITE);



          tft.setCursor(120, 22);
          tft.print("Page:");

          tft.setCursor(120, 22);
          tft.print(page);


          tft.setCursor(50, 22);
          tft.print(edit);
          old = up;
          break;

      }
  }
}
