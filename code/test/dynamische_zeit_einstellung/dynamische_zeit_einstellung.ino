float uptime_m = 0;
float uptime_h = 12;

float downtime_m = 0;
float downtime_h = 15;

bool btn;
int _month = 5;
int old_month = 5;

void setup() {
  pinMode(5, INPUT_PULLUP);
  Serial.begin(9600);
  for (int i = 1; i <= 12; i++) {
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
    if (i == 5) {
      break;
    }
  }
}

void loop() {
  btn = !digitalRead(5);
  if (btn) {
    if (_month >= 12) {
      _month = 0;
    }
    _month++;
    Serial.print("new month: ");
    Serial.println(_month);
    delay(500);
  }
  if (old_month != _month) {
    if (_month <= 12 and _month >= 7) {
      uptime_h = uptime_h + 0.8;
      downtime_h = downtime_h - 1.2;
    }
    else {
      uptime_h = uptime_h - 0.8;
      downtime_h = downtime_h + 1.2;
    }
    Serial.print(int(uptime_h));
    Serial.print(":");
    Serial.print(int(uptime_m));
    Serial.print("/");
    Serial.print(int(downtime_h));
    Serial.print(":");
    Serial.println(int(downtime_m));
    old_month = _month ;
  }
}
