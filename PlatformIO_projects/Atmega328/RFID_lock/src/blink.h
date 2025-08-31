#include "LedBlink.h"
#include "common.h"

// #define SERIAL_SPEED 115200

extern Blinker blinkerOpen;
// extern Blinker blinkerClose;

void disableAllBlinkers();
void setBlinkParameters(Blinker &bl, byte numOfBlinks);
void blink();