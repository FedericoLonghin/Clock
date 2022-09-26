String getMainPage() {
  String html = "<!DOCTYPE html> <html lang='en'> <head> <meta charset='utf-8' /> <meta name='viewport' content='width=device-width, initial-scale=1' /> <title>Clock - Manager</title> <link rel='stylesheet' href='https://fonts.googleapis.com/css2?family=Material+Symbols+Outlined:opsz,wght,FILL,GRAD@20..48,100..700,0..1,-50..200' /> <style> @import url(https://fonts.googleapis.com/css?family=Poppins); * { box-sizing: border-box; } body { width: 100%; height: 100%; margin: 0; display: block; background-color: #fff; font-family: poppins; user-select: none; } nav { background-color: #fff; padding: 20px; padding-bottom: 0; width: 100%; text-align: center; font-family: poppins; color: #424242; font-size: 100px; } .button-body { margin: 30px; padding: 20px; align-items: center; border: solid; border-radius: 32px; border-color: #424242; color: #424242; text-align: center; font-size: 40px; } .modal { height: 0; font-size: 20px; text-align: left; display: none; } .modal-visible { height: auto; display: block; } .button { display: block; } .checkbox-container { margin-top: 10px; } .checkbox-item { text-align: left; font-size: 25px; margin-bottom: 10px; } .modal-section { margin: auto; max-width: 400px; margin-bottom: 20px; } .submit-button { margin-left: 70%; width: 30%; max-width: 200px; height: 50px; font-size: 20px; border-radius: 8px; font-family: Poppins; color: #424242; border-color: #424242; } .simple-button:active { background-color: #eee; } label { font-size: 20px; } .time-inputs { max-width: 75px; } .alarm-list-row { clear: left; margin-bottom: 10px; height: 80px; align-items: center; border-radius: 16px; border: solid; padding: 5px 10px; border-color: #424242; border-width: .8px; background-color: #eee; } .alarm-list-col { float: left; } .alarm-list-time { width: 90%; } .alarm-list-hour { width: 100%; height: 100%; font-size: 30px; } .alarm-list-day { width: 100%; height: 100%; font-size: 15px; } .alarm-list-delete { padding: 0px; width: 10%; height: 100%; margin-left: 0; } .material-symbols-outlined { font-size: 30px; align-self: center; margin-top: 20px; } </style> <script> const Http = new XMLHttpRequest(); const url = ''; function showModal(modalId) { document.getElementById(modalId).classList.toggle('modal-visible'); } </script> </head> <body> <nav> Clock </nav> <div class='button'> <div class='button-body simple-button' onclick='Http.open(\"GET\", url+\"/strip\");Http.send();'> Toggle Strip </div> </div> <div class='button'> <div class='button-body'> <div onclick='showModal(\"alarmListModal\");'> Alarm List </div> <div class='modal' id='alarmListModal'> ";
  if (!existingAlarms) {
    html += " No alarms available!";
  } else {
  }
  for (byte i = 0; i < existingAlarms; i++) {
    html += "<div class='alarm-list-row'> <div class='alarm-list-time alarm-list-col'> <div class='alarm-list-hour '>";
    html += alarms[i].hour;
    html += ":";
    html += alarms[i].min;
    html += "</div> <div class='alarm-list-day '>";
    html += alarms[i].oneTime ? "One time, " : "";
    for (byte j = 0; j < 7; j++) {
      if (alarms[i].weekDay[(j + 1) % 7]) {
        html += weekDayShort[(j + 1) % 7];
        html+=", ";
      }
    }
    html[html.length()-2] = '\0'; //remove last comma
    
    html += "</div> </div> <div class='alarm-list-col alarm-list-delete' onclick='Http.open(\"GET\", url+\"/delete?alarm=";
    html += i + 1;
    html += "\");Http.send(); location.reload();'><span class='material-symbols-outlined'>delete</span></div> <div style='clear:both;'></div> </div>";
  }

  html += "</div> </div> </div> <div class='button'> <div class='button-body'> <div onclick='showModal(\"newAlarmModal\");'> New Alarm </div> <div class='modal' id='newAlarmModal'> <form id='alarmForm' method='get' action='/alarm'> <div class='modal-section'> When will it ring? <div class='checkbox-container'> <div class='checkbox-item'> <div class='checkbox-item'> <label for='time'>Select a time:</label> <input type='time' id='time' name='time' class='time-inputs'required> </div> </div> <div class='checkbox-item'> <input type='checkbox' id='mon' name='Mon'> <label for='mon'>Monday</label> </div> <div class='checkbox-item'> <input type='checkbox' id='tue' name='Tue'> <label for='tue'>Tuesday</label> </div> <div class='checkbox-item'> <input type='checkbox' id='wed' name='Wed'> <label for='wed'>Wednesday</label> </div> <div class='checkbox-item'> <input type='checkbox' id='thu' name='Thu'> <label for='thu'>Thursday</label> </div> <div class='checkbox-item'> <input type='checkbox' id='fri' name='Fri'> <label for='fri'>Friday</label> </div> <div class='checkbox-item'> <input type='checkbox' id='sat' name='Sat'> <label for='sat'>Saturday</label> </div> <div class='checkbox-item'> <input type='checkbox' id='sun' name='Sun'> <label for='sun'>Sunday</label> </div> </div> </div> <div class='modal-section'> Repeat only one time <div class='checkbox-container'> <div class='checkbox-item'> <input type='checkbox' id='oneTime' name='oneTime'> <label for='oneTime'>Onetime</label> </div> </div> </div> <input type='submit' class='submit-button' form='alarmForm' value='Set'> </div> </form> </div> </div> <div class='button'> <div class='button-body'> <div onclick='showModal(\"newTimerModal\");'> New Timer </div> <div class='modal' id='newTimerModal'> <form id='timerForm' method='get' action='/timer'> <div class='modal-section'> How many seconds? <div class='checkbox-container'> <div class='checkbox-item'> <div class='checkbox-item'> <label for='timerLen'>Select a time:</label> <input type='number' id='timerLen' name='len' class='time-inputs' required> </div> </div> <input type='submit' class='submit-button' form='timerForm' value='Set'> </div> </form> </div> </div> </div> </body> </html>";
  return html;
}

String getAPPage() {
  String html = "<!DOCTYPE html> <html lang='en'> <head> <meta charset='UTF-8'> <meta http-equiv='X-UA-Compatible' content='IE=edge'> <meta name='viewport' content='width=device-width, initial-scale=1.0'> <title>Clock - WIFI Settings</title> </head> <body> <form action='/WIFIData'> <div> <label for='username'>SSID:</label><br> <input type='text' id='SSID' name='SSID'> </div> <br> <div> <label for='Pass'>Password:</label><br> <input type='password' id='Pass' name='Password'> </div> <br> <input type='submit' value='Enter'> </form> </body> </html>";
  return html;
}