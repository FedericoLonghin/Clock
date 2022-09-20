#include "Support.h"

void setup() {
  Serial.begin(9600);
  pinMode(BTN_PIN, INPUT_PULLUP);
  strip.begin();
  strip.show();
  strip.setBrightness(brightness_pv);
  clockMode = CONNECTING;

  server.on("/strip", handleStrip);
  server.on("/timer", handleTimer);

  server.begin();
}

void loop() {

  //BTN
  if (!digitalRead(BTN_PIN) && millis() - lastTimeBTNPressed > 200) {
    if (stripMode == AUTO_ON || stripMode == MAN_ON) {
      stripMode = MAN_OFF;
      brightness_sp = 0;
    } else if (stripMode == AUTO_OFF) {

      stripMode = MAN_ON;
      brightness_sp = brightness_default;

    } else {
      stripMode = MAN_ON;
      brightness_sp = brightness_default;
    }
    lastTimeBTNPressed = millis();
  }

  //PHOTORESISTOR
  if (clockMode != TIMER && stripMode != MAN_OFF && stripMode != MAN_ON) {
    if (darkEnviroment()) {
      stripMode = AUTO_OFF;
      brightness_sp = 0;
    } else {
      stripMode = AUTO_ON;
      brightness_sp = brightness_default;
    }
  }
  if (stripMode == MAN_ON && !darkEnviroment()) stripMode = AUTO_ON;

  //BRIGHTNESS ADJUSTMENT
  if (brightness_sp != brightness_pv) {

    if (millis() - lastFadeStep > fadeStepDuration) {
      lastFadeStep = millis();
      inFade = 1;
      if (brightness_pv < brightness_sp) brightness_pv++;
      else brightness_pv--;
      strip.setBrightness(brightness_pv);
      strip.show();
    }
  } else inFade = 0;

  switch (clockMode * (stripMode == MAN_ON || stripMode == AUTO_ON)) {
    case DARK:
      if (!inFade) {
        strip.clear();
        strip.show();
      }
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
    case TIMER:
      if (!timerRing) getRemainingTime();
      drawTimer();
      break;
  }
  server.handleClient();
}