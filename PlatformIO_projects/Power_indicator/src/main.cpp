#include <ESP8266WiFi.h>
#include <GyverTimer.h>

#include "common.h"
#include "blink.h"

String  otherWiFis[] = {"Tenda", "TP-LINK", "TP-Link", "DV", "yura", "Sania", "MILA", "22", "JULIA", "boba", "Basb", "Арсен", "Alex", "rydi", "HOME_30"};
String  myWifi = "CoolWave";

GTimer timer_5s(MS, 5000);

byte otherWiFiNumber = 0;

void setup() {
  Serial.begin(SERIAL_SPEED);
  disableAllBlinkers();
}

byte getOtherWiFiStatus() {
  otherWiFiNumber = 0;
  byte wifiStatus = 0;
  int numberOfWifi = WiFi.scanNetworks(false, true);
  Serial.printf("\n\nNumber of WiFi networks: %d", numberOfWifi);
  if(numberOfWifi >= 4) wifiStatus = 1;  
  if(numberOfWifi >= 6) wifiStatus = 2; 
    
  for(int i = 0; i < numberOfWifi; i++) {
    String curWiFi = WiFi.SSID(i);
    Serial.printf("\nCurrent SSID: %s", curWiFi.c_str());
    for(size_t j = 0; j < sizeof(otherWiFis)/sizeof(otherWiFis[0]); j++) {
//      Serial.printf("\nSearching for: %s", otherWiFis[j]);
      if(curWiFi.indexOf(otherWiFis[j]) >= 0) {
        Serial.printf("\n--- Found %s ---", otherWiFis[j].c_str());
        otherWiFiNumber++;
        if(otherWiFiNumber > 2) wifiStatus = 2;
      }
    }
  } 
  
  Serial.printf("\nwifiStatus: %d", wifiStatus);
  return wifiStatus;
}

bool isMyWifiPresent() {
  int numberOfWifi = WiFi.scanNetworks(false, true);
  for(int i = 0; i < numberOfWifi; i++) {
    if(myWifi.equals(WiFi.SSID(i))) {      
      Serial.printf("\n--- Found %s ---", myWifi.c_str());
      return true;
    }
  }
  Serial.printf("\n--- Not found %s ---", myWifi.c_str());
  return false;
}

void showOtherWiFiStatus() {   
  byte wifiStatus = getOtherWiFiStatus();
  Serial.printf("\n--- wifiStatus = %d ---", wifiStatus);
  switch(wifiStatus) {
    case 0:
      setBlinkParameters(blinker_r, 1);
      break;
    case 1:
      setBlinkParameters(blinker_b, 1);
      break;
    case 2:
      setBlinkParameters(blinker_g, otherWiFiNumber);
      break;
  }
}

void loop() {        
  if(timer_5s.isReady()) {
    showOtherWiFiStatus();          
  }
  blink();
}
