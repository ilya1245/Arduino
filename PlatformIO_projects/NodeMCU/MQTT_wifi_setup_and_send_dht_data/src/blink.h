#include <LedBlink.h>
#include <common.h>

extern Blinker blinkerPingOk;
extern Blinker blinkerWifiConnected;
extern Blinker blinkerWifiDisconnected;

extern void setBlinkParameters(Blinker &bl, byte numOfBlinks);
extern void blink();