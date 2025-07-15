#include <common.h>

GTimer lightTimer(MS, ALARM_ON_TIME);
GTimer soundTimer(MS);
GTimer lcdClearTimer(MS, 3000);

LiquidCrystal_I2C lcd(0x27, 16, 2);

int mode = 0; // ALARM_OFF 
// boolean lightState = false;

byte pwmValue = 255;
byte pwmMinValue = 10;

void setMode(int m) {
  // if (mode == m) return;
  mode = m;
  Serial.print("Mode ");
  Serial.println(mode);
  for (int i = 0; i < mode; i++) {
    digitalWrite(BEEP_SIGNAL_PIN, 1);
    delay(50);
    digitalWrite(BEEP_SIGNAL_PIN, 0);
    delay(100);
  }
}