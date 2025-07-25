#include <Arduino.h>
#include <math.h>

#define PWM_PIN 5  // Например, D5 = PD4 на STM8S103F3

int pwmMinValue = 30;
int pwmMaxValue = 255;

void setup() {
  pinMode(PWM_PIN, OUTPUT);  // Просто OUTPUT, этого достаточно
}

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

// void wave_2_1() {
//   unsigned char pwmWaveValue;
//   // byte pwmStep = 2;

//   unsigned char i = 0;
//   float angle;

//   while (true) {
//     angle = (i++ * 2 * PI) / 255;
//     // Serial_println_float(angle);
//     pwmWaveValue = pwmMinValue + (1 - abs(cosf(angle))) * (pwmMaxValue - pwmMinValue);
//     // pwmWaveValue = (unsigned char)(1 - cosf(angle)) * (pwmMaxValue - pwmMinValue);
//     analogWrite(PWM_PIN, pwmWaveValue);
//     delay(20); //slow down the wave
//   }
// }

void wave_2() {
  unsigned char pwmWaveValue;
  // byte pwmStep = 2;

  unsigned char i = 0;
  float angle;

  while (true) {
    angle = (i++ * PI) / 255;
    // Serial_println_float(angle);
    pwmWaveValue = pwmMinValue + (unsigned char)(sinf(angle) * (220));
    // pwmWaveValue = (unsigned char)(1 - cosf(angle)) * (pwmMaxValue - pwmMinValue);
    analogWrite(PWM_PIN, -pwmWaveValue);
    delay(20); //slow down the wave
  }
}

void loop() {
  wave_2();

  // float x = 1.0;
  // float y = cosf(x);
  // // Serial_println_float(y);
  // delay(1000);
}



