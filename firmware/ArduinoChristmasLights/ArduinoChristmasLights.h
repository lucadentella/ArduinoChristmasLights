// Libraries
#include <Preferences.h>
#include <WiFiManager.h>
#include <ESPUI.h>
#include <gamma.h>

// Definitions - Access point for WifiManager
#define AP_NAME       "ArduinoStripLights"
#define AP_PASSWORD   "MyPassword"

// Definitions - Working modes
#define MODE_BLINK      0
#define MODE_FADE       1
#define MODE_FULLON     2
#define MODE_FULLOFF    3

// Definitions - Fade directions
#define FADE_UP         true
#define FADE_DOWN       false

// Definitions - PINs
#define PIN_EN    16
#define PIN_IN1   18
#define PIN_IN2   33

// Definitions - PWM/LEDC
#define PWM_FREQUENCY   5000
#define PWM_RESOLUTION  8
#define LEDC_CHANNEL    0

// Definitions - Starting values
#define DEFAULT_BLINK_SPEED   50
#define DEFAULT_FADE_SPEED    30

// Definitions - Full ON delay (5ms)
#define FULLON_DELAY    5

// Web interface elements
uint16_t tab1, selectMode, sliderFadeSpeed, sliderBlinkSpeed, buttonReset;

// Global objects
WiFiManager wifiManager;
Preferences preferences;
GAMMA gt1(256);

// Global variables
bool apMode = false;
int workingMode;
int blinkDelay, fadeDelay;
int dutyCycle;
bool fadeDirection = FADE_UP;
bool outStatus = false;
unsigned long now, lastUpdate = -1;