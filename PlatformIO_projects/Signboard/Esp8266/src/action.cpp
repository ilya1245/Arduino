#include "action.h"
#include "blink.h"
#include "tune.h"
#include "store.h"


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

void selectAction(byte irCommand) {
  if (isOn || irCommand == 20 || irCommand == 4) {
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
        blinkAll(timeInterval * 2, timeInterval * 1.6);
        break;
      case 23: // key 2
        Serial.println("key 2");
        isSwitchMode = true;
        ledModeIrCommand = irCommand;
        blinkAll(timeInterval * 2, timeInterval);
        break;
      case 24: // key 3
        Serial.println("key 3");
        isSwitchMode = true;
        ledModeIrCommand = irCommand;
        blinkAll(timeInterval * 2, 100);
        break;
      case 25: // key 4
        Serial.println("key 4");
        isSwitchMode = true;
        ledModeIrCommand = irCommand;
        blinkAll(timeInterval * 2, 50, 100, 2);
        break;
      case 26: // key 5
        Serial.println("key 5");
        isSwitchMode = true;
        ledModeIrCommand = irCommand;
        waveAll();
        break;
      case 27: // key 6
        Serial.println("key 6");
        isSwitchMode = true;
        ledModeIrCommand = irCommand;
        waveLeftToRight();
        break;
      case 28: // key 7
        Serial.println("key 7");
        isSwitchMode = true;
        ledModeIrCommand = irCommand;
        waveLeftToLeft();
        break;
      case 29: // key 8
        Serial.println("key 8");
        isSwitchMode = true;
        ledModeIrCommand = irCommand;
        waveRightToLeft();
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
    }
  }
}