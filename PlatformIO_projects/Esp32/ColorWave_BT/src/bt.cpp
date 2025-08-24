#include "bt.h"

BluetoothSerial SerialBT;

int mode = 0;

void setWaveStepDelay(int speed) {
  printf("speed: %dMs\n", speed);
  waveStepDelay = WAVE_STEP_DELAY_MAX - int((WAVE_STEP_DELAY_MAX - WAVE_STEP_DELAY_MIN)*speed/100);
  ledStepTimer.setInterval(waveStepDelay);
}

void setWaveGradient(int length) {
  printf("length: %d\n", length);
  waveGradient = WAVE_GRADIENT_MAX - int((WAVE_GRADIENT_MAX - WAVE_GRADIENT_MIN)*length/100);
}

// Разбор команд
void processBtCommand(String cmd) {
  printf("\ncmd: %s\n", cmd);
  cmd.trim();  

  if (cmd == "ON") {
    Serial.print("Включено");
    isOn = true; 
    printf("\nisOn: %d\n", isOn);   
  } else if (cmd == "OFF") {
    Serial.print("Выключено");
    isOn = false;
    printf("\nisOn: %d\n", isOn); 
    FastLED.clear();    
    FastLED.show(); 
  } else if (cmd.startsWith("SPEED:")) {
    setWaveStepDelay(cmd.substring(6).toInt());
    printf("waveStepDelay: %dMs\n", waveStepDelay);    
  } else if (cmd.startsWith("LENGTH:")) {
    setWaveGradient(cmd.substring(7).toInt());
    printf("waveGradient: %d\n", waveGradient);
  } else if (cmd == "Reset") {
    Serial.println("Reset");
    writeDefaultSettings();
  } else if (cmd == "Save") {
    Serial.println("Save");
    writeSettings();
  }
}

void processBt() {
  // Читаем команды с телефона
  if (SerialBT.available()) {
    String cmd = SerialBT.readStringUntil('\n');
    processBtCommand(cmd);
  }
}

