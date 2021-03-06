String message;
String readin;
String readin2;
char Cmessage[2];
void setup() {
  pinMode(5, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);

  readin = digitalRead(5);
  readin2 = digitalRead(4);
  message = readin + readin2;
  Serial.begin(9600);
  message.toCharArray(Cmessage, message.length() + 1);
  Serial.println(readin);
  Serial.println(readin2);
  Serial.println(message);
  for (int i = 0; i < message.length(); i++) {
    Serial.println(Cmessage[i]);

  }

}

void loop() {
  // put your main code here, to run repeatedly:

}
