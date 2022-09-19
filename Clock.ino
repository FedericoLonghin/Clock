#include "Support.h"

// Wifi things
#include <ESP8266WiFi.h>
const char *ssid     = "WifiNetwork";
const char *password = "Password";


// NTP things
#include <NTPClient.h>
#include <WiFiUdp.h>

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");



void setup() {
  Serial.begin(9600);
  
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  fetchTime();
}

void loop() {
  getRealTime();
  delay(500);
}