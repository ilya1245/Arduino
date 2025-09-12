#include <stdio.h>
#include <map>
#include <pins_arduino.h>
#include <GyverTimer.h>

#define byte uint8_t

#define SERIAL_SPEED 115200
#define NUMBER_OF_LETTERS 1

#define vsnprintf _snprintf

extern std::map<int, uint8_t> ledPins;

extern byte pwmMaxValue;
extern byte pwmMinValue;
extern byte pwmStepValue;
extern int pwmHighValue;
extern int pwmLowValue;

extern int timeInterval; // switch interval in milis
extern int timeStep; // time tuning step
extern byte timeFlash; // Flash time

extern GTimer timerWaveExit;
extern GTimer timer_1s;

extern boolean isPrintKeyCode;
extern boolean isOn;
extern boolean isBlinkMode;
extern boolean isSwitchMode;

extern void smartDelay(long pause, int delayTimeStep);
extern void smartDelay(long pause);

