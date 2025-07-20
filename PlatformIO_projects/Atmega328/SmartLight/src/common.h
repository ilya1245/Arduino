#include <Arduino.h>
#include <GyverTimer.h>
#include <LiquidCrystal_I2C.h>
#include <constants.h>

extern GTimer lightTimer;
extern GTimer soundTimer;
extern GTimer lcdClearTimer;

extern int mode; 
extern boolean lightState;

extern byte pwmValue;
extern byte pwmMinValue;

extern LiquidCrystal_I2C lcd;

extern void setMode(int m);