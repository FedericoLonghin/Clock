#include "Support.h"

void setup() {
  Serial.begin(9600);
  pinMode(BTN_PIN, INPUT_PULLUP);
  strip.begin();
  strip.show();
  strip.setBrightness(BRIGHTNESS);
  clockMode = CONNECTING;
}

void loop() {
  switch (clockMode) {
    case NORMAL:
      getRealTime();
      drawTime();
      break;
    case CONNECTING:
      connectToWifi();
      fetchTime();
      clockMode = NORMAL;
      break;
  }
}