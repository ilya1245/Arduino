#include "action.h"

byte nextActionRange = 0;


void onOff(bool m) {
  isOn = m;
  if (isOn) {
    Serial.println("onOff - On");
    processMode(mode);
  } else {
    Serial.println("onOff - Off");  
    isSwitchMode = true;    
    turnPinsOff();
  }
}

void blinkAll(uint16_t period, uint16_t onMls, uint16_t offMls, byte numOfBlinks) {
  Serial.println("blinkAll - start");
  isBlinkMode = true;
  for (int i = 0; i < NUMBER_OF_LETTERS; i++) {
    blinkers[i].setPwmMaxValue(pwmHighValue);
    blinkers[i].setPwmMinValue(pwmLowValue);
    blinkers[i].setPeriod(period);
    blinkers[i].setOnTime(onMls);
    blinkers[i].setOffTime(offMls);
    blinkers[i].setNumOfBlinks(numOfBlinks);
    blinkers[i].setActive(true);
  }
  Serial.println("blinkAll - end");
}

void blinkAll(uint16_t period, uint16_t onMls) {
  blinkAll(period, onMls, 0, 1);
}

void setup(uint16_t period, uint16_t onMls, uint16_t offMls) {
  Serial.println("setup - start");
  isBlinkMode = true;
  for (int i = 0; i < NUMBER_OF_LETTERS; i++) {
    blinkers[i].setPeriod(period);
    blinkers[i].setOnTime(onMls);
    blinkers[i].setOffTime(offMls);
    blinkers[i].setNumOfBlinks(i + 1);
    blinkers[i].setActive(true);
  }
  Serial.println("setup - end");
}

void waveAll() {
  Serial.println("waveAll - start"); 
  isSwitchMode = false;
  byte pwmWaveValue;
  byte i = 0;
  float angle;

  while (true) {
    angle = (i++ * 2 * PI) / 255;
    pwmWaveValue = pwmLowValue + (1 - abs(cos(angle))) * (pwmHighValue - pwmLowValue);
    for (int i = 0; i < NUMBER_OF_LETTERS; i++) {
      analogWrite(ledPins[i], pwmWaveValue);
    }
    delay(timeInterval / 25); //slow down the wave
    loop();
    if (isSwitchMode) return;
  }
}

void tukTuk() {
  Serial.println("tukTuk - start");
  isSwitchMode = false;
  isBlinkMode = false;

  while (true) {
    for (int i = NUMBER_OF_LETTERS - 1; i >= 0; i--) {
      analogWrite(ledPins[i], pwmHighValue);
      smartDelay(100);
      analogWrite(ledPins[i], pwmLowValue);
      smartDelay(timeInterval * 2 - 100);
    }
    if (isSwitchMode) return;
  }
  Serial.println("tukTuk - end");
}

void processMode(int mode) {
  turnPinsOff();  
  if (isOn) {
    isSwitchMode = true;
    switch (mode) {
      case 0: // key 1
        Serial.println("mode 1");
        // blinkAll(timeInterval * 2, timeInterval * 1.6);
        turnPinsHigh();
        break;
      case 1: // key 2
        Serial.println("mode 2");
        blinkAll(timeInterval * 2, timeInterval);
        break;
      case 2: // key 3
        Serial.println("mode 3");
        blinkAll(timeInterval * 2, timeFlash);
        break;
      case 3: // key A
        Serial.println("mode A");
        blinkAll(timeInterval * 2, timeFlash, 100, 2);
        break;
      case 4: // key B
        Serial.println("mode B");
        waveAll();
        break;
      case 5: // key C
        Serial.println("mode C");
        tukTuk();
        break;
    }
  }
}