float uptime_m = 0;
float uptime_h = 12;

float downtime_m = 0;
float downtime_h = 15;

void setup() {
  Serial.begin(9600);
  for (int i = 0; i <= 12; i++) {
    if (i <= 12 and i >= 7) {
      uptime_h = uptime_h + 0.8;
      downtime_h = downtime_h - 1.2;
    }
    else {
      uptime_h = uptime_h - 0.8;
      downtime_h = downtime_h + 1.2;
    }
    Serial.print(i);
    Serial.print(" ");
    Serial.print(int(uptime_h));
    Serial.print(":");
    Serial.print(int(uptime_m));
    Serial.print("/");
    Serial.print(int(downtime_h));
    Serial.print(":");
    Serial.println(int(downtime_m));
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
