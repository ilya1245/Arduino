#include <stdio.h>
#include <map>
// #include <pins_arduino.h>
// #include <GyverTimer.h>


#define byte uint8_t

#define SERIAL_SPEED 115200
#define NUMBER_OF_LETTERS 7

// extern std::map<int, int> ledPins;

extern int timeInterval; // switch interval in milis
extern int timeStep; // time tuning step

// extern GTimer timerWaveExit;
// extern GTimer timer_1s;

extern bool isPrintKeyCode;
extern bool isOn;
extern bool isBlinkMode;
extern bool isSwitchMode;
extern byte ledModeIrCommand;

// extern void smartDelay(long pause, int delayTimeStep);
// extern void smartDelay(long pause);

