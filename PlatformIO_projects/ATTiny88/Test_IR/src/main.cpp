#include <Arduino.h>

#include "common.h"
#include "action.h"

#define TX_PIN 7
#include "ATtinySerialOut.hpp"

#define IR_INPUT_PIN 6
#define IR_FEEDBACK_LED_PIN 5
#include "TinyIRReceiver.hpp"

#include <GyverTimer.h>

GTimer timer_3s(MS, 3000);

int i = 0;

void setup() {
  initTXPin();
  initPCIInterruptForTinyReceiver();
  Serial.println("Ready to receive NEC IR signals at pin " + IR_INPUT_PIN);
}

void loop() {
  if (timer_3s.isReady()) {
    Serial.print("loop ");    
    Serial.println(i);
    i++;
  }  
}

void handleReceivedTinyIRData(uint16_t aAddress, uint8_t aCommand, bool isRepeat) {
  Serial.print("CommanD: ");
  Serial.println(aCommand);
  selectAction(aCommand);
}