#include <Arduino.h>
#include <SoftwareSerial.h>
#include <GyverTimer.h>
#include "constants.h"

extern SoftwareSerial mySerial; // Только TX, RX отключен

extern GTimer keyDelayTimer;
extern GTimer keyPressTimer;


