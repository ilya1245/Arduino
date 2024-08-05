#include "action.h"
#include "blink.h"
#include "tune.h"


void onOff() {
  isOn = !isOn;
  if (isOn) {
    blinkAll(timeInterval * 2, timeInterval * 2);
    for (int i = 0; i < NUMBER_OF_LETTERS; i++) {
      blinkers[i].setActive(true);
    }
  } else {
    disableAllBlinkers();
    turnPinsOff();
  }
}

void blinkAll(uint16_t period, uint16_t onMls, uint16_t offMls, byte numOfBlinks) {
  Serial.println("blinkAll - start");
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
  byte pwmStep = 2;

  byte i;
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