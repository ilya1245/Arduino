#include <Arduino.h>
#include <GyverTimer.h>
#include <LedBlink.h>
#include <stdio.h>

#include "common.h"
#include "blink.h"
#include "store.h"
#include "action.h"
#include "bt.h"

void setup() {
  Serial.begin(SERIAL_SPEED);
  SerialBT.begin("Technology_STEM");
  Serial.println("Starting...");

  EEPROM.begin(512);
  readSettings();

  for (int i = 0; i < NUMBER_OF_LETTERS; i++) {
    pinMode(ledPins[i], OUTPUT);
    Serial.println(ledPins[i]);
  }

  initBlinkers();;
  if (isOn) {
    processMode(mode);
  }  
}

void loop() {
  processBt();
  if (isBlinkMode) blink();
}
