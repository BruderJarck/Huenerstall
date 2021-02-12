int bt1;
int bt2;
int bt3;
void setup() {
  pinMode(A0, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);
  pinMode(A3, INPUT_PULLUP);
  pinMode(13, OUTPUT);
}

void loop() {
  bt1 = !digitalRead(A0);
  bt2 = !digitalRead(A1);
  bt3 = !digitalRead(A3);
  
  if((bt1)or(bt2)or(bt3) == HIGH){
  digitalWrite(13, HIGH);
}
else{
  digitalWrite(13,LOW);
}
}
