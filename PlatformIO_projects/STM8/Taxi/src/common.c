#include "common.h"

// int mode = 1; 

byte pwmMaxValue = 255;
byte pwmMinValue = 10;

int putchar(int c) {
  Serial_write(c);
  return c;
}

// void setMode(int m) {
//   // if (mode == m) return;
//   mode = m;
//   // Serial.print("Mode ");
//   // Serial.println(mode);
// }

void wave_1() {
  // Увеличиваем яркость
  for (int i = pwmMinValue; i < pwmMaxValue; i++) {
    analogWrite(PWM_PIN, i);
    delay(10);
  }

  // Уменьшаем яркость
  for (int i = pwmMaxValue; i >= pwmMinValue; i--) {
    analogWrite(PWM_PIN, i);
    delay(10);
  }
}

void wave_2() {
  byte pwmWaveValue;
  byte i = 0;
  float angle;

  while (true) {
    angle = (i++ * 2 * PI) / 255;
    // Serial_println_float(angle);
    // pwmWaveValue = pwmMinValue + (unsigned char)(sinf(angle) * (220));
    pwmWaveValue = pwmMinValue + (byte)((1 - abs(cosf(angle))) * (pwmMaxValue - pwmMinValue));
    analogWrite(PWM_PIN, pwmWaveValue);
    delay(40); //slow down the wave
  }
}