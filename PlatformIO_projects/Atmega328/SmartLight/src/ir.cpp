#include <Arduino.h>
#include <ir.h>

NecDecoder ir;
boolean isPrintKeyCode = true;

void irIsr() {
  ir.tick();  
}

void processIr() {
  if (ir.available()) {
    digitalWrite(RED_LED_PIN, 1);
    delay(20);
    digitalWrite(RED_LED_PIN, 0);
    lightTimer.stop();

    controlLightByState();
    if(isPrintKeyCode) printf("KeyCode: %d   \n", ir.readCommand());

    switch(ir.readCommand()) {
      case 2: // ok button
          Serial.println("Ok"); 
          lightState = !lightState;
          setMode(1);                   
          break;
      case 98: // up
          Serial.println("Up"); 
          if (mode != 3) {
            if (pwmValue < 250) pwmValue += 10;   
          } else {
            soudLevelThreshold++;
          }      
          break;
      case 168: // down
          Serial.println("Down");
          if (mode != 3) {
            if (pwmValue > pwmMinValue) pwmValue -= 10;
          } else {
            soudLevelThreshold--;
          } 
          break;
      case 104: // 1          
          setMode(1);        
          break;
      case 152: // 2
          setMode(2);
          break;
      case 176: // 3
          setMode(3);
          break;
      default: // auto
        break;  
    }
  }  
}