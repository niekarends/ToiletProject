/*
  Web client

  This sketch connects to a website (http://www.google.com)
  using a WiFi shield.

  This example is written for a network using WPA encryption. For
  WEP or WPA, change the WiFi.begin() call accordingly.

  This example is written for a network using WPA encryption. For
  WEP or WPA, change the WiFi.begin() call accordingly.

  Circuit:
   WiFi shield attached

  created 13 July 2010
  by dlf (Metodo2 srl)
  modified 31 May 2012
  by Tom Igoe
*/


#include <SPI.h>
#include <WiFi101.h>
#include "arduino_secrets.h"
///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;            // your network key Index number (needed only for WEP)

const int button1Pin = 7;     // the number of the pushbutton pin
const int button2Pin = 8;

int currentState1 = 0;         // variable for reading the pushbutton status
int previousState1 = 0;

int currentState2 = 0;         // variable for reading the pushbutton status
int previousState2 = 0;


int status = WL_IDLE_STATUS;
// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
IPAddress server(185, 170, 7, 129); // numeric IP for Google (no DNS)
//char server[] = "www.google.com";    // name address for Google (using DNS)

// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
WiFiClient client;

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  // initialize the LED pin as an output:
  // initialize the pushbutton pin as an input:
  pinMode(button1Pin, INPUT_PULLUP);
  pinMode(button2Pin, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);

//  while (!Serial) {
//    ; // wait for serial port to connect. Needed for native USB port only
//  }

  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
    while (true);
  }
}

void connectToWiFi() {
  digitalWrite(LED_BUILTIN, HIGH);
  WiFi.maxLowPowerMode();
  // attempt to connect to WiFi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(5000);
  }
  digitalWrite(LED_BUILTIN, LOW);
  Serial.println("Connected to wifi");
  printWiFiStatus();
}

void doPost(String id, String value) {
  Serial.println("\nStarting connection to server...");
  if (client.connect(server, 1026)) {
    Serial.println("connected to server");
    // Make a HTTP request:
    String body = "{\"status\": {\"value\":\"" + value + "\", \"type\":\"string\"}}";
    Serial.println(body + "\nContent-Length: " + body.length());

    client.println("PATCH /v2/entities/" + id + "/attrs HTTP/1.1");
    client.println("Host: 185.170.7.129:1026");
    client.println("Content-Type: application/json");
    client.println("Connection: close");
    client.println("Content-Length: " + String(body.length()));
    client.println();
    client.println(body);
    Serial.println("Sent request, now starting reading");
  }
  //Read the response

  while (client.connected()) {
    int i = 0;
    while (client.available()) {
      char c = client.read();
      Serial.write(c);
    }
    if (!client.connected()) {
      Serial.println();
      Serial.println("End of transmission");
      client.stop();
    }
  }

}

String doGet() {
  Serial.println("\nStarting connection to server...");
  if (client.connect(server, 1026)) {
    Serial.println("connected to server");
    // Make a HTTP request:
    client.println("GET /v2 HTTP/1.1");
    client.println("Host: 185.170.7.129:1026");
    client.println("Connection: close");
    client.println();
    Serial.println("Sent request, now starting reading");
  }
  char s[] = "";
  //Read the response

  while (client.connected()) {
    int i = 0;
    while (client.available()) {
      char c = client.read();
      Serial.write(c);
    }
  }
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting from server.");
    client.stop();
  }
  //  Serial.println("Response was [" + s + "]");
}

void loop() {
  //Check if still connected to WIFI
  status = WiFi.status();
  if (status != WL_CONNECTED) {
    Serial.println("Lost Wifi connection");
    connectToWiFi();
  }

  //Check button1 state
  currentState1 = digitalRead(button1Pin);
  if (currentState1 != previousState1) {
    previousState1 = currentState1;
    if (currentState1 == 1) {
      Serial.println("Button 1 High");
//      WiFi.end();
      doPost("sensor1", "occupied");
    } else {
      Serial.println("Button 1 Low");
      doPost("sensor1", "free");
    }
  }

  currentState2 = digitalRead(button2Pin);
  if (currentState2 != previousState2) {
    previousState2 = currentState2;
    if (currentState2 == 0) {
      Serial.println("Button 2 High");
      doPost("sensor2", "occupied");
    } else {
      Serial.println("Button 2 Low");
      doPost("sensor2", "free");
    }
  }

  //Only check once a second
  delay(100);
}


void printWiFiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI): ");
  Serial.print(rssi);
  Serial.println(" dBm");
}
