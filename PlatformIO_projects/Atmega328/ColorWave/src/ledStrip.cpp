#include "ledStrip.h"
#include "ir.h"

CRGB leds[NUM_LEDS];
GTimer ledStepTimer(MS);

int waveStepDelay; 
int waveGradient;


void redWave() {
  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Red;
    FastLED.show();
    delay(500);
    leds[i] = CRGB::Black;
  }
}

void rainbowWave() {
  processIr();
  static uint8_t hue = 0;   // переменная для оттенка (0..255)
  processIr();
  // Заполняем всю ленту градиентом
  fill_rainbow(leds, NUM_LEDS, hue, waveGradient);
  processIr();
  FastLED.show();
  processIr();
  hue += 3;                    // меняем оттенок (будет плавный переход)
  processIr();
  // delay(waveStepDelay); 
}