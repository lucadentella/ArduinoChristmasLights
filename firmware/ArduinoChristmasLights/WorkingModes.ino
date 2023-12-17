// Method to change workingMode: it takes care of changing the GUI, PINs...
// if updateComboBox is true, it also set the working mode in the combobox (for example when restoring from Preferences)
void changeWorkingMode(bool updateComboBox) {

  switch(workingMode) {

    // Full OFF: disable H-Bridge (EN = 0) and controls
    case MODE_FULLOFF:
      ledcDetachPin(PIN_EN);
      pinMode(PIN_EN, OUTPUT);
      digitalWrite(PIN_EN, LOW);
      ESPUI.setEnabled(sliderBlinkSpeed, false);
      ESPUI.setEnabled(sliderFadeSpeed, false);
      if(updateComboBox) ESPUI.updateSelect(selectMode, "fulloff", 0);
      break;

    // Full ON: blink FAST at 100% brightness and disable controls
    case MODE_FULLON:
      ledcDetachPin(PIN_EN);
      pinMode(PIN_EN, OUTPUT);
      digitalWrite(PIN_EN, HIGH);
      ESPUI.setEnabled(sliderBlinkSpeed, false);
      ESPUI.setEnabled(sliderFadeSpeed, false);
      if(updateComboBox) ESPUI.updateSelect(selectMode, "fullon", 0);
      break;

    // BLINK: blink at 100% brightness and enable blink speed control
    case MODE_BLINK:
      ledcDetachPin(PIN_EN);
      pinMode(PIN_EN, OUTPUT);
      digitalWrite(PIN_EN, HIGH);
      ESPUI.setEnabled(sliderBlinkSpeed, true);
      ESPUI.setEnabled(sliderFadeSpeed, false);
      if(updateComboBox) ESPUI.updateSelect(selectMode, "blink", 0);
      break;

    // FADE: use LEDC to fade the brigtness and enable fade speed control
    case MODE_FADE:
      ledcAttachPin(PIN_EN, LEDC_CHANNEL);
      ESPUI.setEnabled(sliderBlinkSpeed, false);
      ESPUI.setEnabled(sliderFadeSpeed, true);
      if(updateComboBox) ESPUI.updateSelect(selectMode, "fade", 0);
      break;
  }
}

// Method called in the loop() to perform the current workingMode
void doWorkingMode() {

  // Get current time
  now = millis();

  switch(workingMode) {

    // Full OFF: nothing to do
    case MODE_FULLOFF:
      break;

    // Full ON: blink at fixed speed
    case MODE_FULLON:
      if(now - lastUpdate > FULLON_DELAY) {
        outStatus = !outStatus;
        if(outStatus) {
          digitalWrite(PIN_IN1, HIGH);
          digitalWrite(PIN_IN2, LOW);
        } else {
          digitalWrite(PIN_IN1, LOW);
          digitalWrite(PIN_IN2, HIGH);
        }
        lastUpdate = now;
      }
      break;

    // BLINK: blink at set speed
    case MODE_BLINK:
      if(now - lastUpdate > blinkDelay) {
        outStatus = !outStatus;
        if(outStatus) {
          digitalWrite(PIN_IN1, HIGH);
          digitalWrite(PIN_IN2, LOW);
        } else {
          digitalWrite(PIN_IN1, LOW);
          digitalWrite(PIN_IN2, HIGH);
        }
        lastUpdate = now;
      }
      break;

    // FADE: use LEDC to fade the brigtness
    case MODE_FADE:
      if(now - lastUpdate > fadeDelay) {
        if(fadeDirection == FADE_UP) {
          dutyCycle++;
          ledcWrite(LEDC_CHANNEL, gt1[dutyCycle]);
          if(dutyCycle == 255) fadeDirection = FADE_DOWN;
        }
        else {
            dutyCycle--;
          ledcWrite(LEDC_CHANNEL, gt1[dutyCycle]);
          if(dutyCycle == 20) {
            
            fadeDirection = FADE_UP;
            outStatus = !outStatus;
            if(outStatus) {
              digitalWrite(PIN_IN1, HIGH);
              digitalWrite(PIN_IN2, LOW);
            } else {
              digitalWrite(PIN_IN1, LOW);
              digitalWrite(PIN_IN2, HIGH);
            }
          }     
        }
        lastUpdate = now;
      }
      break;
  }  
}

// Methods to update blink and fade speed (use Map() to convert input values)
void setBlinkDelay(int blinkSpeed) {
  blinkDelay = map(blinkSpeed, 0, 100, 1000, 100);
}
void setFadeDelay(int fadeSpeed) {
  fadeDelay = map(fadeSpeed, 0, 100, 50, 1);
}