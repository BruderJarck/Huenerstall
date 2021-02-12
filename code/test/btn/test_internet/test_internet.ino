const int kPinBtn = A0;  // Push-Button connected to Analog pin A0
const int kPinLED = 13;  // LED connected to to Digital Pin 13

void setup()
{
  pinMode(kPinBtn, OUTPUT); // Generally, in push-button we take INPUT as a parameter but here we take OUTPUT because ANALOG PIN 

  digitalWrite(kPinBtn, HIGH); // Make button condition HIGH

  pinMode(kPinLED, OUTPUT);
}

void loop()
{
  // Now, normal push-button operation, LED blink when we press push button

  if(digitalRead(kPinBtn) == LOW)  // If button pressed
  {
    digitalWrite(kPinLED, HIGH);   // Blink LED
  }
  else digitalWrite(kPinLED, LOW); // Else LED is off
}
