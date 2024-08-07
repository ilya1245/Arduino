#include <LibPrintf.h>
#include <GyverTimer.h>
#include <LedBlink.h>

#include "common.h"
#include "blink.h"
#include "ir.h"
#include "store.h"
#include "action.h"

void setup() {
  Serial.begin(SERIAL_SPEED);
  Serial.println("Starting...");
  irrecv.enableIRIn();

  pinMode(RECV_LED_PIN, OUTPUT);

  EEPROM.begin(512);
  readSettings();

  for (int i = 0; i < NUMBER_OF_LETTERS; i++) {
    pinMode(ledPins[i], OUTPUT);
    Serial.println(ledPins[i]);
  }

  analogWriteFreq(10000);

  initBlinkers();
  // delay(7000);
  if (isOn) {
    selectAction(ledModeIrCommand);
  }  
}

void loop() {
  processIr();
  if (isBlinkMode) blink();
}
