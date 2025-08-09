#include <Arduino.h>
#include <GyverTimer.h>
#include <LibPrintf.h>
#include <EEPROM.h>
#include <ESPping.h>
#include <LedBlink.h>
#include <constants.h>

// extern GTimer timer_3s;
extern GTimer timer_5s;
// extern GTimer timer_5m;

extern String ssidStored;
extern String passStored;
extern bool apMode;