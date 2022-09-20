void connectToWifi() {
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}


void handleStrip() {
  if (stripMode == AUTO_ON || stripMode == MAN_ON) {
    stripMode = MAN_OFF;
    brightness_sp = 0;
  } else if (stripMode == AUTO_OFF || stripMode == MAN_OFF) {
    stripMode = MAN_ON;
    brightness_sp = brightness_default;
  }
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/html", "<!DOCTYPE html><html><head> <meta name='viewport' content='width=device-width, initial-scale=1'> <title>Clock</title></head><body><h1>Done!</h1></body></html>");
  Serial.println("request");
}
void handleTimer() {
  timerCentSecLength = server.arg("len").toInt() * 100;
  timerCentSecEnd = timerCentSecLength + (millis() / 10);
  onTimer = 1;
  clockMode = TIMER;

  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/html", "<!DOCTYPE html><html><head> <meta name='viewport' content='width=device-width, initial-scale=1'> <title>Clock</title></head><body><h1>Done!</h1></body></html>");
}

void handleAlarm() {

  if (existingAlarms < 5) {
    for (byte i = 0; i < 7; i++) {
      alarms[existingAlarms].weekDay[i] = server.arg(weekDayShort[i]).toInt();
    }
    alarms[existingAlarms].oneTime = server.arg("oneTime").toInt();
    alarms[existingAlarms].hour = server.arg("hour").toInt();
    alarms[existingAlarms].min = server.arg("min").toInt();
    existingAlarms++;
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.send(200, "text/html", "<!DOCTYPE html><html><head> <meta name='viewport' content='width=device-width, initial-scale=1'> <title>Clock</title></head><body><h1>Done!</h1></body></html>");
  } else {
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.send(200, "text/html", "<!DOCTYPE html><html><head> <meta name='viewport' content='width=device-width, initial-scale=1'> <title>Clock</title></head><body><h1>Too many Alarms!</h1></body></html>");
  }
}