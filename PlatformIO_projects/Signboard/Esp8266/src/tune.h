#include "common.h"

extern byte pwmMaxValue;
extern byte pwmMinValue;
extern byte pwmStepValue;
extern int pwmHighValue;
extern int pwmLowValue;

extern void tunePwmHighValue(int pwmStep);
extern void tunePwmLowValue(int pwmStep);
extern void tuneTimeInterval(int tStep);