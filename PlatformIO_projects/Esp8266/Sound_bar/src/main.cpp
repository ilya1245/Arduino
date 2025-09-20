#include <FastLED.h>

#define LED_PIN     D2       // GPIO4
#define NUM_LEDS    20
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB

CRGB leds[NUM_LEDS];

#define MIC_PIN     A0       // аналоговый вход ESP8266 (0–1V!)
#define BRIGHTNESS  200

// Задаём рабочий диапазон микрофона
#define MIN_SOUND_LEVEL  300   // тихо
#define MAX_SOUND_LEVEL  315   // громко

void setup() {
  Serial.begin(115200);
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
}

void loop() {
  // 1. Чтение микрофона
  int micValue = analogRead(MIC_PIN);    // 0..1023
  Serial.println(micValue);

  static int smoothValue = MIN_SOUND_LEVEL;
  smoothValue = (smoothValue * 7 + micValue) / 8;  // простое сглаживание

  // 2. Масштабируем из 700–800 в 0–NUM_LEDS
  int level = map(smoothValue, MIN_SOUND_LEVEL, MAX_SOUND_LEVEL, 0, NUM_LEDS);

  // защита от выхода за пределы
  level = constrain(level, 0, NUM_LEDS);

  // 3. Заполняем диоды
  for (int i = 0; i < NUM_LEDS; i++) {
    if (i < level) {
      // hue: от зелёного (96) → жёлтый → красный (0)
      uint8_t hue = map(i, 0, NUM_LEDS - 1, 200, 0);
      leds[i] = CHSV(hue, 255, 255);
    } else {
      leds[i] = CRGB::Black;
    }
  }

  // 4. Отправляем в ленту
  FastLED.show();
  delay(20);
}
