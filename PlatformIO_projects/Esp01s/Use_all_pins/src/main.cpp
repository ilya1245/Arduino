#include <Arduino.h>
#include <map>

std::map<int, int> ledPins = { {0, 0}, {1, 1}, {2, 2}, {3, 3} }; // 1- TX, 3 - RX
// std::map<int, int> ledPins = { {0, D0}, {1, D1}, {2, D2}, {3, D3} };

void setup() { 
  for (int i = 0; i < 4; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }
}

void loop() {
  while(true) {
    for (int i = 0; i < 4; i++) {
      digitalWrite(ledPins[i], HIGH);
      delay(500);
      digitalWrite(ledPins[i], LOW);
      delay(500);
    }
  } 
}
