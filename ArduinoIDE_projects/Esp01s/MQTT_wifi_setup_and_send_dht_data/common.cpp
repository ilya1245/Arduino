#include "common.h"

GTimer timer_10s(MS, 10000);

String ssidStored;
String passStored;

boolean isPingOk = false;
float temperatureCorrection = 0.0f;