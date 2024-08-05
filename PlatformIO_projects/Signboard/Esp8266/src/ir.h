#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include "common.h"

#define RECV_PIN D5
#define RECV_LED_PIN D0

extern IRrecv irrecv;

extern void processIr();