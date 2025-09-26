#include <FastLED.h>
#include "common.h"

extern CRGB leds[];

extern void slowBar();
extern void showBar(int level);
extern int getBarLevel(int micValue);