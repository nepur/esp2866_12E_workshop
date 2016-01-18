/*
 *  This example demonstrates how to use
 *  WiFiClientSecure class to access HTTPS API.
 *  It calls a Firebase url to retrieve a known
 *  key
 *
 *  Created by Rupen Patel, 2016.
 *  This example is in public domain.
 */

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

const short int BUILTIN_LED1 = 2; //GPIO2
const short int BUILTIN_LED2 = 16;//GPIO16

char WIFI_SSID[] = "YOUR_SSID";
char WIFI_PASS[] = "YOUR_WIFI_PASSWORD";

/* 
 *  Connect to local WiFi router and obtain an IP address
 */
void connectWiFi(char ssid[], char password[]) {
  WiFi.mode(WIFI_STA);
  delay(5000);
  Serial.print("connecting to ");
  Serial.println(ssid);

  if (WiFi.SSID() != ssid) {
    // No encryption
    // WiFi.begin(ssid);
    
    // WPA/WPA2
    WiFi.begin(ssid, password);
    
    // WEP
    // WiFi.begin(ssid,keyIndex, key);
    
  }
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  // configure time and wait for it..
  configTime(3 * 3600, 0, "pool.ntp.org");
  delay(2000);
}

void setup() {
  // Setup the onboard GPIO pins for output to drive LEDs
  pinMode(BUILTIN_LED1, OUTPUT);
  pinMode(BUILTIN_LED2, OUTPUT);

  //Setup debug port with right baud rate
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  
  connectWiFi(WIFI_SSID, WIFI_PASS);

  Serial.print("Setup completed ");
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(BUILTIN_LED1, HIGH);
  delay(2000);  
  digitalWrite(BUILTIN_LED1, LOW);
  delay(2000);
}
