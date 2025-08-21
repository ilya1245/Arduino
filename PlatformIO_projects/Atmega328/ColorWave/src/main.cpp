#include "common.h"
#include "ir.h"
#include "ledStrip.h"

void setup() {
  Serial.begin(SERIAL_SPEED);
  // подключил на D2, прерывание 0
  attachInterrupt(0, irIsr, FALLING);

  pinMode(RECV_LED_PIN, OUTPUT);
  pinMode(RECV_PIN, INPUT);
  // writeDefaultSettings();
  readSettings();

  FastLED.addLeds<LED_TYPE, LED_ADDRESS_PIN, COLOR_ORDER>(leds, NUM_LEDS);
}


void loop() {
  processIr();
  if (ledStepTimer.isReady()) {    
    if (isOn) {
      rainbowWave();
    }    
  }  
}