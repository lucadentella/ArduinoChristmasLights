#define PIN_EN    16
#define PIN_IN1   18
#define PIN_IN2   33


void setup() {

  pinMode(PIN_EN, OUTPUT);
  pinMode(PIN_IN1, OUTPUT);
  pinMode(PIN_IN2, OUTPUT);

  // start mode, OFF
  digitalWrite(PIN_IN1, LOW);
  digitalWrite(PIN_IN2, LOW);

  // enable H-Bridge
  digitalWrite(PIN_EN, HIGH);
}

void loop() {

  digitalWrite(PIN_IN1, HIGH);
  digitalWrite(PIN_IN2, LOW);
  delay(1000);
  digitalWrite(PIN_IN1, LOW);
  digitalWrite(PIN_IN2, HIGH);
  delay(1000);
}
