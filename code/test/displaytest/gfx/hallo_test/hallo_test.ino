
int i;
#define TFT_PIN_CS   10 // Arduino-Pin an Display CS   
#define TFT_PIN_DC   9  // Arduino-Pin an 
#define TFT_PIN_RST  8  // Arduino Reset-Pin

#include <SPI.h>
#include <Adafruit_GFX.h>    // Adafruit Grafik-Bibliothek
#include <Adafruit_ST7735.h> // Adafruit ST7735-Bibliothek

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_PIN_CS, TFT_PIN_DC, TFT_PIN_RST);  // Display-Bibliothek Setup

void setup() {

  tft.initR(INITR_BLACKTAB);   // ST7735-Chip initialisieren

  tft.setTextWrap(false);
  tft.fillScreen(ST7735_BLACK);

}

void loop() {
  tft.setRotation(1);

  tft.drawFastHLine(0, 30, 160, ST7735_GREEN);

  delay(1000);
  tft.setCursor(13, 67);  // Set position (x,y)
  tft.setTextColor(ST7735_GREEN);
  tft.setTextSize(2);
  tft.print("Hallo");
  delay(1000);
  tft.fillScreen(ST7735_BLACK);



}
