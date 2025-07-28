#include "common.h"

// int mode = 1; 

byte pwmMaxValue = 100;
byte pwmMinValue = 30;

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

// void wave_1() {
//   // Увеличиваем яркость
//   for (int i = pwmMinValue; i < pwmMaxValue; i++) {
//     analogWrite(PWM_PIN, i);
//     delay(10);
//   }

//   // Уменьшаем яркость
//   for (int i = pwmMaxValue; i >= pwmMinValue; i--) {
//     analogWrite(PWM_PIN, i);
//     delay(10);
//   }
// }

float bhaskara_sin(float x_deg) {
    if (x_deg < 0) x_deg = -x_deg;
    x_deg = x_deg - ((int)(x_deg / 360.0f)) * 360.0f;
    if (x_deg > 180.0) x_deg = 360.0 - x_deg;
    float x = x_deg;
    return (4.0f * x * (180.0f - x)) / (40500.0f - x * (180.0f - x));
}

float bhaskara_cos(float x_deg) {
    return bhaskara_sin(90.0f - x_deg);
}

void wave_3() {
  byte pwmWaveValue;
  byte i = 0;
  float angle;

  while (true) {
    angle = (i++ * 180.0f) / 255;
    pwmWaveValue = pwmMinValue + (byte)((1 - abs(bhaskara_cos(angle))) * (pwmMaxValue - pwmMinValue));
    analogWrite(PWM_PIN, pwmWaveValue);
    delay(20); //slow down the wave
  }
}

// void wave_2() {
//   byte pwmWaveValue;
//   byte i = 0;
//   float angle;

//   while (true) {
//     angle = (i++ * 2 * PI) / 255;
//     // Serial_println_float(angle);
//     // pwmWaveValue = pwmMinValue + (unsigned char)(sinf(angle) * (220));
//     pwmWaveValue = pwmMinValue + (byte)((1 - abs(cosf(angle))) * (pwmMaxValue - pwmMinValue));
//     analogWrite(PWM_PIN, pwmWaveValue);
//     delay(40); //slow down the wave
//   }
// }