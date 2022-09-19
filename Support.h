struct timeUnit {
  byte hour;
  byte min;
  byte sec;
};
struct timeUnit timeReal;
struct timeUnit timeFetc;
int timeLastFetch;



// Wifi things
#include <ESP8266WiFi.h>
const char *ssid = "WifiNetwork";
const char *password = "Password";


// NTP things
#include <NTPClient.h>
#include <WiFiUdp.h>

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");


// NeoPixel things
#include <Adafruit_NeoPixel.h>
#define LED_PIN 12
#define LED_COUNT 60
byte BRIGHTNESS = 50;
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRBW + NEO_KHZ800);
#define PIXEL_ROTATION_OFFSET 1


// IO things
#define BTN_PIN 0
#define PHR_PIN A0
#define PHR_LOWLIGHT_THRESHOLD 40

enum clockMode {
  DARK,
  NORMAL,
  CONNECTING
};
byte clockMode = 0;