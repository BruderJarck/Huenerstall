

#define TFT_PIN_CS   10 // Arduino-Pin an Display CS   
#define TFT_PIN_DC   9  // Arduino-Pin an 
#define TFT_PIN_RST  8  // Arduino Reset-Pin

#include <SPI.h>
#include <Adafruit_GFX.h>    // Adafruit Grafik-Bibliothek
#include <Adafruit_ST7735.h> // Adafruit ST7735-Bibliothek

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_PIN_CS, TFT_PIN_DC, TFT_PIN_RST);  // Display-Bibliothek Setup

void setup(void) {

  
  
  tft.initR(INITR_BLACKTAB);   // ST7735-Chip initialisieren

}

void loop() {

  // Bildschirm mit Farbe fuellen
  // fillScreen(farbe);
  tft.fillScreen(ST7735_BLACK);

  delay(2000); // 2 Sekunden warten
  
  // Fontgroesse setzen
  // setTextSize(groesse);
  tft.setTextSize(2);
  
  // Schrift umbrechen?
  // setTextWrap(true);   true=Ja, false=Nein
  tft.setTextWrap(true); 
  
  // Textposition setzen
  // setCursor(x,y);
  tft.setCursor(24,4);
 
  // Textfarbe setzen
  // setTextColor(farbe);
  tft.setTextColor(ST7735_WHITE);
  
  // Text ausgeben
  // print(text);
  tft.print("Hallo !");

  delay(2000); // 2 Sekunden warten
  
  // Linie zeichnen
  // drawLine(x_start,y_start,x_ende,y_ende,farbe);
  tft.drawLine(10,24,118,24,ST7735_GREEN);

  delay(2000); // 2 Sekunden warten
    
  // Ein Rechteck zeichnen 
  // drawRect(x_oben_links,y_oben_links,weite,hoehe,farbe);
  tft.drawRect(4,35,120,20,ST7735_RED); 
  
  delay(2000); // 2 Sekunden warten

  // Ein gefuelltes Rechteck zeichnen 
  // drawRect(x_oben_links,y_oben_links,weite,hoehe,farbe);
  tft.fillRect(10,40,108,10,ST7735_YELLOW);

  delay(2000); // 2 Sekunden warten

  // Ein Rechteck zeichnen 
  // drawRoundRect(x_oben_links,y_oben_links,weite,hoehe,rundung,farbe);
  tft.drawRoundRect(4,65,120,20,5,ST7735_MAGENTA); 
  
  delay(2000);
  
  // Einen Kreis zeichnen 
  // drawCircle(x_oben_links,y_oben_links,radius,farbe);
  tft.drawCircle(64,115, 20, ST7735_CYAN);
  
  delay(2000); // 2 Sekunden warten
  
  // Einen gefuellten Kreis zeichnen 
  // fillCircle(x_oben_links,y_oben_links,radius,farbe);
  tft.fillCircle(64,115, 10, ST7735_BLUE);
  
  delay(2000); // 2 Sekunden warten

  // Neue Fontgroesse setzen
  // setTextSize(groesse);
  tft.setTextSize(1);
  
  // Neue Textfarbe setzen
  // setTextColor(farbe);
  tft.setTextColor(ST7735_GREEN);
  
  // Neue Textposition setzen
  // setCursor(x,y);
  tft.setCursor(14,147);
  
  // Text ausgeben
  // print(text);
  tft.print("blog.simtronyx.de");
  
  delay(8000); // 8 Sekunden warten
  
  // Gesamtes Display invertieren?
  // invertDisplay(true);   true=Ja, false=Nein
  tft.invertDisplay(true);
  
  delay(1000); // 1 Sekunde warten
  
  // Gesamtes Display invertieren?
  // invertDisplay(false);   true=Ja, false=Nein
  tft.invertDisplay(false);

  delay(1000); // 1 Sekunde warten
}
