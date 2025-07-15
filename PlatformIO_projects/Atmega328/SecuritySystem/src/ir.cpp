#include <Arduino.h>
#include <ir.h>

NecDecoder ir;
boolean isPrintKeyCode = true;

void irIsr() {
  ir.tick();  
}

void processIr() {
  if (ir.available()) {
    if(isPrintKeyCode) printf("KeyCode: %d   \n", ir.readCommand());

    switch(ir.readCommand()) {
      case 104: // star          
          setMode(1); // on the watch system       
          break;
      case 176: // hash
          setMode(0); // off the watch system
          break;
      default: // auto
        break;  
    }
  }  
}