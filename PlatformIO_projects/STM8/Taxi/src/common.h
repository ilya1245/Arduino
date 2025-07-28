#include <Arduino.h>
// #include <math.h>
#include <constants.h>

extern int mode; 
extern byte pwmMaxValue;
extern byte pwmMinValue;
extern byte pwmStep;

extern int putchar(int c);

extern void setMode(int m);

extern void doWave();