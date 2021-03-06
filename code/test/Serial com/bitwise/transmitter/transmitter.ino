
// Transmit rate in bps
#define TX_RATE 1000

// Pin assignments
#define TX_CLOCK 3
#define TX_DATA 4

const char *message = "1256,1,12";

void setup() {
  pinMode(TX_CLOCK, OUTPUT);
  pinMode(TX_DATA, OUTPUT);
  Serial.begin(9600);

  for (int byte_idx = 0; byte_idx < strlen(message); byte_idx++) {
    char tx_byte = message[byte_idx];

    for (int bit_idx = 0; bit_idx < 8; bit_idx++) {
      bool tx_bit = tx_byte & (0x80 >> bit_idx);

      digitalWrite(TX_DATA, tx_bit);
      delay((1000 / TX_RATE) / 2);

      Serial.println(tx_bit ? "1" : "0");;

      // Pulse clock
      digitalWrite(TX_CLOCK, HIGH);
      delay((1000 / TX_RATE) / 2);
      digitalWrite(TX_CLOCK, LOW);
    }
  }
  digitalWrite(TX_DATA, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:

}
