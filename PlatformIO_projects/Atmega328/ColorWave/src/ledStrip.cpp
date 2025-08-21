#include "ledStrip.h"
#include "ir.h"

CRGB leds[NUM_LEDS];
GTimer ledStepTimer(MS);

uint8_t hue = 0;
int waveStepDelay; 
int waveGradient;
int baseColorStep;

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
  // Заполняем всю ленту градиентом
  fill_rainbow(leds, NUM_LEDS, hue, waveGradient);
  processIr();
  FastLED.show();
  processIr();
  hue += baseColorStep;                    // меняем оттенок (будет плавный переход)
  processIr();
}

// void rainbowWave_2() {
//   // static uint8_t hue = 0;                // оттенок
//   static unsigned long lastUpdate = 0;   // время последнего обновления
//   const uint16_t interval = 20;          // обновлять каждые 20 мс (~50 FPS)

//   // проверяем, прошло ли достаточно времени
//   if (millis() - lastUpdate >= waveStepDelay) {
//     fill_rainbow(leds, NUM_LEDS, hue, waveGradient);  // рисуем радугу
//     FastLED.show();                        // отправляем в ленту

//     hue += baseColorStep;            // смещение оттенка (скорость анимации)
//     lastUpdate = millis();
//   }
// }