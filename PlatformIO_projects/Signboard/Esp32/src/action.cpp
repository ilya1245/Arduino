#include "action.h"
#include "blink.h"
#include "tune.h"
#include "store.h"
#include "common.h"

byte nextActionRange = 0;


void onOff() {
  isOn = !isOn;
  if (isOn) {
    Serial.println("onOff - On");
    selectAction(ledModeIrCommand);
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
  if (!isOn) return;
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

//void oneWaveLeft() {
//  disableAllBlinkers();
//  for (int i = NUMBER_OF_LETTERS -1; i >= 0; i--) {
//    blinkers[i].setPeriod(period);
//    blinkers[i].setOnTime(onMls);
//    blinkers[i].setOffTime(offMls);
//    blinkers[i].setNumOfBlinks(i+1);
//    blinkers[i].setActive(true);
//    smartDelay(timeInterval);
//  }
//}



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
      analogWrite(ledPins[i], pwmHighValue);
      smartDelay(timeFlash);
      analogWrite(ledPins[i], pwmLowValue);
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
      analogWrite(ledPins[i], pwmHighValue);
      smartDelay(timeFlash);
      analogWrite(ledPins[i], pwmLowValue);
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
      analogWrite(ledPins[i], pwmHighValue);
      smartDelay(timeFlash);
      analogWrite(ledPins[i], pwmLowValue);
      smartDelay(timeInterval);
      if (isSwitchMode) return;
    }
    turnPinsLow();
    for (int i = NUMBER_OF_LETTERS - 1; i >= 1; i--) {
      i == NUMBER_OF_LETTERS - 1 ? analogWrite(ledPins[0], pwmLowValue) : analogWrite(ledPins[i+1], pwmLowValue);
      analogWrite(ledPins[i], pwmHighValue);
      smartDelay(timeFlash);
      analogWrite(ledPins[i], pwmLowValue);
      smartDelay(timeInterval);
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
    byte i = random(NUMBER_OF_LETTERS);
    analogWrite(ledPins[i], pwmHighValue);
    smartDelay(timeFlash);
    analogWrite(ledPins[i], pwmLowValue);
    smartDelay(timeInterval);
    turnPinsLow();
    if (isSwitchMode) return;  
  }
  Serial.println("flashRandom - end");
}


void selectAction(byte irCommand) {
  if (isOn || irCommand == 20 || irCommand == 4 || irCommand == 7) {
    switch (irCommand) {
      case 20: // on/off
        Serial.println("on/off");
        isSwitchMode = true;
        onOff();
        break;
      case 22: // key 1
        Serial.println("key 1");
        isSwitchMode = true;
        ledModeIrCommand = irCommand;
        nextActionRange == 0 ? blinkAll(timeInterval * 2, timeInterval * 1.6) : pinLeftToRight();
        break;
      case 23: // key 2
        Serial.println("key 2");
        isSwitchMode = true;
        ledModeIrCommand = irCommand;
        nextActionRange == 0 ? blinkAll(timeInterval * 2, timeInterval) : pinRightToLeft();
        break;
      case 24: // key 3
        Serial.println("key 3");
        isSwitchMode = true;
        ledModeIrCommand = irCommand;
        nextActionRange == 0 ? blinkAll(timeInterval * 2, timeFlash) : pinBackward();
        break;
      case 25: // key 4
        Serial.println("key 4");
        isSwitchMode = true;
        ledModeIrCommand = irCommand;
        nextActionRange == 0 ? blinkAll(timeInterval * 2, timeFlash, 100, 2) : flashLeftToRight();
        break;
      case 26: // key 5
        Serial.println("key 5");
        isSwitchMode = true;
        ledModeIrCommand = irCommand;
        nextActionRange == 0 ? waveAll() : flashRightToLeft();
        break;
      case 27: // key 6
        Serial.println("key 6");
        isSwitchMode = true;
        ledModeIrCommand = irCommand;
        nextActionRange == 0 ? waveLeftToRight() : flashBackward();
        break;
      case 28: // key 7
        Serial.println("key 7");
        isSwitchMode = true;
        ledModeIrCommand = irCommand;
        nextActionRange == 0 ? waveLeftToLeft() : pinRandom();
        break;
      case 29: // key 8
        Serial.println("key 8");
        isSwitchMode = true;
        ledModeIrCommand = irCommand;
        nextActionRange == 0 ? waveRightToLeft() : flashRandom();
        break;
      case 30: // key 9
        Serial.println("key 9");
        isSwitchMode = true;
        ledModeIrCommand = irCommand;
        waveRightToRight();
        break;
      case 31: // key 0
        Serial.println("key 0");
        isSwitchMode = true;
        ledModeIrCommand = irCommand;
        blinkAll(timeInterval * 2, timeInterval * 2);
        break;
      case 9: // setup
        Serial.println("key setup");

        setup(timeInterval * 8, 50, timeInterval);
        break;
      case 18: // key left Up
        Serial.println("key left Up");
        tunePwmHighValue(pwmStepValue);
        break;
      case 21: // key left Down
        Serial.println("key left Down");
        tunePwmHighValue(-pwmStepValue);
        break;
      case 16: // key right Up
        Serial.println("key right Up");
        tunePwmLowValue(pwmStepValue);
        break;
      case 19: // key right Down
        Serial.println("key right Down");
        tunePwmLowValue(-pwmStepValue);
        break;
      case 11: // key Left
        Serial.println("key Left");
        tuneTimeInterval(-timeStep);
        break;
      case 13: // key Right
        Serial.println("key Right");
        tuneTimeInterval(timeStep);
        break;
      case 4: // key Record
        Serial.println("key Record");
        writeSettings();
        break;
      case 7: // key Reset
        Serial.println("key Reset");
        writeDefaultSettings();
        break;
      case 15: // key Next Action Range
        Serial.println("key Next Action Range");
        nextActionRange = 1;
        printf("Action range = %d\n", nextActionRange);
        break;
      case 10: // key Previous Action Range
        Serial.println("key Previous Action Range");
        nextActionRange = 0;
        printf("Action range = %d\n", nextActionRange);
        break;
    }
  }
}