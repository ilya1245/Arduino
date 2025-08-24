#include "common.h"
#include "bt.h"
#include "ledStrip.h"

void setup() {
  Serial.begin(SERIAL_SPEED);
  SerialBT.begin("ColorWave");
  
  EEPROM.begin(512);
  // writeDefaultSettings();
  readSettings();

  FastLED.addLeds<LED_TYPE, LED_ADDRESS_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.clear();    
  FastLED.show();
}


void loop() {
  processBt();
  if (ledStepTimer.isReady()) {    
    if (isOn) {
      rainbowWave();
    }    
  }  
}