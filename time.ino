void fetchTime(){
    timeClient.begin();
    timeClient.setTimeOffset(7200);
    timeClient.update();
    timeFetc.hour=timeClient.getHours();
    timeFetc.min=timeClient.getMinutes();
    timeFetc.sec=timeClient.getSeconds();
    timeLastFetch=millis();
    }

void getRealTime(){
    int sec=(millis()-timeLastFetch)/1000;
    timeReal.sec=(timeFetc.sec+sec);
    timeReal.min=(timeFetc.min+timeReal.sec/60);
    timeReal.hour=(timeFetc.hour+sec/3600);
    timeReal.sec= timeReal.sec%60;
    timeReal.min=    timeReal.min%60;
    timeReal.hour=timeReal.hour%24;

    Serial.printf("%d:%d:%d",timeReal.hour,timeReal.min,timeReal.sec);
    Serial.println();
} 