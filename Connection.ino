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

void handleMain(){
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/html", getMainPage());

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
      alarms[existingAlarms].weekDay[i] = server.arg(weekDayShort[i]) == "on";
    }
    alarms[existingAlarms].oneTime = server.arg("oneTime") == "on";
    char compressedTime[8];
    server.arg("time").toCharArray(compressedTime, 8);
    decodeTime(compressedTime, &alarms[existingAlarms].hour, &alarms[existingAlarms].min);
    existingAlarms++;
    WriteAlarmsToEEPROM();
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.send(200, "text/html", "<!DOCTYPE html><html><head> <meta name='viewport' content='width=device-width, initial-scale=1'> <title>Clock</title></head><body><h1>Done!</h1></body></html>");
    Serial.println(compressedTime);
  } else {
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.send(200, "text/html", "<!DOCTYPE html><html><head> <meta name='viewport' content='width=device-width, initial-scale=1'> <title>Clock</title></head><body><h1>Too many Alarms!</h1></body></html>");
  }
}

void handleAlarmList() {
  String page = "<!DOCTYPE html><html><head> <meta name='viewport' content='width=device-width, initial-scale=1'> <title>Clock</title></head><body><h1>Alarm list:</h1>";
  for (byte i = 0; i < existingAlarms; i++) {
    page += "<p>Alarm n.";
    page += i + 1;
    page += " --- dayCode:";
    page += alarms[i].weekDay[0];
    page += alarms[i].weekDay[1];
    page += alarms[i].weekDay[2];
    page += alarms[i].weekDay[3];
    page += alarms[i].weekDay[4];
    page += alarms[i].weekDay[5];
    page += alarms[i].weekDay[6];
    page += " - Onetime:";
    page += alarms[i].oneTime;
    page += " - ";
    page += alarms[i].hour;
    page += ":";
    page += alarms[i].min;
  }
  page += "</body></html>";
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/html", page);
}

void handleDelete() {
  String page = "";
  byte al = server.arg("alarm").toInt();
  if (al && al - 1 <= existingAlarms) {  //check if the number argument is present in the query
    deleteAlarm(al - 1);
    page += "<!DOCTYPE html><html><head> <meta name='viewport' content='width=device-width, initial-scale=1'> <title>Clock</title></head><body><h1>Deleted alarm n. ";
    page += al;
    page += "</h1></body></html>";
  } else {
    page += "<!DOCTYPE html><html><head> <meta name='viewport' content='width=device-width, initial-scale=1'> <title>Clock</title></head><body><h1>Please, specify the number! </h1></body></html>";
  }
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/html", page);
}