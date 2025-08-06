#include <LedBlink.h>
#include <common.h>

extern Blinker blinkerWifiOk;
extern Blinker blinkerWifiSearch;

// extern void disableAllBlinkers();
extern void setBlinkParameters(Blinker &bl, byte numOfBlinks);
extern void blink();