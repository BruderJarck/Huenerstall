#include <Wire.h>
#include <avr/sleep.h>

uint8_t received_measurements[2];
unsigned char last_received;
int index = 0;

const int alarmPin = 4; 

void setup() {
  Serial.begin(9600);
  Wire.begin(5);
  Wire.onReceive(on_receiveEvent);
  enter_sleep();
}
void enter_sleep() {
  sleep_enable();                       // Enabling sleep mode
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);  // Setting the sleep mode, in this case full sleep

  noInterrupts();                       // Disable interrupts
  attachInterrupt(digitalPinToInterrupt(alarmPin), on_alarm, LOW);

  Serial.println("Going to sleep!");    // Print message to serial monitor
  Serial.flush();                       // Ensure all characters are sent to the serial monitor

  interrupts();                         // Allow interrupts again
  sleep_cpu();                          // Enter sleep mode

  /* The program will continue from here when it wakes */


  Serial.println("I'm back!");          // Print message to show we're back
}


void on_alarm() {
  sleep_disable(); 
  detachInterrupt(digitalPinToInterrupt(alarmPin));
}

void on_receiveEvent(int howMany) {
  while (Wire.available())
  {
    last_received = Wire.read();
    received_measurements[index] = last_received;
    index++;
    Serial.print("receicing: ");
    Serial.println(last_received);
  }
  Serial.println("sending done, view received_measurements");
  for (int i = 0; i <= sizeof(received_measurements)-1; i++) {
    Serial.println(received_measurements[i]);
    received_measurements[i] = 0;
  }
}
void loop() {}
