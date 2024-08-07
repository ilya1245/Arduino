#include "LedBlink.h"
#include "common.h"

// #define SERIAL_SPEED 115200

#define RED_LED_PIN D2
#define GREEN_LED_PIN D3
#define BLUE_LED_PIN D4

extern Blinker blinker_r;
extern Blinker blinker_g;
extern Blinker blinker_b;

void disableAllBlinkers();
void setBlinkParameters(Blinker &bl, byte numOfBlinks);
void blink();