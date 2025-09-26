#include "ledStrip.h"

CRGB leds[NUM_LEDS];

void showBar(int level) {
  Serial.printf("\nlevel = %d", level);
  for (int i = 0; i < NUM_LEDS; i++) {    
    if (i < level) {
      // hue: от зелёного (96) → жёлтый → красный (0)
      uint8_t hue = map(i, 0, NUM_LEDS - 1, -86, 0); //200, 0
      Serial.printf("\ni = %d   hue = %d\n", level, hue);
      leds[i] = CHSV(hue, 255, 255);
    } else {
      leds[i] = CRGB::Black;
    }
  }
  FastLED.show();
}

void slowBar() {
  for (int i = 1; i <= NUM_LEDS; i++) {
    showBar(i);
    delay(100);
  }
}

int getBarLevel(int micValue) {
  float sqrt_diff = 0;
  if (micValue > MIN_SOUND_LEVEL) {
    sqrt_diff = sqrt(micValue - MIN_SOUND_LEVEL) * SOUND_SCALE;
  }
  Serial.printf("\nsqrt_diff = %f", sqrt_diff);

  return int(constrain(sqrt_diff, 0, NUM_LEDS));
}
