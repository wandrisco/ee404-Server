#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h> 
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>

ESP8266WiFiMulti wifiMulti;           // Create an instance of the ESP8266WiFiMulti class, called 'wifiMulti'

ESP8266WebServer server(80);         // Create a webserver object that listens for HTTP request on port 80

const char *ssid = "CpE esp8266-01 Access Point";        // The name of the Wi-Fi network that will be created
const char *password = "gojaguars";               // The password required to connect to it, leave blank for an open network (must be 8 chars)

String header;

const int led0 = 0, led2 = 2;
String output0State = "off";
String output2State = "off";

void handleRoot();                   // function prototypes for HTTP handlers
void handleLED();
void handleNotFound();
void checkClients();
void getVoltage(), getCurrent();

void setup(void){
  Serial.begin(115200);             // Start the Serial communication to send messages to the computer
  delay(10);
  Serial.println("ESP-01 Module Running...\n");
  Serial.flush();

  pinMode(led0, OUTPUT);
  pinMode(led2, OUTPUT);

  digitalWrite(led0, LOW);
  digitalWrite(led2, LOW);

  WiFi.softAP(ssid, password);             // Start the access point
  Serial.print("Access Point: \"");
  Serial.print(ssid);
  Serial.println("\" started");
  Serial.print("AP IP:\t");
  Serial.println(WiFi.softAPIP());
  Serial.print("\n");
  Serial.flush();

  wifiMulti.addAP("OPEN", "");
  wifiMulti.addAP("Wandrisco's iPhone", "d6cgg1t9gk5oo");
  wifiMulti.addAP("HAL", "1hC$sOLK");

  Serial.print("Connecting...");
  int i = 0;https://github.com/esp8266/Arduino
  while (wifiMulti.run() != WL_CONNECTED) { // Wait for the Wi-Fi to connect: scan for Wi-Fi networks, and connect to the strongest of the networks above
    delay(250);
    Serial.print('.');
  }
  Serial.print("\n");
  
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID());              // Tell us what network we're connected to
  Serial.flush();
  Serial.print("IP Address:\t");
  Serial.println(WiFi.localIP());           // Send the IP address of the ESP8266 to the computer
  Serial.print('\n');
  Serial.flush();

  if (MDNS.begin("esp8266")) {              // Start the mDNS responder for esp8266.local
    Serial.println("mDNS responder started");
    Serial.flush();
  } else {
    Serial.println("Error setting up MDNS responder!");
    Serial.flush();
  }

  server.on("/", HTTP_GET, handleRoot);     // Call the 'handleRoot' function when a client requests URI "/"
  server.on("/LED", HTTP_POST, handleLED);  // Call the 'handleLED' function when a POST request is made to URI "/LED"
  server.onNotFound(handleNotFound);        // When a client requests an unknown URI (i.e. something other than "/"), call function "handleNotFound"

  server.begin();                           // Actually start the server
  Serial.println("HTTP server started");
  Serial.print('\n');


}

void loop(void){  
  //server.handleClient();                    // Listen for HTTP requests from clients  
  
  checkClients();                           //Checks for clients connecting to AP
}

void checkClients() {  
    switch (WiFi.softAPgetStationNum()) {
    case 0: 
      Serial.print(WiFi.softAPgetStationNum());
      Serial.print(" clients connected to "); 
      Serial.print(ssid);
      Serial.print('\n');
      break;
    case 1:
      Serial.print(WiFi.softAPgetStationNum());
      Serial.print(" client connected to "); 
      Serial.print(ssid);
      Serial.print('\n');
      break;
    case 2: 
      Serial.print(WiFi.softAPgetStationNum());
      Serial.print(" clients connected to "); 
      Serial.print(ssid);
      Serial.print('\n');
      break;
    case 3:
      Serial.print(WiFi.softAPgetStationNum());
      Serial.print(" clients connected to "); 
      Serial.print(ssid);
      Serial.print('\n');
      break;
    case 4:
      Serial.print(WiFi.softAPgetStationNum());
      Serial.print(" clients connected to "); 
      Serial.print(ssid);
      Serial.print('\n');
      break;
    case 5:
      Serial.print(WiFi.softAPgetStationNum());
      Serial.print(" clients connected to "); 
      Serial.print(ssid);
      Serial.print('\n');
      break;
  }
delay (5000);
}

void handleRoot() {                         // When URI / is requested, send a web page with a button to toggle the LED
  server.send(200, "text/html", "<form action=\"/LED\" method=\"POST\"><input type=\"submit\" value=\"Toggle LED 2\"></form>");
}

void handleLED() {                          // If a POST request is made to URI /LED
  digitalWrite(led0,!digitalRead(led0));      // Change the state of the LED
  digitalWrite(led2,!digitalRead(led2));      // Change the state of the LED

  server.sendHeader("Location","/");        // Add a header to respond with a new location for the browser to go to the home page again
  server.send(303);                         // Send it back to the browser with an HTTP status 303 (See Other) to redirect
}

void handleNotFound(){
  server.send(404, "text/plain", "404: Not found"); // Send HTTP status 404 (Not Found) when there's no handler for the URI in the request
}

void getVoltage(){
  Serial.println("The Voltage reads as: ");
}

void getcurrent(){
  Serial.println("The Current reads as: ");

}


/*
 * EEPROM.begin(size) before you read or write  b/w 4 and 4096 bytes
 * EEPROM.commit() anytime you want to commit/save changes
 * 
 * 
 * 
 * 
 */
 
