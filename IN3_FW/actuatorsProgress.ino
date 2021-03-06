void actuatorsProgress() {
  byte  numWords = 0;
  temperaturePercentage = 0;
  page = actuatorsProgressPage;
  tft.setTextSize(1);
  print_text = 0;
  rectangles = numWords;
  drawGraphicInterface();
  drawHeading();
  tft.setTextColor(COLOR_MENU_TEXT);
  setSensorsGraphicPosition();
  drawActuatorsSeparators();
  if (controlTemperature) {
    temperatureAtStart = temperature[roomNTC];
    printLoadingTemperatureBar();
    switch (language) {
      case spanish:
        textToWrite = "Temperatura";
        break;
      case english:
      case french:
        textToWrite = "Temperature";
        break;
    }
    tft.drawCentreString(textToWrite, tft.width() / 2, tempBarPosY - 4 * letter_height / 3, textFontSize);
    tft.drawCentreString("%", tft.width() / 2 + 14, temperatureY , textFontSize);
  }
  if (controlHumidity) {
    humidityAtStart = humidity;
    printLoadingHumidityBar();
    switch (language) {
      case spanish:
        textToWrite = "Humedad";
        break;
      case english:
        textToWrite = "Humidity";
        break;
      case french:
        textToWrite = "Humidite";
        break;
    }
    tft.drawCentreString(textToWrite, tft.width() / 2, humBarPosY - 4 * letter_height / 3, textFontSize);
    tft.drawCentreString("%", tft.width() / 2 + 14, humidityY, textFontSize);
  }
  tft.setTextColor(COLOR_WARNING_TEXT);
  drawStop();
  state_blink = 1;
  checkTempSensorPin();
  if (swapTempSensors) {
    asignCorrectTempSensorsPin();
  }
  while (!digitalRead(pulse));
  turnFansOn();
  if (temperatureAtStart > temperature[roomNTC]) {
    temperatureAtStart = temperature[roomNTC];
  }
  if (controlTemperature) {
    if (temperaturePIDcontrol) {
      startPID();
    }
  }
  while (1) {
    updateData();
    if (controlTemperature) {
      if (!temperaturePIDcontrol) {
        basicTemperatureControl();
      }
    }
    if (controlHumidity) {
      basicHumidityControl();
    }
    while (!digitalRead(pulse)) {
      updateData();
      back_mode();
    }
    blinkGoBackMessage();
  }
}

void checkTempSensorPin() {
  //pending: program timeout too
  Serial.println("checking NTC pinout");
  float prevroomTemp = temperature[roomNTC];
  float prevHeaterTemp = temperature[heaterNTC];
  Serial.println(prevroomTemp);
  Serial.println(prevHeaterTemp);
  bool exitCheck = 0;
  long timeElapsedChecking = millis();
  turnFansOn();
  heatUp();
  while (!exitCheck) {
    updateData();
    while (!digitalRead(pulse)) {
      updateData();
      back_mode();
    }
    if (millis() - timeElapsedChecking > CheckTempSensorPinTimeout) {
      //error
    }
    if ((temperature[heaterNTC] - prevHeaterTemp) > CheckSensorRaiseTemp) {
      swapTempSensors = 0;
      exitCheck = 1;
    }
    if ((temperature[roomNTC] - prevroomTemp) > CheckSensorRaiseTemp) {
      swapTempSensors = 1;
      EEPROM.write(EEPROM_swapTempSensors, swapTempSensors);
      exitCheck = 1;
    }
    delay(500);
    printStatus();
  }
}


void asignCorrectTempSensorsPin() {
  int valueRetainer = THERMISTOR_HEATER;
  THERMISTOR_HEATER = THERMISTOR_ROOM;
  THERMISTOR_ROOM = valueRetainer;
  NTCpin[roomNTC] = {THERMISTOR_ROOM};
  NTCpin[heaterNTC] = {THERMISTOR_HEATER};
  Serial.println("NTC pins swapped");
}

void blinkGoBackMessage() {
  if (millis() - blinking > 1000) {
    blinking = millis();
    state_blink = !state_blink;
    if (state_blink) {
      tft.setTextColor(ILI9341_ORANGE);
    }
    else {
      tft.setTextColor(COLOR_MENU);
      blinking += 400;
    }
    drawStop();
  }
}

void basicTemperatureControl() {
  if (temperature[roomNTC] < desiredRoomTemp) {
    heatUp();
  }
  else {
    analogWrite(HEATER, 0);
  }
}

void basicHumidityControl() {
  if (humidity < desiredRoomHum) {
    digitalWrite(HUMIDIFIER, HIGH);
  }
  else {
    digitalWrite(HUMIDIFIER, LOW);
  }
}

void heatUp() {
  if (temperature[heaterNTC] < heaterLimitTemp) {
    analogWrite(HEATER, maxHeaterPWM);
  }
  else {
    analogWrite(HEATER, 0);
  }
}

