#include "common.h"

std::map<int, int> ledPins = { {0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 6}, {5, 7}, {6, 8} };

int timeInterval = 500; // switch interval in milis
int timeStep = 100; // time tuning step

// GTimer timerWaveExit(MS, 100);
// GTimer timer_1s(MS, 1000);

bool isPrintKeyCode = true;
bool isBlinkMode = false;
bool isOn = false;
bool isSwitchMode = false;
byte ledModeIrCommand = 0;

// void smartDelay(long pause, int delayTimeStep = 50) {
//   for (int i = 0; i < pause / delayTimeStep; i++) {
//     delay(delayTimeStep);
//     loop();
//   }
// }

// void smartDelay(long pause) {
//     smartDelay(pause, 50);
// }