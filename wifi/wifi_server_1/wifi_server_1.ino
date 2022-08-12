/*
    This sketch sends a string to a TCP server, and prints a one-line response.
    You must run a TCP server in your local network.
    For example, on Linux you can use this command: nc -v -l 3000
*/

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

const char* ssid     = "CoolDap";
const char* password = "guest-24";

const char* host = "134.249.124.221"; // 192.168.0.50
const uint16_t port = 11022;

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

ESP8266WiFiMulti WiFiMulti;

void setup() {
  Serial.begin(9600);

  // We start by connecting to a WiFi network
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(ssid, password);

  Serial.println();
  Serial.println();
  Serial.print("Wait for WiFi... ");

  while (WiFiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  server.begin();

  delay(500);
}

boolean isNewClient;


void loop() {
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  Serial.print("connecting to ");
  Serial.print(host);
  Serial.print(':');
  Serial.println(port);

  // Use WiFiClient class to create TCP connections
  WiFiClient client_1;

  if (!client_1.connect(host, port)) {
    Serial.println("connection failed");
    Serial.println("wait 5 sec...");
    delay(5000);
    return;
  }

  // This will send the request to the server
  client_1.println("hello from ESP8266");

  //read back one line from server
  Serial.println("receiving from remote server");
  String line = client_1.readStringUntil('\r');
  Serial.println(line);

  Serial.println("closing connection");
  client_1.stop();

  Serial.print("isNewClient=");
  Serial.println(isNewClient);

  WiFiClient client = server.available();   // Listen for incoming clients
  if (client) {                             // If a new client connects,
    isNewClient = true;
    Serial.println("New Client.");          // print a message out in the serial port
  
  
  
  
  
  
  
  
  }

  client.stop();
  Serial.println("Client disconnected.");
  Serial.println("");




}
