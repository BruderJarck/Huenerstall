
// include TFT and SPI libraries
#include <TFT.h>
#include <SPI.h>

// pin definition for Arduino UNO
#define cs   10
#define dc   9
#define rst  8


// create an instance of the library
TFT TFTscreen = TFT(cs, dc, rst);

void setup() {

  //initialize the library
  TFTscreen.begin();

  // clear the screen with a black background
  TFTscreen.background(0, 0, 0);
  //set the text size
  TFTscreen.setTextSize(2);
  Serial.begin(9600);
}

void loop() {


  for (int i = 0; i < 4; i++) {
    
    TFTscreen.stroke(255, 255, 255);
    Serial.print(i);
    TFTscreen.text("I:", 6, 57);
    TFTscreen.text(i, 6, 80);

  }
}
