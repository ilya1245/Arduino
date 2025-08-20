#include "bt.h"
#include "action.h"

BluetoothSerial SerialBT;

int mode = 0;

// Разбор команд
void processBtCommand(String cmd) {
  Serial.printf("cmd: %s\n", cmd);
  cmd.trim();  

  if (cmd == "ON") {
    Serial.println("Включено");
    onOff(true);
  } else if (cmd == "OFF") {
    Serial.println("Выключено");
    onOff(false);
  } else if (cmd.startsWith("UPPER:")) {
    pwmHighValue = cmd.substring(6).toInt();
    Serial.printf("Верхняя яркость: %d%%\n", pwmHighValue*100/pwmMaxValue);    
  } else if (cmd.startsWith("LOWER:")) {
    pwmLowValue = cmd.substring(6).toInt();
    Serial.printf("Нижняя яркость: %d%%\n", pwmLowValue*100/pwmMaxValue);
  } else if (cmd.startsWith("INTERVAL:")) {
    timeInterval = cmd.substring(9).toInt() * 10;
    Serial.printf("Интервал мерцания: %d%%\n", timeInterval/10);
  } else if (cmd == "Reset") {
    Serial.println("Reset");
    writeDefaultSettings();
  } else if (cmd == "Save") {
    Serial.println("Save");
    writeSettings();
  }

  if (cmd.startsWith("MODE:") && isOn) {
    mode = cmd.substring(5).toInt();
    Serial.printf("Выбран режим: %d\n", mode);    
  } 
  processMode(mode);
}

void processBt() {
  // Читаем команды с телефона
  if (SerialBT.available()) {
    String cmd = SerialBT.readStringUntil('\n');
    processBtCommand(cmd);
  }
}