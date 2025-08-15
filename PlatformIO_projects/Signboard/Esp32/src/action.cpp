#include "action.h"
#include "blink.h"
#include "tune.h"
#include "store.h"
#include "common.h"
#include "bt.h"

byte nextActionRange = 0;


void onOff(bool m) {
  isOn = m;
  if (isOn) {
    Serial.println("onOff - On");
    processMode(mode);
  } else {
    Serial.println("onOff - Off");    
    disableAllBlinkers();
    turnPinsOff();
  }
}

void blinkAll(uint16_t period, uint16_t onMls, uint16_t offMls, byte numOfBlinks) {
  Serial.println("blinkAll - start");
  if (!isOn) return;
  disableAllBlinkers();
  isBlinkMode = true;
  if (!isOn) return;
  for (int i = 0; i < NUMBER_OF_LETTERS; i++) {
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
  if (!isOn) return;
  disableAllBlinkers();
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
  if (!isOn) return;
  disableAllBlinkers();
  isSwitchMode = false;
  byte pwmWaveValue;
  // byte pwmStep = 2;

  byte i = 0;
  float angle;

  while (true) {
    angle = (i++ * 2 * PI) / 255;
    //    printf("\nangle = %f", angle);
    //    printf("\nsin(angle) = %f\n", cos(angle));
    pwmWaveValue = pwmLowValue + (1 - abs(cos(angle))) * (pwmHighValue - pwmLowValue);
    for (int i = 0; i < NUMBER_OF_LETTERS; i++) {
      analogWrite(ledPins[i], pwmWaveValue);
    }
    delay(timeInterval / 25); //slow down the wave
    loop();
    if (isSwitchMode) return;
  }
}

void oneWaveToRight() {
  if (!isOn) return;
  for (int i = 0; i < NUMBER_OF_LETTERS; i++) {
    blinkers[i].setPeriod(timeInterval * (NUMBER_OF_LETTERS - i));
    blinkers[i].setOnTime((NUMBER_OF_LETTERS - i) * timeInterval);
    blinkers[i].setOffTime(timeInterval * i);
    blinkers[i].setNumOfBlinks(1);
    blinkers[i].setActive(true);
  }
}

void waveLeftToRight() {
  Serial.println("waveLeftToRight - start");
  if (!isOn) return;
  disableAllBlinkers();
  isSwitchMode = false;
  isBlinkMode = false;
  if (!isOn) return;

  while (true) {
    for (int i = 0; i < NUMBER_OF_LETTERS; i++) {
      analogWrite(ledPins[i], pwmHighValue);
      //      printf("i = %d before smartDelay\n", i);
      smartDelay(timeInterval);
      //      printf("i = %d after smartDelay\n", i);
      //      printf("isSwitchMode = %d\n", isSwitchMode);
      if (isSwitchMode) return;
    }
    for (int i = 0; i < NUMBER_OF_LETTERS; i++) {
      analogWrite(ledPins[i], pwmLowValue);
      //      printf("i = %d before smartDelay\n", i);
      smartDelay(timeInterval);
      //      printf("i = %d after smartDelay\n", i);
      //      printf("isSwitchMode = %d\n", isSwitchMode);
      if (isSwitchMode) return;
    }
  }
  Serial.println("waveLeftToRight - end");
}

void waveRightToLeft() {
  Serial.println("waveLeftToRight - start");
  if (!isOn) return;
  disableAllBlinkers();
  isSwitchMode = false;
  isBlinkMode = false;
  if (!isOn) return;

  while (true) {
    for (int i = NUMBER_OF_LETTERS - 1; i >= 0; i--) {
      analogWrite(ledPins[i], pwmHighValue);
      smartDelay(timeInterval);
    }
    if (timerWaveExit.isReady() && isSwitchMode) return;
    for (int i = NUMBER_OF_LETTERS - 1; i >= 0; i--) {
      analogWrite(ledPins[i], pwmLowValue);
      smartDelay(timeInterval);
    }
    if (timerWaveExit.isReady() && isSwitchMode) return;
  }
  Serial.println("waveLeftToRight - end");
}

void waveLeftToLeft() {
  Serial.println("waveLeftToRight - start");
  if (!isOn) return;
  disableAllBlinkers();
  isSwitchMode = false;
  isBlinkMode = false;
  if (!isOn) return;

  while (true) {
    for (int i = 0; i < NUMBER_OF_LETTERS; i++) {
      analogWrite(ledPins[i], pwmHighValue);
      smartDelay(timeInterval);
    }
    if (timerWaveExit.isReady() && isSwitchMode) return;
    for (int i = NUMBER_OF_LETTERS - 1; i >= 0; i--) {
      analogWrite(ledPins[i], pwmLowValue);
      smartDelay(timeInterval);
    }
    if (timerWaveExit.isReady() && isSwitchMode) return;
  }
  Serial.println("waveLeftToRight - end");
}

void waveRightToRight() {
  Serial.println("waveLeftToRight - start");
  if (!isOn) return;
  disableAllBlinkers();
  isSwitchMode = false;
  isBlinkMode = false;
  if (!isOn) return;

  while (true) {
    for (int i = NUMBER_OF_LETTERS - 1; i >= 0; i--) {
      analogWrite(ledPins[i], pwmHighValue);
      smartDelay(timeInterval);
    }
    if (timerWaveExit.isReady() && isSwitchMode) return;
    for (int i = 0; i < NUMBER_OF_LETTERS; i++) {
      analogWrite(ledPins[i], pwmLowValue);
      smartDelay(timeInterval);
    }
    if (timerWaveExit.isReady() && isSwitchMode) return;
  }
  Serial.println("waveLeftToRight - end");
}

void pinLeftToRight() {
  Serial.println("pinLeftToRight - start");
  if (!isOn) return;
  disableAllBlinkers();
  isSwitchMode = false;
  isBlinkMode = false;
  if (!isOn) return;

  while (true) {
    for (int i = 0; i < NUMBER_OF_LETTERS; i++) {
      i == 0 ? analogWrite(ledPins[NUMBER_OF_LETTERS-1], pwmLowValue) : analogWrite(ledPins[i-1], pwmLowValue);
      analogWrite(ledPins[i], pwmHighValue);
      smartDelay(timeInterval);
      if (isSwitchMode) return;
    }
  }
  Serial.println("pinLeftToRight - end");
}

void pinRightToLeft() {
  Serial.println("pinRightToLeft - start");
  if (!isOn) return;
  disableAllBlinkers();
  isSwitchMode = false;
  isBlinkMode = false;
  if (!isOn) return;

  while (true) {
    for (int i = NUMBER_OF_LETTERS - 1; i >= 0; i--) {
      i == NUMBER_OF_LETTERS - 1 ? analogWrite(ledPins[0], pwmLowValue) : analogWrite(ledPins[i+1], pwmLowValue);
      analogWrite(ledPins[i], pwmHighValue);
      smartDelay(timeInterval);
      if (isSwitchMode) return;
    }
  }
  Serial.println("pinRightToLeft - end");
}

void pinBackward() {
  Serial.println("pinBackward - start");
  if (!isOn) return;
  disableAllBlinkers();
  isSwitchMode = false;
  isBlinkMode = false;
  if (!isOn) return;

  while (true) {
    for (int i = 0; i < NUMBER_OF_LETTERS - 1; i++) {
      i == 0 ? analogWrite(ledPins[NUMBER_OF_LETTERS-1], pwmLowValue) : analogWrite(ledPins[i-1], pwmLowValue);
      analogWrite(ledPins[i], pwmHighValue);
      smartDelay(timeInterval);
      if (isSwitchMode) return;
    }
    turnPinsLow();
    for (int i = NUMBER_OF_LETTERS - 1; i >= 1; i--) {
      i == NUMBER_OF_LETTERS - 1 ? analogWrite(ledPins[0], pwmLowValue) : analogWrite(ledPins[i+1], pwmLowValue);
      analogWrite(ledPins[i], pwmHighValue);
      smartDelay(timeInterval);
      if (isSwitchMode) return;
    }
    turnPinsLow();
  }
  Serial.println("pinBackward - end");
}

void pinRandom() {
  Serial.println("pinRandom - start");
  if (!isOn) return;
  disableAllBlinkers();
  isSwitchMode = false;
  isBlinkMode = false;
  if (!isOn) return;

  while (true) {    
    analogWrite(ledPins[random(NUMBER_OF_LETTERS)], pwmHighValue);
    smartDelay(timeInterval);
    turnPinsLow();
    if (isSwitchMode) return;  
  }
  Serial.println("pinRandom - end");
}

void doFlash(int pin) {
  analogWrite(ledPins[pin], pwmHighValue);
  smartDelay(timeFlash);
  analogWrite(ledPins[pin], pwmLowValue);
}

void flashLeftToRight() {
  Serial.println("pinLeftToRight - start");
  if (!isOn) return;
  disableAllBlinkers();
  isSwitchMode = false;
  isBlinkMode = false;
  if (!isOn) return;

  while (true) {
    for (int i = 0; i < NUMBER_OF_LETTERS; i++) {
      i == 0 ? analogWrite(ledPins[NUMBER_OF_LETTERS-1], pwmLowValue) : analogWrite(ledPins[i-1], pwmLowValue);
      doFlash(i);
      smartDelay(timeInterval-timeFlash);
      if (isSwitchMode) return;
    }
  }
  Serial.println("pinLeftToRight - end");
}

void flashRightToLeft() {
  Serial.println("pinLeftToRight - start");
  if (!isOn) return;
  disableAllBlinkers();
  isSwitchMode = false;
  isBlinkMode = false;
  if (!isOn) return;

  while (true) {
    for (int i = NUMBER_OF_LETTERS - 1; i >= 0; i--) {
      i == 0 ? analogWrite(ledPins[NUMBER_OF_LETTERS-1], pwmLowValue) : analogWrite(ledPins[i-1], pwmLowValue);
      doFlash(i);
      smartDelay(timeInterval-timeFlash);
      if (isSwitchMode) return;
    }
  }
  Serial.println("pinLeftToRight - end");
}

void flashBackward() {
  Serial.println("pinBackward - start");
  if (!isOn) return;
  disableAllBlinkers();
  isSwitchMode = false;
  isBlinkMode = false;
  if (!isOn) return;

  while (true) {
    for (int i = 0; i < NUMBER_OF_LETTERS - 1; i++) {
      i == 0 ? analogWrite(ledPins[NUMBER_OF_LETTERS-1], pwmLowValue) : analogWrite(ledPins[i-1], pwmLowValue);
      doFlash(i);
      smartDelay(timeInterval-timeFlash);
      if (isSwitchMode) return;
    }
    turnPinsLow();
    for (int i = NUMBER_OF_LETTERS - 1; i >= 1; i--) {
      i == NUMBER_OF_LETTERS - 1 ? analogWrite(ledPins[0], pwmLowValue) : analogWrite(ledPins[i+1], pwmLowValue);
      doFlash(i);
      smartDelay(timeInterval-timeFlash);
      if (isSwitchMode) return;
    }
    turnPinsLow();
  }
  Serial.println("pinBackward - end");
}

void flashRandom() {
  Serial.println("flashRandom - start");
  if (!isOn) return;
  disableAllBlinkers();
  isSwitchMode = false;
  isBlinkMode = false;
  if (!isOn) return;

  while (true) { 
    int i = random(NUMBER_OF_LETTERS);
    doFlash(i);
    smartDelay(timeInterval-timeFlash);
    turnPinsLow();
    if (isSwitchMode) return;  
  }
  Serial.println("flashRandom - end");
}

void flashRandom_2() {
  Serial.println("flashRandom_2 - start");
  if (!isOn) return;
  disableAllBlinkers();
  isSwitchMode = false;
  isBlinkMode = false;
  if (!isOn) return;

  while (true) { 
    int i = random(NUMBER_OF_LETTERS);
    doFlash(i);
    smartDelay(100);
    doFlash(i);
    smartDelay(timeInterval - 100 - 2*timeFlash);
    turnPinsLow();
    if (isSwitchMode) return;  
  }
  Serial.println("flashRandom_2 - end");
}

// void waveAll() {
//   Serial.println("waveAll - start");
//   if (!isOn) return;
//   disableAllBlinkers();
//   isSwitchMode = false;
//   byte pwmWaveValue;
//   // byte pwmStep = 2;

//   byte i = 0;
//   float angle;

//   while (true) {
//     angle = (i++ * 2 * PI) / 255;
//     //    printf("\nangle = %f", angle);
//     //    printf("\nsin(angle) = %f\n", cos(angle));
//     pwmWaveValue = pwmLowValue + (1 - abs(cos(angle))) * (pwmHighValue - pwmLowValue);
//     for (int i = 0; i < NUMBER_OF_LETTERS; i++) {
//       analogWrite(ledPins[i], pwmWaveValue);
//     }
//     delay(timeInterval / 25); //slow down the wave
//     loop();
//     if (isSwitchMode) return;
//   }
// }

void tukTuk() {
  Serial.println("tukTuk - start");
  if (!isOn) return;
  disableAllBlinkers();
  isSwitchMode = false;
  isBlinkMode = false;
  if (!isOn) return;

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
  if (isOn) {
    switch (mode) {
      case 0: // key 1
        Serial.println("key 1");
        isSwitchMode = true;
        blinkAll(timeInterval * 2, timeInterval * 1.6);
        break;
      case 1: // key 2
        Serial.println("key 2");
        isSwitchMode = true;
        blinkAll(timeInterval * 2, timeInterval);
        break;
      case 2: // key 3
        Serial.println("key 3");
        isSwitchMode = true;
        blinkAll(timeInterval * 2, timeFlash);
        break;
      case 3: // key A
        Serial.println("key A");
        isSwitchMode = true;
        blinkAll(timeInterval * 2, timeFlash, 100, 2);
        break;
      case 4: // key B
        Serial.println("key B");
        isSwitchMode = true;
        waveAll();
        break;
      case 5: // key C
        Serial.println("key C");
        isSwitchMode = true;
        tukTuk();
        break;
    }
  }
}