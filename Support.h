struct timeUnit {
  int hour;
  int min;
  int sec;
};
struct timeUnit timeReal;
struct timeUnit timeFetch;
int timeLastFetch;



// Wifi things
#include <ESP8266WiFi.h>

#include <WiFiClient.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server(80);

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
byte brightness_sp = 50, brightness_pv = 0, brightness_default = 50, brightness_flashHigh = 150, brightness_flashLow = 20;
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRBW + NEO_KHZ800);
#define PIXEL_ROTATION_OFFSET 1


// IO things
#define BTN_PIN 0
#define PHR_PIN A0
#define PHR_LOWLIGHT_THRESHOLD 40

enum clockMode {
  DARK,
  NORMAL,
  CONNECTING,
  TIMER
};
enum stripMode {
  MAN_OFF,
  MAN_ON,
  AUTO_OFF,
  AUTO_ON,
  FADING
};
byte clockMode = CONNECTING, stripMode = AUTO_ON;
byte fadeStepDuration = 10;
bool inFade;
int lastTimeBTNPressed, lastFadeStep;

bool onTimer, timerRing;
long int timerCentSecLength, timerCentSecEnd, timerCentSecLeft;
int timerPixelCount;
float timerPixelCountFloat;