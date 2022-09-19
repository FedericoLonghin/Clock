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
  if (!digitalRead(BTN_PIN)) {
    if (stripMode == AUTO_ON || stripMode == MAN_ON) stripMode = MAN_OFF;
    else if (stripMode == AUTO_OFF) stripMode = MAN_ON;
    else stripMode = MAN_ON;
    while (!digitalRead(BTN_PIN))
      ;
  }
  if (stripMode != MAN_OFF && stripMode != MAN_ON) stripMode = darkEnviroment() ? AUTO_OFF : AUTO_ON;
  if (stripMode == MAN_ON && !darkEnviroment()) stripMode = AUTO_ON;
  switch (clockMode * (stripMode == MAN_ON || stripMode == AUTO_ON)) {
    case DARK:
      strip.clear();
      strip.show();
      break;
    case NORMAL:
      getRealTime();
      drawTime();
      break;
    case CONNECTING:
      drawPointer(0, 1, strip.Color(255, 255, 0));
      strip.show();
      connectToWifi();
      fetchTime();
      clockMode = NORMAL;
      break;
  }
}