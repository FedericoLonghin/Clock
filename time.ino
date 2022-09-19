void fetchTime() {
  timeClient.begin();
  timeClient.setTimeOffset(7200);
  timeClient.update();
  timeFetch.hour = timeClient.getHours();
  timeFetch.min = timeClient.getMinutes();
  timeFetch.sec = timeClient.getSeconds();
  timeLastFetch = millis();
}

void getRealTime() {
  unsigned long int sec = (millis() - timeLastFetch) / 1000;
  timeReal.sec = (timeFetch.sec + sec);
  timeReal.min = (timeFetch.min + timeReal.sec / 60);
  timeReal.hour = (timeFetch.hour + sec / 3600);
  timeReal.sec = timeReal.sec % 60;
  timeReal.min = timeReal.min % 60;
  timeReal.hour = timeReal.hour % 24;

  Serial.printf("%d:%d:%d -- %d", timeReal.hour, timeReal.min, timeReal.sec,sec);
  Serial.printf(" --%d:%d:%d\n", timeFetch.hour, timeFetch.min, timeFetch.sec,sec);
}