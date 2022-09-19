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
  server.send(200, "text/plain", String(stripMode));
  Serial.println("request");
}
void handleTimer() {
  timerCentSecLength = server.arg("len").toInt() * 100;
  timerCentSecEnd = timerCentSecLength + (millis() / 10);
  onTimer = 1;
  clockMode = TIMER;

  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", "Timer setted!");
}