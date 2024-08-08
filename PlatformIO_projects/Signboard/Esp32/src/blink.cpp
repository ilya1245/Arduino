#include "blink.h"
#include "tune.h"

Blinker blinkers[NUMBER_OF_LETTERS];

void initBlinkers() {
  for (int i = 0; i < NUMBER_OF_LETTERS; i++) {
    blinkers[i] = Blinker(ledPins[i], timeInterval * 2, timeInterval * 2, &Serial, SERIAL_SPEED);
    blinkers[i].setPwmMaxValue(pwmHighValue);
    blinkers[i].setPwmMinValue(pwmLowValue);
    blinkers[i].setActive(false);
    blinkers[i].setLogLevel(1); // If commented out, the blinkers doesn't work on esp32
  }
}

// ---------------- Blink code ----------------
void disableAllBlinkers() {
  for (int i = 0; i < NUMBER_OF_LETTERS; i++) {
    blinkers[i].setActive(false);
  }

  for (int i = NUMBER_OF_LETTERS - 1; i >= 0; i--) {
    analogWrite(ledPins[i], pwmLowValue);
  }
}

void turnPinsOff() {
  for (int i = NUMBER_OF_LETTERS - 1; i >= 0; i--) {
    analogWrite(ledPins[i], 0);
  }
}

void blink() {
  //  Serial.println("blink()");
  for (int i = 0; i < NUMBER_OF_LETTERS; i++) {
    blinkers[i].blink();
  }
}