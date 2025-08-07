#include "blink.h"
#include "connection.h"
#include "processData.h"

void setup() { 
  Serial.begin(SERIAL_SPEED);
  Serial.println("\nsetup()");
  wiFiMultiStable.setLogLevel(2);
  // blinkerWifiOk.setInvertBlinking(true);
  // blinkerWifiSearch.setInvertBlinking(true);
  mqttClient.setServer(MQTT_SERVER, MQTT_PORT);
  connectToMQTT();  
} 

void loop() {
  // Serial.println("\nloop()");
  if(timer_3s.isReady()) {
    if(wiFiMultiStable.isPingWork()) {     
      Serial.println("\nPing is ok.");  
    } else {
      connectToMQTT();
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
    processSensorData();
  }
  
  mqttClient.loop();
  blink();
}
