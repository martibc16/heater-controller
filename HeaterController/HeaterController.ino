#include "config.h"
#include "Menu.h"
#include "LogicaCale.h"


void setup() {
  Serial.begin(9600);

  EEPROM.get(0, tSetACS);
  EEPROM.get(20, deltaT);
  refreshEeprom = millis();

  if (tSetACS > 80)
    tSetACS = 45;

  if (deltaT > 20)
    deltaT = 4;

  setSyncProvider(RTC.get);   // the function to get the time from the RTC
  if (timeStatus() != timeSet)
    Serial.println("Unable to sync with the RTC");
  else
    Serial.println("RTC has set the system time");

  pinMode(PINACS, OUTPUT);
  pinMode(PINCALE, OUTPUT);
  pinMode(PINFAT, OUTPUT);
  pinMode(PINCALDERA, OUTPUT);
  pinMode(PINTERMOSTAT, INPUT_PULLUP);
  pinMode(PINBOMBACIR, INPUT_PULLUP);
  pinMode(PINTERMOFAT, INPUT_PULLUP);
  pinMode(A6, INPUT);
  termostatActiu = false;
  canviEstat = false;
  ACSON = false;

  sensors.begin();
  sensors.setResolution(ACS, resolution);

  sensors.setWaitForConversion(false);
  sensors.requestTemperatures();

  delayInMillis = 750 / (1 << (12 - resolution));
  lastTempRequest = millis();

  
    Alarm.alarmRepeat(10, 0, 0, onProg);
    Alarm.alarmRepeat(13, 30, 0, offProg);
    Alarm.alarmRepeat(dowMonday , 16, 0, 0, onProg);
    Alarm.alarmRepeat(dowTuesday , 16, 0, 0, onProg);
    Alarm.alarmRepeat(dowWednesday , 16, 0, 0, onProg);
    Alarm.alarmRepeat(dowThursday , 16, 0, 0, onProg);
    Alarm.alarmRepeat(dowFriday , 16, 0, 0, onProg);
    Alarm.alarmRepeat(dowSaturday , 16, 0, 0, onProg);
    Alarm.alarmRepeat(19, 30, 0, offProg);
    Alarm.alarmRepeat(23, 0, 0, offProg);
  
 // newAlarm(9, 30, 1, true);


  joystickBtns.begin();
  Wire.begin();
  oled.begin(&Adafruit128x64, OLED_I2C_ADDRESS); //check config
  oled.setFont(menuFont);
  oled.clear();
  tempsStandby = millis();

#if RST_PIN >= 0
  oled.begin(&Adafruit128x64, I2C_ADDRESS, RST_PIN);
#else // RST_PIN >= 0
  oled.begin(&Adafruit128x64, I2C_ADDRESS);
#endif // RST_PIN >= 0


  mainMenu[0].disable();
  mainMenu[2].disable();
  mainMenu[3].disable();
  mainMenu[5].disable();

  Wire.setClock(400000);
}

float timre;
void loop() {
  timre = millis();
  readSensors();

  storeInEEPROM();

  checkForStateChanges();

  nav.poll();
  Alarm.delay(1);//simulate a delay when other tasks are done

  /**********Used for debugging************/
  /*Serial.print(hour());
    Serial.print("\t");
    Serial.print(minute());
    Serial.print("\t");
    Serial.print(second());
    Serial.print("\t");*/
    Serial.print(progACS);
    Serial.print("\t AutoProg:");
    Serial.print(autoProgACS);
    Serial.print("\t tACS: ");
    Serial.print(tACS);
    Serial.print("\t");
    Serial.print(tSetACS);
    Serial.print("\t");
    Serial.print(tSetACS+deltaT);
    Serial.print("\t ACSon:");
    Serial.println(ACSON);
  /**********************/


  if (digitalRead(BTN_SEL) == LOW || digitalRead(BTN_UP) == LOW || digitalRead(BTN_DOWN) == LOW || digitalRead(BTN_ESC) == LOW)
  {
    tempsActiu = millis();
    oled.ssd1306WriteCmd(SSD1306_DISPLAYON);
  }
  else if (millis() - tempsActiu > 60000)
    oled.ssd1306WriteCmd(SSD1306_DISPLAYOFF);

}
