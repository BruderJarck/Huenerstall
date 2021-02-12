

#define TFT_PIN_CS   10 // Arduino-Pin an Display CS   
#define TFT_PIN_DC   9  // Arduino-Pin an 
#define TFT_PIN_RST  8  // Arduino Reset-Pin

#include <SPI.h>
#include <Adafruit_GFX.h>    // Adafruit Grafik-Bibliothek
#include <Adafruit_ST7735.h> // Adafruit ST7735-Bibliothek

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_PIN_CS, TFT_PIN_DC, TFT_PIN_RST);

int senspin = A7;
int sensor;
void setup() {
  Serial.begin(9600);
  pinMode(12, INPUT);
  tft.initR(INITR_BLACKTAB);   // ST7735-Chip initialisieren
  tft.setTextSize(2);
  tft.fillScreen(ST7735_BLACK);
  tft.setTextColor(ST7735_WHITE);
  tft.setTextWrap(true);



}

void loop() {
  sensor = analogRead(senspin);
  if (sensor < 300) {

    tft.setCursor(20, 20);
    tft.fillRect(20, 20, 100, 50, 0x0000);
    tft.print("tag");
    delay(100);


  }
  else {
    tft.setCursor(20, 20);
    tft.fillRect(20, 20, 100, 50, 0x0000);
    tft.print("nacht");
    delay(100);
  }
}
