void readSensors() {
  if (millis() - lastTempRequest >= delayInMillis) // waited long enough??
  {
    sensors.requestTemperatures();
    int tmp;

    tmp = sensors.getTempC(ACS);
    if (tmp > -120)
      tACS = (((tmp - RawLowACS) * ReferenceRange) / (RawHighACS - RawLowACS)) + ReferenceLow;
      
    tmp = sensors.getTempC(TAIACS);
    if (tmp > -120)
      tTAIACS = (((tmp - RawLowTAIACS) * ReferenceRange) / (RawHighTAIACS - RawLowTAIACS)) + ReferenceLow;
      
    tmp = sensors.getTempC(TAICal);
    if (tmp > -120)
      tTAICal = (((tmp - RawLowTAICal) * ReferenceRange) / (RawHighTAICal - RawLowTAICal)) + ReferenceLow;
  }

  /*if (tACS < -100 || tTAIACS < -100 || tTAICal < -100) //s'ha de canviar el valor en funció del offset de readSensors()
    {
    oled.clear();
    oled.set2X();
    oled.println("Error");
    oled.set1X();
    oled.print("Sensor ");
    if (tACS == -128)
      oled.println("ACS");
    if (tTAIACS == -128)
      oled.println("TAIACS");
    if (tTAICal == -128)
      oled.println("TAICal");

    while (tACS == -128 || tTAIACS == -128) // || tTAICal == -127)
      readSensors();

    oled.clear();
    oled.println("Clica per continuar");

    }*/

}

void updateActuators() {
  if (ACSON)
  {
    digitalWrite(PINACS, HIGH);
    digitalWrite(PINCALDERA, HIGH);

    if (!termostatActiu &&  digitalRead(PINCALE) == HIGH)//if central heating actuator was onit can now turn off since the DHW turns on
      digitalWrite(PINCALE, LOW);
  }
  if (!ACSON)
  {
    if (!termostatActiu)
      digitalWrite(PINCALDERA, LOW);
    else
      digitalWrite(PINACS, LOW);
  }


  if (termostatActiu)
  {
    digitalWrite(PINCALE, HIGH);
    digitalWrite(PINCALDERA, HIGH);

    if (!ACSON &&  digitalRead(PINACS) == HIGH) //if dhw actuator was on it can now turn off since the central heating turns on
      digitalWrite(PINACS, LOW);
  }
  if (!termostatActiu)
    if (!ACSON)
      digitalWrite(PINCALDERA, LOW);
    else if (!FATactiu)
      digitalWrite(PINCALE, LOW);


  if (FATactiu)
  {
    digitalWrite(PINFAT, HIGH);
    digitalWrite(PINCALE, HIGH);

    if (!ACSON &&  digitalRead(PINACS) == HIGH) 
      digitalWrite(PINACS, LOW);
  }
  if (!FATactiu)
  {
    digitalWrite(PINFAT, LOW);
    if (!ACSON && !termostatActiu)
      digitalWrite(PINCALDERA, LOW);
    else if (!termostatActiu && ACSON)
      digitalWrite(PINCALE, LOW);
  }
}

void onProg()
{
  autoProgACS = true;
  if (progACS == 1)
  {
    progACS = 0;
  }
}

void offProg()
{
  autoProgACS = false;
  if (progACS == 1)
  {
    progACS = 0;
  }
}

void storeInEEPROM()
{
  if (millis() - refreshEeprom > 1000000)
  {
    EEPROM.put(0, tSetACS);
    EEPROM.put(20, deltaT);
    refreshEeprom = millis();
  }
}

void checkForStateChanges()
{
  if (!termostatActiu && digitalRead(PINBOMBACIR) == HIGH && !FATactiu && digitalRead(PINCALE) == HIGH ) //If circulating pump is already off
    digitalWrite(PINCALE, LOW);


  if (!ACSON && digitalRead(PINBOMBACIR) == HIGH && digitalRead(PINACS) == HIGH ) //if circulating pump is already off
    digitalWrite(PINACS, LOW);


  if ((autoProgACS || progACS == 1 || progACS == 2) && progACS != 3)
  {
    if ((tACS < tSetACS - deltaT) && !ACSON )
    {
      ACSON = true;
      canviEstat = true;
      tempsStandby = millis();
    }
    else if ((tACS > tSetACS + deltaT) && ACSON)
    {
      ACSON = false;
      canviEstat = true;
      tempsStandby = millis();
    }
  }
  else if (ACSON && ((!autoProgACS && progACS != 2) || progACS == 3))
  {
    ACSON = false;
    canviEstat = true;
    tempsStandby = millis();
  }

  if (digitalRead(PINTERMOSTAT) == LOW && !termostatActiu)
  {
    termostatActiu = true;
    canviEstat = true;
    tempsStandby = millis() + 7001;
  }
  else if (digitalRead(PINTERMOSTAT) == HIGH && termostatActiu)
  {
    termostatActiu = false;
    canviEstat = true;
    tempsStandby = millis() + 7001;
  }

  if (digitalRead(PINTERMOFAT) == LOW && !FATactiu)
  {
    FATactiu = true;
    canviEstat = true;
    tempsStandby = millis() + 7001;
  }
  else if (digitalRead(PINTERMOFAT) == HIGH && FATactiu)
  {
    FATactiu = false;
    canviEstat = true;
    tempsStandby = millis() + 7001;
  }

  if (canviEstat && millis() - tempsStandby > 7000)
  {
    updateActuators();
    canviEstat = false;
    tempsStandby = 4294967295;
  }
}
