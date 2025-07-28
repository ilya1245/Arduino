#include "common.h"

int mode = 1; // on

byte pwmMaxValue = 200;
byte pwmMinValue = 10;
byte pwmStep = 5;

int putchar(int c) {
  Serial_write(c);
  return c;
}

void setMode(int m) {
  mode = m;
  // printf("mode: %d\n", mode);
}

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
  // printf("wave_3()\n");
  byte pwmWaveValue;
  byte i = 0;
  float angle;

  while (true) {
    if (mode == 0) return;
    // printf("wave_3() - loop\n");
    i += 2;
    angle = (i * 180.0f) / 255;
    pwmWaveValue = pwmMinValue + (byte)((1 - abs(bhaskara_cos(angle))) * (pwmMaxValue - pwmMinValue));
    analogWrite(PWM_PIN, pwmWaveValue);
    // delay(20); //slow down the wave
    if (i % 10 == 0) processIr();
  }
}

void doWave() {
  // printf("doWave()\n");
  mode == 0 ? digitalWrite(PWM_PIN, LOW) : wave_3();
}
