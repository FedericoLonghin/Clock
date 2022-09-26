String getMainPage() {
  String html = "<!DOCTYPE html> <html lang='en'> <head> <meta charset='utf-8' /> <meta name='viewport' content='width=device-width, initial-scale=1' /> <title>Clock - Manager</title> <style> @import url(https://fonts.googleapis.com/css?family=Poppins); * { box-sizing: border-box; } body { width: 100%; height: 100%; margin: 0; display: block; background-color: #fff; font-family: poppins; user-select: none; } nav { background-color: #fff; padding: 20px; padding-bottom: 0; width: 100%; text-align: center; font-family: poppins; color: #424242; font-size: 100px; } .button-body { margin: 30px; padding: 20px; align-items: center; border: solid; border-radius: 32px; border-color: #424242; color: #424242; text-align: center; font-size: 40px; } .modal { visibility: hidden; height: 0; font-size: 20px; text-align: left; display: block; } .modal-visible { visibility: visible; height: auto; } .button { display: block; } .checkbox-container { margin-top: 10px; } .checkbox-item { text-align: left; font-size: 25px; margin-bottom: 10px; } .modal-section { margin: auto; max-width: 400px; margin-bottom: 20px; } .submit-button { margin-left: 70%; width: 30%; max-width: 200px; height: 50px; font-size: 20px; border-radius: 8px; font-family: Poppins; color: #424242; border-color: #424242; } .time-picker { height: 40px; font-size: 20px; border-radius: 8px; font-family: Poppins; color: #424242; border-color: #424242; } .simple-button:active { background-color: #eee; } label{ font-size: 20px; } </style> <script> const Http = new XMLHttpRequest(); const url = ''; function showModal() { document.getElementById('alarmModal').classList.toggle('modal-visible'); } </script> </head> <body> <nav> Clock </nav> <div class='button'> <div class='button-body simple-button' onclick='Http.open(\"GET\", url+\"/strip\");Http.send();'> Toggle Strip </div> </div> <div class='button'> <div class='button-body'> <div onclick='showModal();'> New Alarm </div> <div class='modal' id='alarmModal'> <form id='alarmForm' method='get' action='/alarm'> <div class='modal-section'> When will it ring? <div class='checkbox-container'> <div class='checkbox-item'> <div class='checkbox-item'> <label for='time'>Select a time:</label> <input type='time' id='time' name='time'> </div> </div> <div class='checkbox-item'> <input type='checkbox' id='mon' name='mon'> <label for='mon'>Monday</label> </div> <div class='checkbox-item'> <input type='checkbox' id='tue' name='tue'> <label for='tue'>Tuesday</label> </div> <div class='checkbox-item'> <input type='checkbox' id='wed' name='wed'> <label for='wed'>Wednesday</label> </div> <div class='checkbox-item'> <input type='checkbox' id='thu' name='thu'> <label for='thu'>Thursday</label> </div> <div class='checkbox-item'> <input type='checkbox' id='fri' name='fri'> <label for='fri'>Friday</label> </div> <div class='checkbox-item'> <input type='checkbox' id='sat' name='sat'> <label for='sat'>Saturday</label> </div> <div class='checkbox-item'> <input type='checkbox' id='sun' name='sun'> <label for='sun'>Sunday</label> </div> </div> </div> <div class='modal-section'> Repeat only one time <div class='checkbox-container'> <div class='checkbox-item'> <input type='checkbox' id='oneTime' name='oneTime'> <label for='oneTime'>Onetime</label> </div> </div> </div> <input type='submit' class='submit-button' form='alarmForm' value='Set'> </div> </form> </div> </div> </body> </html>";
  return html;
}
String getAPPage() {
  String html = "<!DOCTYPE html> <html lang='en'> <head> <meta charset='UTF-8'> <meta http-equiv='X-UA-Compatible' content='IE=edge'> <meta name='viewport' content='width=device-width, initial-scale=1.0'> <title>Clock - WIFI Settings</title> </head> <body> <form action='/WIFIData'> <div> <label for='username'>SSID:</label><br> <input type='text' id='SSID' name='SSID'> </div> <br> <div> <label for='Pass'>Password:</label><br> <input type='password' id='Pass' name='Password'> </div> <br> <input type='submit' value='Enter'> </form> </body> </html>";
  return html;
}