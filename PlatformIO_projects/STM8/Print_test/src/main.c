#include <Arduino.h>
#include <stdio.h>

// Переопределяем putchar, чтобы работал printf
int putchar(int c) {
  Serial_write(c);
  return c;
}

void setup() {
  Serial_begin(9600);
  delay(100);  // немного подождать запуска
  printf("STM8 Serial test OK\n");
}

void loop() {
  static uint32_t counter = 0;
  printf("Counter: %lu\n", counter++);
  delay(1000);  // 1 секунда
}
