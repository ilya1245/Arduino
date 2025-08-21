#include <ir.h>
// #include <ledStrip.h>

NecDecoder ir;
boolean isPrintKeyCode = true;

void irIsr() {
  ir.tick();  
}

void processIr() {
  // Serial.println("\nprocessIr()");
  // delay(waveStepDelay);
  if (ir.available()) {
    // Serial.println("\nprocessIr() if");
    if(isPrintKeyCode) printf("\nKeyCode: %d\n", ir.readCommand());
    // if(isPrintKeyCode) {
    //   Serial.print("\nKeyCode: ");
    //   Serial.println(ir.readCommand());
    // }

    digitalWrite(RECV_LED_PIN, HIGH);
    delay(20);
    digitalWrite(RECV_LED_PIN, LOW);

    switch(ir.readCommand()) {
      case 2: // ok          
          isOn = !isOn; 
          printf("\nisOn: %d\n", isOn);      
          break;

      case 98: // up - faster wave           
          if (waveStepDelay > WAVE_STEP_DELAY_MIN) waveStepDelay -= WAVE_STEP_DELAY_STEP; 
          printf("\nwaveStepDelay = %d\n", waveStepDelay);    
          ledStepTimer.setInterval(waveStepDelay);  
          break;
      case 168: // down - slower wave           
          if (waveStepDelay < WAVE_STEP_DELAY_MAX) waveStepDelay += WAVE_STEP_DELAY_STEP; 
          printf("\nwaveStepDelay = %d\n", waveStepDelay); 
          ledStepTimer.setInterval(waveStepDelay);     
          break;

      case 34: // left - shorter wave           
          if (waveGradient < WAVE_GRADIENT_MAX) waveGradient += WAVE_GRADIENT_STEP; 
          printf("\nwaveGradient = %d\n", waveGradient);     
          break;
      case 194: // right - longer wave           
          if (waveGradient > WAVE_GRADIENT_MIN) waveGradient -= WAVE_GRADIENT_STEP; 
          printf("\nwaveGradient = %d\n", waveGradient);     
          break;

      case 82: // hash
          writeSettings();
          break;
      case 66: // star -  write Default Settings
          writeDefaultSettings();
          ledStepTimer.setInterval(waveStepDelay);
          break;
      default: // auto
        break;  
    }
  } else {
    // delay(waveStepDelay);
  }
}