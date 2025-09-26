#include "common.h"
#include "ledStrip.h"

int micValue = 0;

void setup() {
  Serial.begin(115200);
  FastLED.addLeds<LED_TYPE, LED_ADDRESS_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  slowBar();
}

void loop() {
  if (barTimer.isReady()) {
    Serial.printf("\nmicValue = %d", micValue);
    showBar(getBarLevel(micValue));
     micValue = 0;
  } else {
    int analogSignal = analogRead(MIC_PIN);
    if (analogSignal > micValue) {
      micValue = analogSignal;
    }
  }
}
