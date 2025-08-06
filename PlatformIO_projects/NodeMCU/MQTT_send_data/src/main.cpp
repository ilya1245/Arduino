// #include <WiFiMultiStable.h>
#include <blink.h>
#include <connection.h>

void setup() { 
  Serial.begin(SERIAL_SPEED);
  wiFiMultiStable.setLogLevel(2);  
  mqttClient.setServer(MQTT_SERVER, MQTT_PORT);
  connectToMQTT();  
} 

void loop() {

  if(timer_3s.isReady()) {
    if(wiFiMultiStable.isPingWork()) {     
      Serial.println("\nFeeder: Ping is ok.");  
      // isConnected ? client.loop() : connectToHomeAssistan();
      if (isConnected) {
        // client.loop();
        printf("\nisConnected: %d", isConnected);
      } else {
        connectToMQTT();
      }
    }               
  }

  if(timer_5m.isReady() && activeWifiId != 0) {
    Serial.println("\nReconnecting to Wifi.");    
    connectToMQTT();
    // timeClient.update();
  }
     
  if(timer_10s.isReady()) { 
    Serial.println("\nSending data");
    connectClientIfNeeded();
    mqttClient.loop();

    char status[32];  // буфер для итогового сообщения
    snprintf(status, sizeof(status), "Привет_%d", count++);
    mqttClient.publish(mqttTopicStatus, status);
    
    Serial.println(status);
  }
  
  blink();
}
