#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>

#define EEPROM_SIZE 512
#define EEPROM_FLAG_ADDR 0
#define EEPROM_SSID_LEN_ADDR 1
#define EEPROM_PASS_LEN_ADDR 2
#define EEPROM_DATA_ADDR 3

#define LED_PIN 2

ESP8266WebServer server(80);

String ssidStored;
String passStored;
String wifiListHTML;
bool apMode = false;

// Чтение сохранённых данных
void loadCredentials() {
  if (EEPROM.read(EEPROM_FLAG_ADDR) == 'C') {
    byte ssidLen = EEPROM.read(EEPROM_SSID_LEN_ADDR);
    byte passLen = EEPROM.read(EEPROM_PASS_LEN_ADDR);

    char ssidBuf[ssidLen + 1];
    char passBuf[passLen + 1];

    for (byte i = 0; i < ssidLen; i++) {
      ssidBuf[i] = EEPROM.read(EEPROM_DATA_ADDR + i);
    }
    ssidBuf[ssidLen] = '\0';

    for (byte i = 0; i < passLen; i++) {
      passBuf[i] = EEPROM.read(EEPROM_DATA_ADDR + ssidLen + i);
    }
    passBuf[passLen] = '\0';

    ssidStored = String(ssidBuf);
    passStored = String(passBuf);

    Serial.println("Loaded from EEPROM:");
    Serial.println("SSID: " + ssidStored);
    Serial.println("PASS: " + passStored);
  } else {
    ssidStored = "";
    passStored = "";
    Serial.println("No credentials in EEPROM.");
  }
}

// Сохранение данных
void saveCredentials(const String &ssid, const String &pass) {
  EEPROM.write(EEPROM_FLAG_ADDR, 'C');
  EEPROM.write(EEPROM_SSID_LEN_ADDR, ssid.length());
  EEPROM.write(EEPROM_PASS_LEN_ADDR, pass.length());

  for (byte i = 0; i < ssid.length(); i++) {
    EEPROM.write(EEPROM_DATA_ADDR + i, ssid[i]);
  }

  for (byte i = 0; i < pass.length(); i++) {
    EEPROM.write(EEPROM_DATA_ADDR + ssid.length() + i, pass[i]);
  }

  EEPROM.commit();
}

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

  Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP());

  scanNetworks();

  server.on("/", HTTP_GET, []() {
    String html = "<html><body><h1>WiFi Setup</h1>"
                  "<form action='/save' method='POST'>"
                  "SSID: " + wifiListHTML + "<br>"
                  "Password: <input type='text' name='pass' value='" + passStored + "'><br>"
                  "<input type='submit' value='Save'>"
                  "</form></body></html>";
    server.send(200, "text/html", html);
  });

  server.on("/save", HTTP_POST, []() {
    String ssid = server.arg("ssid");
    String pass = server.arg("pass");

    saveCredentials(ssid, pass);

    server.send(200, "text/html", "<html><body><h1>Saved! Rebooting...</h1></body></html>");
    delay(2000);
    ESP.restart();
  });

  server.begin();
}

// Попытка подключения к Wi-Fi
void tryConnect() {
  Serial.printf("Connecting to %s...\n", ssidStored.c_str());
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssidStored.c_str(), passStored.c_str());

  unsigned long startAttemptTime = millis();

  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 10000) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  if (WiFi.status() == WL_CONNECTED) {
    Serial.printf("\nConnected to %s!\n", ssidStored.c_str());
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    apMode = false;
  } else {
    Serial.println("Failed to connect. Switching to AP mode.");
    startAPMode();
  }
}

void setup() {
  Serial.begin(115200);
  EEPROM.begin(EEPROM_SIZE);
  pinMode(LED_PIN, OUTPUT);

  loadCredentials();

  if (ssidStored.length() > 0) {
    tryConnect();
    if (WiFi.status() != WL_CONNECTED) {
      startAPMode();
    }
  } else {
    startAPMode();
  }
}

void loop() {
  if (apMode) {
    // Мы в режиме точки доступа — обрабатываем запросы
    server.handleClient();
  } else {
    // Мы в режиме клиента — выполняем основную работу
    static unsigned long lastBlink = 0;
    static bool ledState = false;

    if (millis() - lastBlink > 500) {
      ledState = !ledState;
      digitalWrite(LED_PIN, ledState ? LOW : HIGH); // LOW — вкл, HIGH — выкл на ESP
      lastBlink = millis();
    }
  }
}
