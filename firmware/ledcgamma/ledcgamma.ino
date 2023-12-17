#include "gamma.h"
GAMMA gt1(256);

#define PIN_EN    16
#define PIN_IN1   18
#define PIN_IN2   33

#define PWM_FREQUENCY   5000
#define PWM_RESOLUTION  8
#define LEDC_CHANNEL    0

void setup() {

  pinMode(PIN_IN1, OUTPUT);
  pinMode(PIN_IN2, OUTPUT);

  // start mode
  digitalWrite(PIN_IN1, HIGH);
  digitalWrite(PIN_IN2, LOW);

  // LEDC
  ledcSetup(LEDC_CHANNEL, PWM_FREQUENCY, PWM_RESOLUTION);
  ledcAttachPin(PIN_EN, LEDC_CHANNEL);

  // GAMMA
  gt1.begin();
  gt1.setGamma(2.8);
}

void loop() {

   ledcWrite(LEDC_CHANNEL, gt1[50]);
   delay(1000);
   ledcWrite(LEDC_CHANNEL, gt1[100]);
   delay(1000);
   ledcWrite(LEDC_CHANNEL, gt1[200]);
   delay(1000);
}
