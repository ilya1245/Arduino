#include <Arduino.h>

#define IR_PIN 2  // PD3

int putchar(int c) {
  Serial_write(c);
  return c;
}

uint32_t readIRCode() {
  // Ждём начала сигнала
  while (digitalRead(IR_PIN) == HIGH);

  // Измеряем длину LOW-старта (должен быть ~9мс)
  unsigned long start = micros();
  while (digitalRead(IR_PIN) == LOW);
  unsigned long mark = micros() - start;

  // Проверка: это действительно начало сигнала?
  if (mark < 8000 || mark > 10000) return 0;

  // Ждём HIGH (~4.5мс)
  start = micros();
  while (digitalRead(IR_PIN) == HIGH);
  mark = micros() - start;
  if (mark < 4000 || mark > 5000) return 0;

  // Считываем 32 бита
  uint32_t code = 0;
  for (int i = 0; i < 32; i++) {
    // Ждём LOW (~560 мкс)
    while (digitalRead(IR_PIN) == LOW);

    // Измеряем HIGH
    start = micros();
    while (digitalRead(IR_PIN) == HIGH);
    mark = micros() - start;

    // Если HIGH > 1000 мкс, это 1, иначе 0
    code <<= 1;
    if (mark > 1000) code |= 1;
  }

  return code;
}

void setup() {
  Serial_begin(9600);
  pinMode(IR_PIN, INPUT);
  printf("IR receiver ready\n");
}

uint32_t lastCode = 0;
uint32_t lastTime = 0;

void loop() {
  uint32_t irCode = readIRCode();  // ваша функция чтения IR

  if (irCode == 0) {
    return;  // ничего не пришло
  }

  if (irCode == 4294967295UL) {
    // повтор — используем lastCode
    irCode = lastCode;
  } else {
    // новое нажатие
    lastCode = irCode;
  }

  // Обработка нажатий
  printf("IR code: %lu\n", irCode);

  if (irCode == 2155836045UL) {
    printf("Key 1\n");
  } else if (irCode == 2155851855UL) {
    printf("Key 2\n");
  } else if (irCode == 2155819215UL) {
    printf("Key 3\n");
  }

  delay(100);  // Защита от повторной обработки
}
