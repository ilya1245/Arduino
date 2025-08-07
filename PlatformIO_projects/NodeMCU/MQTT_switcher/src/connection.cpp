#include <connection.h>
#include <blink.h>


WiFiClient espClient;
PubSubClient mqttClient(espClient);

std::pair <char*, char*> wifi_prim("CoolWave", "zlgk8e-1"); 
std::pair <char*, char*> wifi_sec_1("Redmi_4", "cat_7032");
std::pair <char*, char*> wifi_sec_2("S40", "12345123");
std::pair<char*, char*> my_wifis[] = {wifi_prim, wifi_sec_1, wifi_sec_2};
WiFiMultiStable wiFiMultiStable(my_wifis, sizeof(my_wifis)/sizeof(my_wifis[0]), &Serial, SERIAL_SPEED);
int activeWifiId = -1;

void callback(char* topic, byte* payload, unsigned int length) {
  payload[length] = '\0';  // превращаем в строку
  String message = String((char*)payload);
  
  if (String(topic) == MQTT_LED_COMMAND_TOPIC) {
    if (message == "ON") {
      digitalWrite(LED_PIN, HIGH);  // активный LOW на ESP8266
      mqttClient.publish(MQTT_LED_STATE_TOPIC, "ON");
    } else {
      digitalWrite(LED_PIN, LOW);
      mqttClient.publish(MQTT_LED_STATE_TOPIC, "OFF");
    }
  }
}

void connectClientIfNeeded() {
  while (!mqttClient.connected()) {
    Serial.println("connectClientIfNeeded() - reconnect");
    if (mqttClient.connect(MQTT_CLIENT_ID)) {
      Serial.println("connectClientIfNeeded() - connected");
      mqttClient.subscribe(MQTT_LED_COMMAND_TOPIC);
    } else {
      delay(5000);
    }
  }
}

void connectToMQTT() { 
  printf("\nconnectToMQTT()"); 
  setBlinkParameters(blinkerWifiSearch, 1);
  wiFiMultiStable.connectToWifi();
  activeWifiId = wiFiMultiStable.getActiveWifiId();
  printf("\nactiveWifiId: %d", activeWifiId);
  if(activeWifiId >= 0) {
    connectClientIfNeeded();
    setBlinkParameters(blinkerWifiOk, activeWifiId+1);
  }
}