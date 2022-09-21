void drawTime() {
  strip.clear();
  drawPointer(timeReal.hour * 5, 5, strip.Color(255, 0, 0));
  drawPointer(timeReal.min, 3, strip.Color(0, 255, 0));
  drawPointer(timeReal.sec, 1, strip.Color(0, 0, 255));
  strip.show();
}


void drawPointer(byte num, byte size, uint32_t color) {
  for (byte i = 1; i <= size; i++) {
    int pix = ((59 - (num - ((size + 1) / 2) + i)) + PIXEL_ROTATION_OFFSET) % 60;
    pix = pix < 0 ? (pix + 60) : pix;

    //Serial.printf("%d ", pix);
    strip.setPixelColor(pix, color);
  }
  //Serial.println("");
}

void drawTimer() {
  if (!clockRinging) {
    strip.clear();

    timerPixelCountFloat = (timerCentSecLength - timerCentSecLeft);
    timerPixelCount = (timerPixelCountFloat / timerCentSecLength) * 60;
    for (byte i = 0; i < timerPixelCount; i++) {
      strip.setPixelColor(59 - i, strip.Color(255, 255, 0));
    }
    strip.show();
  }
}

void ring(bool ringType, byte alarmNumber) {
  clockMode = RINGING;
  clockRinging = 1;
  strip.fill(strip.Color(255, 0, 0));
  if (brightness_pv == brightness_flashLow) brightness_sp = brightness_flashHigh;
  if (brightness_pv == brightness_flashHigh) brightness_sp = brightness_flashLow;
  //Serial.printf("sp:%d,pv:%d\n", brightness_sp, brightness_pv);
  byte i = 0;
  while (!digitalRead(BTN_PIN)) {
    strip.setBrightness(brightness_default);
    if (i < 60) {
      for (byte j = 0; j <= i; j++) {
        strip.setPixelColor(59 - j, strip.Color(255, 255, 0));
      }
      strip.show();
      delay(fadeStepDuration);
      i++;
    } else {
      if (clockRinging) {  //entering here only one time
        clockRinging = 0;
        clockMode = NORMAL;
        if (TIMER_RING) {

          onTimer = 0;
          timerRing = 0;
        } else if (ALARM_RING) {
          if (alarms[alarmNumber].oneTime) {  //delete the alarm
            deleteAlarm(alarmNumber);
          } else {
            alarms[alarmNumber].alreadyRinged = 1;
          }
        }
      }
      lastTimeBTNPressed = millis();
    }
  }
}