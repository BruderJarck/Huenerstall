bool light = false;

void setup() {
  attachInterrupt(digitalPinToInterrupt(2), on_btn, FALLING);
  pinMode(13, OUTPUT);
}

void on_btn(){
    light = true;
}
void loop() {
  if(light == true){
    digitalWrite(13,HIGH);
    delay(1000);
  digitalWrite(13,LOW);
  light = false;
  }

}
