#include "common.h"
#include "ledStrip.h"

float scale = 4.0;
int currentLevel = 0;
int micValue = 0;




void setup() {
  Serial.begin(115200);
  FastLED.addLeds<LED_TYPE, LED_ADDRESS_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  slowBar();
}

void updateBarLevel() {
  float sqrt_diff = 0;
  if (micValue > MIN_SOUND_LEVEL) {
    sqrt_diff = sqrt(micValue - MIN_SOUND_LEVEL) * scale;
  }
  Serial.printf("\nsqrt_diff = %f", sqrt_diff);
  // Serial.println(sqrt_diff); 

  // if (sqrt_diff > currentLevel) {
    currentLevel = int(sqrt_diff);
  // } 
  // else {
  //   currentLevel--;
  // }
  
  currentLevel = constrain(currentLevel, 0, NUM_LEDS);

}

void loop() {
  if (barTimer.isReady()) {
    Serial.printf("\nmicValue = %d", micValue);
    updateBarLevel();
    showBar(currentLevel);
     micValue = 0;
  } else {
    micValue = micValue < analogRead(MIC_PIN) ? analogRead(MIC_PIN) : micValue;
  }

}
