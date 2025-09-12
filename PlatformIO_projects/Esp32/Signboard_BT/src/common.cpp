#include "common.h"

// std::map<int, uint8_t> ledPins = { {0, 15}, {1, 2}, {2, 4}, {3, 16}, {4, 17}, {5, 5}, {6, 18}, {7, 19}, {8, 21}, {9, 3} };
// std::map<int, uint8_t> ledPins = { {0, 13}, {1, 15}, {2, 4}, {3, 16}, {4, 17}, {5, 5}, {6, 18}, {7, 23}, {8, 19}, {9, 22} };
// std::map<int, uint8_t> ledPins = { {9, 13}, {8, 15}, {7, 4}, {6, 16}, {5, 17}, {4, 5}, {3, 18}, {2, 23}, {1, 19}, {0, 22} };
std::map<int, uint8_t> ledPins = { {0, 12} };

byte pwmMaxValue = 255;
byte pwmMinValue = 0;
byte pwmStepValue = 5;
int pwmHighValue = 100;
int pwmLowValue = 5;

int timeInterval = 500; // switch interval in milis
int timeStep = 100; // time tuning step
byte timeFlash = 50; // Flash time

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