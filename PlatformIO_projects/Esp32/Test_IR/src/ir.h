#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include "common.h"

#define RECV_PIN 13
#define RECV_LED_PIN 12

extern IRrecv irrecv;

extern void processIr();