#include "common.h"

GTimer barTimer(MS, TIME_INTERVAL);

int getSignal() {
  // int sumMicValue = 0;
  // int megementCount = 10;
  // for (int i = 0; i < megementCount; i++) {
  //   sumMicValue += analogRead(MIC_PIN);    // 0..1023
  // }
  // int micValue = int(sumMicValue/megementCount);

  int micValue =  analogRead(MIC_PIN);
  Serial.println(micValue);
  return micValue;
}

