// #include <LibPrintf.h>
#include <connection.h>
#include <blink.h>


WiFiClient espClient;
PubSubClient client(espClient);

std::pair <char*, char*> wifi_prim("CoolWave", "zlgk8e-1"); 
std::pair <char*, char*> wifi_sec_1("Redmi_4", "cat_7032");
std::pair <char*, char*> wifi_sec_2("S40", "12345123");
std::pair<char*, char*> my_wifis[] = {wifi_prim, wifi_sec_1, wifi_sec_2};
WiFiMultiStable wiFiMultiStable(my_wifis, sizeof(my_wifis)/sizeof(my_wifis[0]), &Serial, SERIAL_SPEED);
int activeWifiId = -1;

// const char* mqttServer = "imiflig.site"; // IP твоего брокера

const char* mqttTopicStatus = "esp/status";

bool isConnected = false;



void reconnect() {
  Serial.println("reconnect()");
  while (!client.connected()) {
    client.connect("ESP01Client");
  }
  Serial.println("reconnect() - Done");
}

void connectToMQTT() { 
  printf("\nconnectToWifi()"); 
  setBlinkParameters(blinkerWifiSearch, 1);
  isConnected = false;
  wiFiMultiStable.connectToWifi();
  activeWifiId = wiFiMultiStable.getActiveWifiId();
  printf("\nFeeder: activeWifiId: %d", activeWifiId);
  if(activeWifiId >= 0) {
    reconnect();
    isConnected = true;
    setBlinkParameters(blinkerWifiOk, activeWifiId+1);
  }
}