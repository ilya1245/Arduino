// #include <Arduino.h>
// #include <math.h>
// #include <common.h>
#include <ir.h>

// #define PWM_PIN 5  // Например, D5 = PD4 на STM8S103F3

// byte pwmMinValue = 30;
// byte pwmMaxValue = 255;

// int putchar(int c) {
//   Serial_write(c);
//   return c;
// }

void setup() {
  Serial_begin(9600);
  pinMode(PWM_PIN, OUTPUT); 
  pinMode(RECV_PIN, INPUT);
  printf("IR receiver ready\n");
}



void loop() {
  // printf("loop()\n");
  processIr();
  wave_3();  
}



