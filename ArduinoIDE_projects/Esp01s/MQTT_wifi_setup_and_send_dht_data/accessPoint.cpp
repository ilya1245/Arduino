#include "common.h"
#include "accessPoint.h"
#include "blink.h"
#include "store.h"


ESP8266WebServer apServer(80);
String wifiListHTML;
bool apMode = false;

// Сканирование сетей Wi-Fi
void scanNetworks() {
  Serial.println("Scanning WiFi...");
  int n = WiFi.scanNetworks();
  wifiListHTML = "<select name='ssid'>";
  for (int i = 0; i < n; i++) {
    String ssid = WiFi.SSID(i);
    wifiListHTML += "<option value='" + ssid + "'";
    if (ssid == ssidStored) wifiListHTML += " selected";
    wifiListHTML += ">" + ssid + " (" + String(WiFi.RSSI(i)) + " dBm)</option>";
  }
  wifiListHTML += "</select>";
}

// Режим точки доступа
void startAPMode() {
  Serial.println("Starting AP mode...");
  apMode = true;
  WiFi.mode(WIFI_AP);
  WiFi.softAP("ESP8266_Config");

  scanNetworks();

  Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP());

  apServer.on("/", HTTP_GET, []() {
    String html = "<html><body><h1>WiFi Setup</h1>"
                  "<form action='/save' method='POST'>"
                  "SSID: " + wifiListHTML + "<br>"
                  "Password: <input type='text' name='pass' value='" + passStored + "'><br>"
                  "<input type='submit' value='Save'>"
                  "</form></body></html>";
    apServer.send(200, "text/html", html);
  });

  apServer.on("/save", HTTP_POST, []() {
    String ssid = apServer.arg("ssid");
    String pass = apServer.arg("pass");

    saveCredentials(ssid, pass);

    apServer.send(200, "text/html", "<html><body><h1>Saved! Rebooting...</h1></body></html>");
    delay(2000);
    ESP.restart();
  });

  apServer.begin();
}