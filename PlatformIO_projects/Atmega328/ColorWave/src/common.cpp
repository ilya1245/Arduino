#include "common.h"

boolean isOn;
int keyCode;

void shortBeep(int beeps) {
  for (int i = 0; i < beeps; i++) {
    digitalWrite(BEEP_SIGNAL_PIN, 1);  
    delay(50);
    digitalWrite(BEEP_SIGNAL_PIN, 0);
    delay(100);
  }
}
