bool getWifiMode() {
  return EEPROM.read(ADDR_WIFI_MODE);
}

void getEEPROMData() {
  wifiMode = EEPROM.read(ADDR_WIFI_MODE);
  ssid = readStringFromEEPROM(ADDR_WIFI_SSID);
  password = readStringFromEEPROM(ADDR_WIFI_PSW);
  readAlarmsfromEEPROM();
}


void putEEPROMData() {
  EEPROM.write(ADDR_WIFI_MODE, wifiMode);
  EEPROM.write(ADDR_ALARM_NUM, existingAlarms);
  writeStringToEEPROM(ADDR_WIFI_SSID, ssid);
  writeStringToEEPROM(ADDR_WIFI_PSW, password);
  EEPROM.commit();
}


String readStringFromEEPROM(int addr) {
  int len = EEPROM.read(addr);
  char data[len + 1];

  for (int i = 0; i < len; i++) {
    data[i] = EEPROM.read(addr + 1 + i);
  }
  data[len] = '\0';
  Serial.printf("read len:%d", len);

  return String(data);
}


void writeStringToEEPROM(int addr, const String& data) {
  byte len = data.length();
  Serial.printf("write len:%d", len);
  EEPROM.write(addr, len);
  EEPROM.commit();
  for (int i = 0; i < len; i++) {
    EEPROM.write(addr + 1 + i, data[i]);
  }
}


void WriteAlarmsToEEPROM() {
  EEPROM.write(ADDR_ALARM_NUM, existingAlarms);
  for (int i = 0; i < existingAlarms; i++) {
    EEPROM.write(ADDR_ALARM_START + (OFFSET_TOTAL * i) + OFFSET_HOUR, alarms[i].hour);
    EEPROM.write(ADDR_ALARM_START + (OFFSET_TOTAL * i) + OFFSET_MIN, alarms[i].min);
    EEPROM.write(ADDR_ALARM_START + (OFFSET_TOTAL * i) + OFFEST_ALREAYRINGED, alarms[i].alreadyRinged);

    char weekCompressed = '\0';
    for (int j = 0; j < 7; j++) {
      if (alarms[i].weekDay[j]) weekCompressed |= 1 << j;
    }
    if (alarms[i].oneTime) weekCompressed |= 1 << 7;

    EEPROM.write(ADDR_ALARM_START + (OFFSET_TOTAL * i) + OFFSET_WEEKCODE, weekCompressed);
    //Serial.printf("writing on EEPROM weekCompressed: %d;", weekCompressed);
  }
  EEPROM.commit();
}


void readAlarmsfromEEPROM() {
  existingAlarms = EEPROM.read(ADDR_ALARM_NUM);
  for (int i = 0; i < existingAlarms; i++) {
    alarms[i].hour = EEPROM.read(ADDR_ALARM_START + (OFFSET_TOTAL * i) + OFFSET_HOUR);
    alarms[i].min = EEPROM.read(ADDR_ALARM_START + (OFFSET_TOTAL * i) + OFFSET_MIN);
    alarms[i].alreadyRinged = EEPROM.read(ADDR_ALARM_START + (OFFSET_TOTAL * i) + OFFEST_ALREAYRINGED);
    char weekCompressed = EEPROM.read(ADDR_ALARM_START + (OFFSET_TOTAL * i) + OFFSET_WEEKCODE);


    for (int j = 0; j < 7; j++) {
      alarms[i].weekDay[j] = weekCompressed & (1 << j);
    }
    alarms[i].oneTime = weekCompressed & (1 << 7);
  }
}