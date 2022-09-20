void fetchTime() {

  timeClient.begin();
  timeClient.setTimeOffset(7200);
  timeClient.update();
  timeFetch.weekDay = timeClient.getDay();
  timeFetch.hour = timeClient.getHours();
  timeFetch.min = timeClient.getMinutes();
  timeFetch.sec = timeClient.getSeconds();
  timeLastFetch = millis();
  timeClient.end();
}

void getRealTime() {
  unsigned long int sec = (millis() - timeLastFetch) / 1000;
  timeReal.sec = (timeFetch.sec + sec);
  timeReal.min = (timeFetch.min + timeReal.sec / 60);
  timeReal.hour = (timeFetch.hour + timeReal.min / 60);
  timeReal.weekDay = (timeFetch.weekDay + timeReal.hour / 24);
  timeReal.sec = timeReal.sec % 60;
  timeReal.min = timeReal.min % 60;
  timeReal.hour = timeReal.hour % 24;
  timeReal.weekDay = timeReal.weekDay % 7;

  //Serial.printf("%d, %d:%d:%d -- %d", timeReal.weekDay,timeReal.hour, timeReal.min, timeReal.sec, sec);
  //Serial.printf(" -- %d, %d:%d:%d\n", timeFetch.weekDay,timeFetch.hour, timeFetch.min, timeFetch.sec, sec);
}

void getRemainingTime() {
  timerCentSecLeft = timerCentSecEnd - (millis() / 10);
  if (timerCentSecLeft <= 0) {
    brightness_sp = brightness_flashHigh;
    ringCause = TIMER_RING;
    clockRinging = 1;
  }
}

void checkForTodayAlarm() {
  alarmsForToday = 0;
  for (byte i = 0; i < existingAlarms; i++) {
    if (alarms[i].weekDay[timeReal.weekDay]) {
      alarmsForToday = 1;
      Serial.println("alarm for today");
    }
  }
}

void checkForAlarms() {
  if (alarmsForToday) {
    for (byte i = 0; i < existingAlarms; i++) {
      if (!alarms[i].alreadyRinged && alarms[i].weekDay[timeReal.weekDay] && alarms[i].hour == timeReal.hour && alarms[i].min == timeReal.min) {
        brightness_sp = brightness_flashHigh;
        ringCause = ALARM_RING;
        alarmNumberRinging = i;
        clockRinging = 1;
      }
    }
  }
}