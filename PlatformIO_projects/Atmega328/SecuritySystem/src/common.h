#include <Arduino.h>
#include <GyverTimer.h>
#include <LibPrintf.h>
#include <LiquidCrystal_I2C.h>
#include <LedBlink.h>
#include <constants.h>


// extern GTimer lightTimer;
extern Blinker ledStandbyBlinker;
extern Blinker ledAlarmBlinker;
extern Blinker beepAlarmBlinker;

extern GTimer alarmTimer;
// extern GTimer lcdClearTimer;

extern int mode; 
// extern boolean lightState;

// extern byte pwmValue;
// extern byte pwmMinValue;

// extern LiquidCrystal_I2C lcd;

extern void setMode(int m);

extern void blink();

extern void offAllBlinkers();