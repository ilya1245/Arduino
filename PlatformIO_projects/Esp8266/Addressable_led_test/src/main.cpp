#include <FastLED.h>

#define LED_PIN     D5
#define NUM_LEDS    14   // в твоей ленте 60 диодов = 20 адресных "пикселей"
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
}

void redWave() {
  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Red;
    FastLED.show();
    delay(500);
    leds[i] = CRGB::Black;
  }
}

void rainbowWave() {
  static uint8_t hue = 0;   // переменная для оттенка (0..255)

  // Заполняем всю ленту градиентом
  fill_rainbow(leds, NUM_LEDS, hue, 7);

  FastLED.show();
  hue++;                    // меняем оттенок (будет плавный переход)
  delay(20); 
}

void loop() {
  rainbowWave();
}


