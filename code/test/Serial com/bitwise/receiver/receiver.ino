
// Pin assignments
#define RX_CLOCK 3
#define RX_DATA 4

byte *num = 255;
char message[16];
volatile byte rx_byte = 0;
volatile int bit_position = 0;
volatile bool _update = true;

void setup() {
  pinMode(RX_DATA, INPUT);
  strcpy(message, "");
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(RX_CLOCK), onClockPulse, RISING);

  for (int i = 0; i < 8; i++) {
    Serial.println(num[i]);
  }
}

void onClockPulse() {
  bool rx_bit = digitalRead(RX_DATA);
  Serial.println(rx_bit);
  if (bit_position == 8) {
    rx_byte = 0;
    bit_position = 0;
  }

  if (rx_bit) {
    rx_byte |= (0x80 >> bit_position);
  }

  bit_position += 1;

  if (bit_position == 8) {
    strncat(message, (const char *)&rx_byte, 1);
  }

  _update = true;
}

void loop() {
  if (_update) {
    _update = false;

    Serial.println(message);
    //memset(message, 0, sizeof(message));

  }
}
