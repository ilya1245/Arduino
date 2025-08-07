#include <blink.h>
#include <connection.h>

void setup() { 
  Serial.begin(SERIAL_SPEED);

  wiFiMultiStable.setLogLevel(2);  
  blinkerWifiOk.setInvertBlinking(true);
  blinkerWifiSearch.setInvertBlinking(true);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  mqttClient.setServer(MQTT_SERVER, MQTT_PORT);
  mqttClient.setCallback(callback);
  connectToMQTT();  
} 

void loop() {

  if(timer_3s.isReady()) {
    if(wiFiMultiStable.isPingWork()) {     
      Serial.println("\nFeeder: Ping is ok.");  
      if (activeWifiId < 0) {
        connectToMQTT();
      }
    }               
  }

  if(timer_5m.isReady() && activeWifiId != 0) {
    Serial.println("\nReconnecting to Wifi.");    
    connectToMQTT();
    // timeClient.update();
  }

  mqttClient.loop();  
  blink();
}
