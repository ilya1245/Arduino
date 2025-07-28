// #include <Arduino.h>
#include <ir.h>

// boolean isPrintKeyCode = true;

uint32_t readIRCode() {
  // Ждём начала сигнала
  while (digitalRead(RECV_PIN) == HIGH && millis() % 100 != 0);

  // LOW ~9мс
  unsigned long start = micros();
  while (digitalRead(RECV_PIN) == LOW);
  unsigned long mark = micros() - start;

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


uint32_t lastCode = 0;

void processIr() {
  uint32_t irCode = readIRCode();  // ваша функция чтения IR

  if (irCode == 0) {
    printf("Nothing\n");
    return;  // ничего не пришло
  }

  // Обработка нажатий
  printf("IR code: %lu\n", irCode);

  if (irCode == 4294967295UL) {
    // повтор — используем lastCode
    printf("Repeat\n");
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
    case 2155836045UL: // Key 1
      printf("Key 1\n");
      break; 
  }
  



  // if (irCode == 2155836045UL) {
  //   printf("Key 1\n");
  // } else if (irCode == 2155851855UL) {
  //   printf("Key 2\n");
  // } else if (irCode == 2155819215UL) {
  //   printf("Key 3\n");
  // } else if (irCode == 2155807485UL) {
  //   printf("On/Off\n");
  // }
  

  delay(100);  // Защита от повторной обработки
  doWave();

  // if (ir.available()) {
  //   digitalWrite(RED_LED_PIN, 1);
  //   delay(20);
  //   digitalWrite(RED_LED_PIN, 0);
  //   lightTimer.stop();

  //   controlLightByState();
  //   if(isPrintKeyCode) printf("KeyCode: %d   \n", ir.readCommand());

  //   switch(ir.readCommand()) {
  //     case 2: // ok button
  //         Serial.println("Ok"); 
  //         lightState = !lightState;
  //         setMode(1);                   
  //         break;
  //     case 98: // up
  //         Serial.println("Up"); 
  //         if (mode != 3) {
  //           if (pwmValue < 250) pwmValue += 10;   
  //         } else {
  //           soudLevelThreshold++;
  //         }      
  //         break;
  //     case 168: // down
  //         Serial.println("Down");
  //         if (mode != 3) {
  //           if (pwmValue > pwmMinValue) pwmValue -= 10;
  //         } else {
  //           soudLevelThreshold--;
  //         } 
  //         break;
  //     case 104: // 1          
  //         setMode(1);        
  //         break;
  //     case 152: // 2
  //         setMode(2);
  //         break;
  //     case 176: // 3
  //         setMode(3);
  //         break;
  //     default: // auto
  //       break;  
  //   }
  // }  
}