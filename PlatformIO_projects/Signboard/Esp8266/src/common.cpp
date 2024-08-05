#include "common.h"

std::map<int, int> ledPins = { {0, D1}, {1, D2}, {2, D3}, {3, D4}, {4, D6}, {5, D7}, {6, D8} };

int timeInterval = 500; // switch interval in milis
int timeStep = 100; // time tuning step

GTimer timerWaveExit(MS, 100);
GTimer timer_1s(MS, 1000);

boolean isPrintKeyCode = true;
boolean isBlinkMode = false;
boolean isOn = false;
boolean isSwitchMode = false;

void smartDelay(long pause, int delayTimeStep = 50) {
  for (int i = 0; i < pause / delayTimeStep; i++) {
    delay(delayTimeStep);
    loop();
  }
}

void smartDelay(long pause) {
    smartDelay(pause, 50);
}