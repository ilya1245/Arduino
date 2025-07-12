#include "common.h"

// std::map<int, uint8_t> ledPins = { {0, 2}, {1, 3}, {2, 4}, {3, 5}, {4, 9}, {5, 7}, {6, 8} };
std::map<int, uint8_t> ledPins = { {0, 15}, {1, 2}, {2, 4}, {3, 16}, {4, 17}, {5, 5}, {6, 18} };
// std::map<int, uint8_t> ledPins = { {0, 5}, {1, 6}, {2, 7} };

int timeInterval = 500; // switch interval in milis
int timeStep = 100; // time tuning step

GTimer timerWaveExit(MS, 100);
GTimer timer_1s(MS, 1000);

bool isPrintKeyCode = true;
bool isBlinkMode = false;
bool isOn = false;
bool isSwitchMode = false;
byte ledModeIrCommand = 0;

void smartDelay(long pause, int delayTimeStep = 50) {
  for (int i = 0; i < pause / delayTimeStep; i++) {
    delay(delayTimeStep);
    loop();
  }
}

void smartDelay(long pause) {
    smartDelay(pause, 50);
}