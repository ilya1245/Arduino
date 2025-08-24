#include "ledStrip.h"

CRGB leds[NUM_LEDS];
GTimer ledStepTimer(MS);

uint8_t hue = 0;
int waveStepDelay; 
int waveGradient;
// int baseColorStep;

void redWave() {
  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Red;
    FastLED.show();
    delay(500);
    leds[i] = CRGB::Black;
  }
}

void rainbowWave() {
  fill_rainbow(leds, NUM_LEDS, hue, waveGradient);
  FastLED.show();
  hue += 1; // меняем оттенок (будет плавный переход)
}
