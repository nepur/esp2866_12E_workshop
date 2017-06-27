/*
 *  This example demonstrates how to read an
 *  HC-SR04 Ultrasonic distance sensor and then use
 *  WiFiClientSecure class to access HTTPS API to
 *  push to Firebase
 *
 *  Created by Rupen Patel, 2016.
 *  This example is in public domain.
 */

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

const short int BUILTIN_LED1 = 2; //GPIO2
const short int BUILTIN_LED2 = 16;//GPIO16
const short int TRIG = 5; //D1
const short int ECHO = 4; //D2

char WIFI_SSID[] = "YOUR_SSID_HERE";
char WIFI_PASS[] = "YOUR_WIFI_PASS_HERE";

// NOTE: Leave off the https part.  Just the Host NOT the URL
char BAAS_HOST[] = "YOUR_FIREBASE_HOST_HERE";
int BAAS_PORT = 443;
// Use web browser to view SSL cert and get SHA1 from it
char BAAS_FINGERPRINT[] = "7A 54 06 9B DC 7A 25 B3 86 8D 66 53 48 2C 0B 96 42 C7 B3 0A";
char GET_URL[] = "/wkshp_usonic.json";
char POST_URL[] = "/wkshp_usonic.json";

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

/*
 * Open an HTTPS connection and verify the SHA1 fingerprint of hte cert that was received
 */
WiFiClientSecure openHTTPS(char host[], int httpsPort, char fingerprint[]) {
  // Use WiFiClientSecure class to create TLS connection
  WiFiClientSecure client;
  Serial.print("connecting to ");
  Serial.println(host);
  if (!client.connect(host, httpsPort)) {
    Serial.println("connection failed");
    return client;
  }

  if (client.verify(fingerprint, host)) {
    Serial.println("certificate matches");
  } else {
    Serial.println("certificate doesn't match");
  }

  return client;
}

/*
 * Do an HTTP request and return the response
 */
String httpsRequest(WiFiClientSecure client, String request) {
  Serial.println("Sending HTTPS Request: ");
  Serial.println(request);

  // Send the actual request
  client.print(request);
  
  Serial.println("HTTPS Request sent");

  
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("HTTPS Response headers received");
      break;
     }
  }
  
  String line = client.readStringUntil('\n');
  Serial.println("HTTP response body was:");
  Serial.println("==========");
  Serial.println(line);
  Serial.println("==========");
  return line;
}

/*
 * Do an Get request over HTTPS
 */
String httpsGet(WiFiClientSecure client, char host[], char url[]) {

  String getRequest = "GET " + String(url) + " HTTP/1.1" + "\r\n";
  getRequest += "Host: " + String(host) + "\r\n";
  getRequest += "User-Agent: ESP2866_12E\r\n";
  getRequest += "Accept: */*\r\n";
  //Don't forget to do this under the following circumstances
  //getRequest +=  "Connection: close\r\n";
  getRequest += "\r\n";

  return httpsRequest(client, getRequest);
}

String httpsPost(WiFiClientSecure client, char host[], char url[], String data) {
       
  String post = "POST " + String(url) + " HTTP/1.1" + "\r\n";
  post += "Host: " + String(host) + "\r\n";
  post += "User-Agent: ESP2866_12E\r\n";
  post += "Accept: */*\r\n";
  post += "Content-Length: " + String(data.length()) + "\r\n";
  post += "Content-Type: application/x-www-form-urlencoded\r\n";
  //Don't forget to do this under the following circumstances
  //post +=  "Connection: close\r\n";
  post += "\r\n";
  post += data;
  post += "\r\n";

  return httpsRequest(client, post);
}

void setup() {
  // Setup the onboard GPIO pins for output to drive LEDs
  pinMode(BUILTIN_LED1, OUTPUT);
  pinMode(BUILTIN_LED2, OUTPUT);
  
  //Setup D1 and D2 to drive the HC-SR04
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  //Setup debug port with right baud rate
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  
  connectWiFi(WIFI_SSID, WIFI_PASS);
    
  Serial.print("Setup completed ");
}

void loop() {
  // put your main code here, to run repeatedly:
  long timedelay;
  long distance;
  
  digitalWrite(BUILTIN_LED1, HIGH);
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  
  digitalWrite(TRIG, LOW);
  digitalWrite(BUILTIN_LED1, LOW);

  timedelay = pulseIn(ECHO, HIGH);
  //Calculate the distance (in inches) based on the speed of sound.
  distance = timedelay*0.0133/2;

  Serial.println("-----------------------------------------");
  Serial.println("Read echo distance: " + String(distance));
  Serial.println("-----------------------------------------");


  WiFiClientSecure myClient = openHTTPS(BAAS_HOST, BAAS_PORT, BAAS_FINGERPRINT);
  //String value = httpsGet(myClient, BAAS_HOST, GET_URL);
  //Serial.println(value);

  String jsonBody = "{\"distance\":\""  + String(distance) + "\"}";
  httpsPost(myClient, BAAS_HOST, POST_URL, jsonBody);
  
  myClient.stop();

  delay(2000);
}
