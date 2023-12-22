// Change the workingMode
void selectModeCallback(Control* sender, int value) {

  // blink mode
  if((sender->value).equals(String("blink"))) {
    workingMode = MODE_BLINK;
    changeWorkingMode(false);
  }
  
  // fade mode
  else if((sender->value).equals(String("fade"))) {
    workingMode = MODE_FADE;
    changeWorkingMode(false);
  }

  // Full ON mode
  else if((sender->value).equals(String("fullon"))) {
    workingMode = MODE_FULLON;
    changeWorkingMode(false);
  }

  // Full OFF mode
  else if((sender->value).equals(String("fulloff"))) {
    workingMode = MODE_FULLOFF;
    changeWorkingMode(false);
  }

  // Save new workingMode
  preferences.putInt("working-mode", workingMode);
}

// Change sliders values
void sliderBlinkCallback(Control* sender, int type) {

  int newBlinkSpeed = (sender->value).toInt();
  preferences.putInt("blink-speed", newBlinkSpeed);
  setBlinkDelay(newBlinkSpeed);
}

void sliderFadeCallback(Control* sender, int type) {

  int newFadeSpeed = (sender->value).toInt();
  preferences.putInt("fade-speed", newFadeSpeed);
  setFadeDelay(newFadeSpeed);
}

// Push reset button

void buttonResetCallback(Control* sender, int type) {
  
  Serial.println("Reset triggered");
  preferences.putInt("working-mode", MODE_BLINK);
  preferences.putInt("blink-speed", DEFAULT_BLINK_SPEED);
  preferences.putInt("fade-speed", DEFAULT_FADE_SPEED);
  preferences.end();
  wifiManager.resetSettings();
  ESP.restart();
}