#include "Support.h"

void setup() {
  Serial.begin(9600);
  EEPROM.begin(512);
  strip.begin();
  strip.setBrightness(brightness_pv);
  drawPointer(0, 1, strip.Color(255, 255, 0));
  strip.show();

  if (getWifiMode() == CREATE_NETWORK) {
    clockMode = NO_WIFI;
  } else {
    clockMode = INITIALIZING;
  }

  pinMode(BTN_PIN, INPUT_PULLUP);
}

void loop() {
  //BTN
  if (clockRinging) ring(ringCause, alarmNumberRinging);
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
  if (!clockRinging && stripMode != MAN_OFF && stripMode != MAN_ON) {
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

  if (!clockRinging) checkForAlarms();
  getRealTime();


  //CLOCK_MODE MANAGER
  switch (clockMode) {

    case NORMAL:

      break;
    case INITIALIZING:
      getEEPROMData();
      connectToWifi();
      fetchTime();
      clockMode = NORMAL;
      break;
    case TIMER:
      if (!clockRinging) getRemainingTime();
      break;

    case NO_WIFI:
      if (!APConfigured) {
        createWifiNetwork();
      }
      break;
  }

  if (stripMode == MAN_ON || stripMode == AUTO_ON) {
    if (clockMode == NORMAL) drawTime();
    else if (clockMode == TIMER) drawTimer();
    else if (clockMode == NO_WIFI) {
      if (!APConfigured) {
        drawPointer(0, 1, strip.Color(255, 0, 0));
        strip.show();
        APConfigured = 1;
      }
    }
  } else {
    if (!inFade) {
      strip.clear();
      strip.show();
    }
  }


/*
  switch (clockRinging ? RINGING : (clockMode * (stripMode == MAN_ON || stripMode == AUTO_ON))) {
    case DARK:
      if (!inFade) {
        strip.clear();
        strip.show();
      }
      break;
    case NORMAL:
      drawTime();
      break;

    case TIMER:
      drawTimer();
      break;
    case RINGING:
      strip.show();
      break;
    case NO_WIFI:
      if (!APConfigured) {
        drawPointer(0, 1, strip.Color(255, 0, 0));
        strip.show();
        APConfigured = 1;
      }
      break;
  }
*/

  server.handleClient();
  /*
  for (byte i = 0; i < existingAlarms; i++) {
    Serial.printf("Alarm n. %d --- dayCode:%d%d%d%d%d%d%d,%d, AlreadyRinged:%d, %d:%d\n", i, alarms[i].weekDay[0], alarms[i].weekDay[1], alarms[i].weekDay[2], alarms[i].weekDay[3], alarms[i].weekDay[4], alarms[i].weekDay[5], alarms[i].weekDay[6], alarms[i].oneTime,alarms[i].alreadyRinged, alarms[i].hour, alarms[i].min);
  }*/
}