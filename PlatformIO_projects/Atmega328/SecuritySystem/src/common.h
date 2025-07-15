#include <Arduino.h>
#include <GyverTimer.h>
#include <LibPrintf.h>
#include <LedBlink.h>
#include <constants.h>


// extern GTimer lightTimer;
extern Blinker ledStandbyBlinker;
extern Blinker ledAlarmBlinker;
extern Blinker beepAlarmBlinker;

extern GTimer alarmTimer;
extern int mode; 


extern void setMode(int m);
extern void blink();
extern void offAllBlinkers();