#include <ir.h>

uint32_t lastCode = 0;

uint32_t readIRCode() {
  // Ждём начала сигнала
  while (digitalRead(RECV_PIN) == HIGH && millis() % 100 != 0);

  // LOW ~9мс
  unsigned long start = micros();
  while (digitalRead(RECV_PIN) == LOW);
  unsigned long mark = micros() - start;

  // printf(mark);
  // printf("mark: %lu\n", mark);

  if (mark < 8000 || mark > 10000) return 0;

  // HIGH
  start = micros();
  while (digitalRead(RECV_PIN) == HIGH);
  mark = micros() - start;

  // Повторный кадр: 2.25 мс HIGH
  if (mark > 2000 && mark < 2500) {
    // NEC repeat frame
    return 0xFFFFFFFF;
  }

  // Обычный кадр: 4.5 мс HIGH
  if (mark < 4000 || mark > 5000) return 0;

  // Чтение 32 бит
  uint32_t code = 0;
  for (int i = 0; i < 32; i++) {
    while (digitalRead(RECV_PIN) == LOW);
    start = micros();
    while (digitalRead(RECV_PIN) == HIGH);
    mark = micros() - start;

    code <<= 1;
    if (mark > 1000) code |= 1;
  }

  return code;
}

void processIr() {
  uint32_t irCode = readIRCode();  // ваша функция чтения IR

  if (irCode == 0) {
    // printf("Nothing\n");
    return;  // ничего не пришло
  }

  // Обработка нажатий
  // printf("IR code: %lu\n", irCode);

  if (irCode == 4294967295UL) {
    // повтор — используем lastCode
    // printf("Repeat\n");
    irCode = lastCode;
  } else {
    // новое нажатие
    lastCode = irCode;
  }  

  switch(irCode) {
    case 2155807485UL: // On/Off    
      printf("On/Off\n");      
      mode == 0 ? setMode(1) : setMode(0); // on the watch system  
      // isKeyPressed = true;  
      break;
    case 2155836045UL: // Key 1 - increase bottom pwm level
      printf("Key 1\n");
      pwmMinValue += pwmStep;
      break; 
    case 2155827885UL: // Key 4 - decrease bottom pwm level
      printf("Key 4\n");
      if (pwmMinValue >= pwmStep) pwmMinValue -= pwmStep;
      break; 

    case 2155819215UL: // Key 3 - increase top pwm level
      printf("Key 3\n");
      if (pwmMaxValue <= 255 - pwmStep) pwmMaxValue += pwmStep;
      break; 
    case 2155811055UL: // Key 6 - decrease top pwm level
      printf("Key 6\n");
      pwmMaxValue -= pwmStep;
      break;  
  }
  
  delay(100);  // Защита от повторной обработки 
}