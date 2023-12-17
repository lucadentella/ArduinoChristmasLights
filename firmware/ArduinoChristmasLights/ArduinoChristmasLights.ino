// Include header file
#include "ArduinoChristmasLights.h"

void setup() {

  // Serial for debug
  Serial.begin(115200);

  // Run WifiManager
  wifiManager.autoConnect(AP_NAME, AP_PASSWORD);
  Serial.print("Connected to ");
  Serial.println(wifiManager.getWiFiSSID());

  // Preferences library
  preferences.begin("asl", false);

  // ledc peripheral
  ledcSetup(LEDC_CHANNEL, PWM_FREQUENCY, PWM_RESOLUTION);

  // GAMMA library
  gt1.begin();
  gt1.setGamma(2.8);

  // Pins
  pinMode(PIN_IN1, OUTPUT);
  pinMode(PIN_IN2, OUTPUT);

  // Starting values, from saved Preferences or, if not found, from default values
  workingMode = preferences.getInt("working-mode", MODE_BLINK);
  int blinkSpeed = preferences.getInt("blink-speed", DEFAULT_BLINK_SPEED);
  int fadeSpeed = preferences.getInt("fade-speed", DEFAULT_FADE_SPEED);
  Serial.print("Working mode: "); Serial.println(workingMode);
  Serial.print("Blink speed: "); Serial.println(blinkSpeed);
  Serial.print("Fade speed: "); Serial.println(fadeSpeed);
  setBlinkDelay(blinkSpeed);
  setFadeDelay(fadeSpeed);

  // Build Web interface
  tab1 = ESPUI.addControl(ControlType::Tab, "Settings", "Settings");
  selectMode = ESPUI.addControl(ControlType::Select, "Mode", "blink", ControlColor::None, tab1, &selectModeCallback);
  ESPUI.addControl(ControlType::Option, "Blink", "blink", ControlColor::None, selectMode);
  ESPUI.addControl(ControlType::Option, "Fade", "fade", ControlColor::None, selectMode);
  ESPUI.addControl(ControlType::Option, "Full ON", "fullon", ControlColor::None, selectMode);
  ESPUI.addControl(ControlType::Option, "Full OFF", "fulloff", ControlColor::None, selectMode);  
  sliderBlinkSpeed = ESPUI.addControl(ControlType::Slider, "Blink speed", String(blinkSpeed), ControlColor::None, tab1, &sliderBlinkCallback);
  sliderFadeSpeed = ESPUI.addControl(ControlType::Slider, "Fade speed", String(fadeSpeed), ControlColor::None, tab1, &sliderFadeCallback);
  buttonReset = ESPUI.addControl(ControlType::Button, "RESET", "RESET", ControlColor::None, tab1, &buttonResetCallback); 
  ESPUI.begin("ArduinoStripLights");

  // Initialize the workingMode and the GUI accordingly
  changeWorkingMode(true);
}

void loop() {

  doWorkingMode();
}
