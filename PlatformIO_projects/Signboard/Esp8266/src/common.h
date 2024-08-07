#include <stdio.h>
#include <map>
#include <pins_arduino.h>
#include <GyverTimer.h>

#include "main.h"

#define byte uint8_t

#define SERIAL_SPEED 115200
#define NUMBER_OF_LETTERS 7

extern std::map<int, int> ledPins;

extern int timeInterval; // switch interval in milis
extern int timeStep; // time tuning step

extern GTimer timerWaveExit;
extern GTimer timer_1s;

extern boolean isPrintKeyCode;
extern boolean isOn;
extern boolean isBlinkMode;
extern boolean isSwitchMode;
extern byte ledModeIrCommand;

extern void smartDelay(long pause, int delayTimeStep);
extern void smartDelay(long pause);

