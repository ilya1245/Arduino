#include <WiFiEspAT.h>
#include <ArduinoOTA.h>
#define AT_BAUD_RATE 115200

WiFiServer server(80);


void setup() {

  Serial.begin(115200);
  while (!Serial);

  Serial1.begin(AT_BAUD_RATE);
  WiFi.init(Serial1);

  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  // waiting for connection to Wifi network set with the SetupWiFiConnection sketch
  Serial.println("Waiting for connection to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print('.');
  }
  Serial.println();
Serial.println("Connected to WiFi network.");
  
  server.begin();

// start the WiFi OTA library with internal (flash) based storage
  ArduinoOTA.begin(WiFi.localIP(), "Arduino", "password", InternalStorage);

  // you're connected now, so print out the status:
  printWifiStatus();


  IPAddress ip = WiFi.localIP();
  Serial.println();
    Serial.print("To access the server, enter \"http://");
  Serial.print(ip);
  Serial.println("/\" in web browser.");
}



void loop() {

  WiFiClient client = server.available();
  if (client) {
    IPAddress ip = client.remoteIP();
    Serial.print("new client ");
    Serial.println(ip);

    while (client.connected()) {
      if (client.available()) {
        String line = client.readStringUntil('\n');
        line.trim();
        Serial.println(line);

        // if you've gotten to the end of the HTTP header (the line is blank),
        // the http request has ended, so you can send a reply
        if (line.length() == 0) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 5");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          // output the value of analog input pins
          
            client.println("Test4");
            
          
          client.println("</html>");
          client.flush();
          break;
        }
      }
    }

    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
// check for WiFi OTA updates
  ArduinoOTA.poll();

  // add your normal loop code below ...
}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
