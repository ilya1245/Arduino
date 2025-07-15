#include <Arduino.h>
#include <ir.h>

NecDecoder ir;
boolean isPrintKeyCode = true;

void irIsr() {
  ir.tick();  
}

void processIr() {
  if (ir.available()) {
    // digitalWrite(IR_SENSOR_PIN, 1);
    // delay(20);
    // digitalWrite(IR_SENSOR_PIN, 0);
    // lightTimer.stop();

    // controlLightByState();
    if(isPrintKeyCode) printf("KeyCode: %d   \n", ir.readCommand());

    switch(ir.readCommand()) {
      // case 2: // ok button
      //     Serial.println("Ok"); 
      //     // lightState = !lightState;
      //     setMode(1);                   
      //     break;
      // case 98: // up
      //     Serial.println("Up"); 
      //     // if (pwmValue < 250) pwmValue += 10;         
      //     break;
      // case 168: // down
      //     Serial.println("Down");
      //     // if (pwmValue > pwmMinValue) pwmValue -= 10;
      //     break;
      case 104: // star          
          setMode(1); // on the watch system       
          break;
      // case 152: // 2
      //     setMode(2);
      //     break;
      case 176: // hash
          setMode(0); // off the watch system
          break;
      default: // auto
        break;  
    }
  }  
}