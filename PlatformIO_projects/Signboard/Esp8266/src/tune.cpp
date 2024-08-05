#include "tune.h"
#include "blink.h"
#include "action.h"

byte pwmMaxValue = 255;
byte pwmMinValue = 0;
byte pwmStepValue = 5;
int pwmHighValue = 100;
int pwmLowValue = 5;

void tunePwmHighValue(int pwmStep) {
  printf("pwmHighValue = %d\n", pwmHighValue);
  pwmHighValue += pwmStep;
  printf("pwmHighValue = %d\n", pwmHighValue);
  if (pwmHighValue < pwmLowValue+1) pwmHighValue = pwmLowValue+1;
  if (pwmHighValue > pwmMaxValue) pwmHighValue = pwmMaxValue;
  printf("pwmHighValue = %d\n", pwmHighValue);
  
  for (int i = 0; i < NUMBER_OF_LETTERS; i++) {
    blinkers[i].setPwmMaxValue(pwmHighValue);
  }
  Serial.println("tunePwmHighValue() - end");
}

void tunePwmLowValue(int pwmStep) {
  printf("pwmLowValue = %d\n", pwmLowValue);
  pwmLowValue += pwmStep;
  printf("pwmLowValue = %d\n", pwmLowValue);
  if (pwmLowValue < pwmMinValue) pwmLowValue = pwmMinValue;
  if (pwmLowValue > pwmHighValue) pwmLowValue = pwmHighValue;
  printf("pwmLowValue = %d\n", pwmLowValue);

  for (int i = 0; i < NUMBER_OF_LETTERS; i++) {
    blinkers[i].setPwmMinValue(pwmLowValue);
  }
  Serial.println("tunePwmLowValue() - end");
}

void tuneTimeInterval(int tStep) {
  timeInterval += tStep;
  if (timeInterval < timeStep * 2) timeInterval = timeStep * 2;
  isSwitchMode = true;
  printf("timeInterval = %d\n", timeInterval);
  smartDelay(200);
  blinkAll(timeInterval * 2, timeInterval);
}