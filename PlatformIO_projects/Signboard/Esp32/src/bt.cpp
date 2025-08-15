#include "bt.h"
#include "action.h"

BluetoothSerial SerialBT;

int mode = 0;

// Разбор команд
void processBtCommand(String cmd) {
  Serial.printf("cmd: %s\n", cmd);
  cmd.trim();  

  if (cmd == "ON") {
    isOn = true;
    Serial.println("Включено");
    onOff(true);
  } 
  else if (cmd == "OFF") {
    isOn = false;
    Serial.println("Выключено");
    onOff(false);
    // return();
  }
  else if (cmd.startsWith("MODE:")) {
    mode = cmd.substring(5).toInt();
    Serial.printf("Выбран режим: %d\n", mode);
    processMode(mode);
  } 
  else if (cmd.startsWith("UPPER:")) {
    pwmHighValue = cmd.substring(6).toInt();
    Serial.printf("Верхняя яркость: %d%%\n", pwmHighValue);    
  } 
  else if (cmd.startsWith("LOWER:")) {
    pwmLowValue = cmd.substring(6).toInt();
    Serial.printf("Нижняя яркость: %d%%\n", pwmLowValue);
  } 
  else if (cmd.startsWith("INTERVAL:")) {
    timeInterval = cmd.substring(9).toInt() * 10;
    Serial.printf("Интервал мерцания: %d%%\n", timeInterval);
  }   
  else if (cmd == "Reset") {
    Serial.println("Reset");
    writeDefaultSettings();
  } 
  else if (cmd == "Save") {
    Serial.println("Save");
    writeSettings();
  }
}

// void processMode(int mode) {

// }

void processBt() {
  // Читаем команды с телефона
  if (SerialBT.available()) {
    String cmd = SerialBT.readStringUntil('\n');
    processBtCommand(cmd);
  }
}