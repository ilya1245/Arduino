#include "common.h"

SoftwareSerial mySerial(RX_PIN, TX_PIN); // Только TX, RX отключен

GTimer keyDelayTimer(MS);
GTimer keyPressTimer(MS);



