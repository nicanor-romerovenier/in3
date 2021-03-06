void drawGraphicInterface() {
  if (!page) {
    tft.fillRect(width_select, height_heading, tft.width() - width_select, tft.height() - height_heading, COLOR_MENU);
  }
  else {
    tft.fillRect(0, height_heading, tft.width(), tft.height() - height_heading, COLOR_MENU);
  }
  if (print_text) {
    tft.fillRect(0, height_heading, width_select, (tft.height() - height_heading) / rectangles, COLOR_SELECTED);
  }
  for (int i = 2; i <= rectangles; i++) {
    tft.fillRect(0, (tft.height() - height_heading) * (i - 1) / rectangles + height_heading, width_select, (tft.height() - height_heading) / rectangles, COLOR_BAR);
    tft.fillRect(0, (tft.height() - height_heading) * (i - 1) / rectangles + height_heading - 1, tft.width(), width_indentation, WHITE);
  }
  tft.drawRect(0, tft.height() - 1, width_select, tft.height() - 1, COLOR_MENU);
  if (print_text) {
    tft.setTextSize(1);
    text_size = 1;
    for (int i = 0; i < rectangles; i++) {
      ypos = graphicHeight(i);
      if (!pos_text[i]) {
        tft.drawString(words[i], width_select + side_gap, ypos, textFontSize);
      }
      else if (pos_text[i]) {
        tft.drawCentreString(words[i], width_select + (tft.width() - width_select) / 2, ypos, textFontSize);
      }
      switch (page) {
        case menuPage:
          switch (i) {
            case temperatureGraphicPosition:
              drawTemperatureUnits();
              updateSensors();
              tft.drawRightString(initialSensorsValue, initialSensorPosition, temperatureY, textFontSize);
              break;
            case LEDGraphicPosition:
              if (LEDIntensity) {
                drawRightNumber(LEDIntensity, 280, ypos);
                tft.drawRightString("%", unitPosition, ypos, textFontSize);
              }
              else {
                tft.drawRightString("OFF", unitPosition, ypos, textFontSize);
              }
              break;
            case humidityGraphicPosition:
              drawHumidityUnits();
              tft.drawRightString(initialSensorsValue, initialSensorPosition, humidityY, textFontSize);
              updateSensors();
              break;
          }
          break;
        case settingsPage:
          switch (i) {
            case autoLockGraphicPosition:
              if (auto_lock) {
                switch (language) {
                  case spanish:
                    textToWrite = "SI";
                    break;
                  case english:
                    textToWrite = "YES";
                    break;
                  case french:
                    textToWrite = "OUI";
                    break;
                }
              }
              else {
                switch (language) {
                  case spanish:
                    textToWrite = "NO";
                    break;
                  case english:
                    textToWrite = "NO";
                    break;
                  case french:
                    textToWrite = "PAS";
                    break;
                }
              }
              tft.drawRightString(textToWrite, unitPosition, ypos, textFontSize);
              break;
            case languageGraphicPosition:
              switch (language) {
                case spanish:
                  textToWrite = "SPA";
                  break;
                case english:
                  textToWrite = "ENG";
                  break;
                case french:
                  textToWrite = "FRA";
                  break;
              }
              tft.drawRightString(textToWrite, unitPosition, ypos, textFontSize);
              break;
            case heaterTempGraphicPosition:
              drawRightNumber(heaterLimitTemp, 280, ypos);
              tft.drawRightString("C", unitPosition, ypos, textFontSize);
              break;
          }
          break;
        case calibrateSensorsPage:
          switch (i) {
            case temperatureCalibrationGraphicPosition:
              tft.drawFloat(previousTemperature[roomNTC], 1, valuePosition, ypos, textFontSize);
              break;
            case humidityCalibrationGraphicPosition:
              tft.drawFloat(humidity, 0, valuePosition, ypos, textFontSize);
              break;
          }
          break;
      }
    }
  }
}

void setSensorsGraphicPosition() {
  switch (page) {
    case menuPage:
      humidityX = tft.width() - 50;
      humidityY = graphicHeight(humidityGraphicPosition);
      temperatureX = tft.width() - 79;
      temperatureY = graphicHeight(temperatureGraphicPosition);
      break;
    case actuatorsProgressPage:
      barWidth = tft.width() / 4 * 3;
      barHeight = 15;
      tempBarPosX = tft.width() / 2;
      tempBarPosY = tft.height() / 3 - 11;
      humBarPosX = tempBarPosX;
      humBarPosY = 3 * tft.height() / 4 + 15;
      temperatureX = tempBarPosX - barWidth / 2 - 38;
      temperatureY = tempBarPosY + barHeight / 2 + 5;
      humidityX = tempBarPosX - barWidth / 2;
      humidityY = 4 * tft.height() / 5 + 17;
      break;
  }
}

void drawHeading() {
  tft.fillRect(0, 0, tft.width(), height_heading, COLOR_HEADING);
  if (page) {
    drawBack();
  }
  tft.setTextColor(COLOR_MENU);
  tft.drawCentreString(headingTitle, tft.width() / 2, height_heading / 5, textFontSize);
  tft.drawCentreString(FWversion, tft.width() - 3 * letter_width, height_heading / 5, textFontSize);
}

void eraseBar() {
  tft.fillRect(0, (tft.height() - height_heading) * (bar_pos - 1) / rectangles + height_heading, width_select, (tft.height() - height_heading) / rectangles, COLOR_BAR);
}

void updateBar() {
  tft.fillRect(0, (tft.height() - height_heading) * (bar_pos - 1) / rectangles + height_heading, width_select, (tft.height() - height_heading) / rectangles, COLOR_SELECTED);
  for (int i = 2; i <= rectangles; i++) {
    tft.fillRect(0, (tft.height() - height_heading) * (i - 1) / rectangles + height_heading - 1, tft.height(), width_indentation, WHITE); //mejorable
  }
}

void clearMenu() {
  tft.fillRect(0, height_heading, tft.width(), tft.height() - height_heading, BLACK);
}

void drawBack() {
  tft.fillRect(0, 0, width_back, height_heading, COLOR_HEADING);
  tft.drawRect(0, 0, width_back, height_heading, BLACK);
  tft.fillTriangle(arrow_height, height_heading / 2, width_back / 2 , arrow_height, width_back / 2, height_heading - arrow_height, COLOR_ARROW);
  tft.fillRect(width_back / 2, height_heading / 2 - arrow_tail, width_back / 2 - arrow_height, arrow_tail, COLOR_ARROW);
  tft.fillRect(width_back / 2, height_heading / 2, width_back / 2 - arrow_height, arrow_tail, COLOR_ARROW);
}

void drawRightNumber(int n, int x, int i) {
  length = 1;
  for (long k = 10; k <= n; k *= 10) {
    length++;
  }
  tft.drawNumber(n, x - length * 14, i, textFontSize);
}

void loadLogo() {
  tft.setTextSize(1);
  tft.fillScreen(introBackColor);
  tft.setTextColor(introTextColor);
  drawIntroMessage();
  for (int i = 0; i <= backlight_intensity; i++) {
    analogWrite(SCREENBACKLIGHT, i);
    delay(brightenRate);
  }
  delay(introDelay);
}

void drawIntroMessage() {
  byte numWords = 1;
  switch (language) {
    case english:
      words[0]  = "Welcome to in3";
      break;
    case spanish:
      words[0]  = "Bienvenido a in3";
      break;
    case french:
      words[0]  = "Bienvenue a in3";
      break;
  }
  for (int i = 0; i < numWords; i++) {
    tft.drawCentreString(words[i], tft.width() / 2, tft.height() / (2 + i) , textFontSize);
  }
}

void drawHardwareErrorMessage() {
  byte numErrors = 0;
  byte j;
  int yErrorPos = letter_height;
  tft.drawCentreString("Hardware errors:", tft.width() / 2, yErrorPos , textFontSize);
  yErrorPos += letter_height;
  for (int i = 0; i < hardwareComponents; i++) {
    if (errorHardwareCode[i]) {
      numErrors++;
      if (yErrorPos > (tft.height() - 4 * letter_height)) {
        i = hardwareComponents;
      }
      else {
        tft.drawCentreString(errorComponent[i], tft.width() / 2, yErrorPos , textFontSize);
        yErrorPos += letter_height;
      }
    }
  }
  if (testCritical) {
    tft.setTextColor(ILI9341_RED);
    yErrorPos += letter_height;
    tft.drawCentreString("CRITICAL ERROR, FIX", tft.width() / 2, yErrorPos , textFontSize);
    yErrorPos += letter_height;
    tft.drawCentreString("PROBLEM TO CONTINUE", tft.width() / 2, yErrorPos , textFontSize);
  }
  else {
    tft.setTextColor(ILI9341_ORANGE);
    tft.drawCentreString("lost functions:", tft.width() / 2, yErrorPos , textFontSize);
    yErrorPos += letter_height;
    tft.drawCentreString("temperature, jaundice LED", tft.width() / 2, yErrorPos , textFontSize);
    yErrorPos += letter_height;
    tft.drawCentreString("pulse to continue", tft.width() / 2, yErrorPos , textFontSize);
  }
}

void drawHumidityUnits() {
  tft.drawRightString("/", separatorPosition, ypos, textFontSize);
  tft.drawRightString("%", unitPosition, ypos, textFontSize);
}

void drawTemperatureUnits() {
  tft.drawRightString("/", separatorPosition, ypos, textFontSize);
  tft.drawRightString("C", unitPosition, ypos, textFontSize);
}

void drawCentreNumber(int n, int x, int i) {
  length = 1;
  for (long k = 10; k <= n; k *= 10) {
    length++;
  }
  if (text_size == 2) {
    tft.drawNumber(n, x - length * 27, i, 6);
  }
  else {
    tft.drawNumber(n, x - length * text_size * 7, i, textFontSize);
  }
}

void drawStop() {
  switch (language) {
    case spanish:
      textToWrite = "Pulsa 2 seg para salir";
      break;
    case english:
      textToWrite = "Press 2 sec to go back";
      break;
    case french:
      textToWrite = "appuyez 2 sec pour voler";
      break;
  }
  tft.drawCentreString(textToWrite, tft.width() / 2, tft.height() / 2, textFontSize);
}

int graphicHeight(int position) {
  return ((tft.height() - height_heading) / (2 * rectangles) + position * (tft.height() - height_heading) / (rectangles) + letter_height);
}

void drawHumidity() {
  if (readHumSensor()) {
    tft.setTextColor(COLOR_MENU);
    drawCentreNumber(previousHumidity, humidityX, humidityY);
    tft.setTextColor(COLOR_MENU_TEXT);
    drawCentreNumber(humidity, humidityX, humidityY);
    previousHumidity = humidity;
  }
}

void drawStartMessage() {
  if (enableSet) {
    tft.setTextColor(COLOR_MENU);
    tft.drawCentreString(helpMessage, width_select + (tft.width() - width_select) / 2, getYpos(goToProcessRow), textFontSize);
    tft.setTextColor(COLOR_MENU_TEXT);
    switch (language) {
      case spanish:
        words[startGraphicPosition] = "Empezar";
        break;
      case english:
        words[startGraphicPosition] = "Start";
        break;
      case french:
        words[startGraphicPosition] = "Debut";
        break;
    }
    tft.drawCentreString(words[startGraphicPosition], width_select + (tft.width() - width_select) / 2, getYpos(goToProcessRow), textFontSize);
  }
}

void drawActuatorsSeparators() {
  barThickness = 3;
  tft.fillRect(0, tft.height() / 2 - letter_height / 3, tft.width(), barThickness, COLOR_FRAME_BAR);
  tft.fillRect(0, tft.height() / 2 + letter_height, tft.width(), barThickness, COLOR_FRAME_BAR);
}

void printLoadingHumidityBar() {
  barThickness = 3;
  tft.drawFloat(desiredRoomHum, 1, humBarPosX + barWidth / 2 - 30, humidityY, textFontSize);
  for (int i = 1; i <= barThickness; i++) {
    tft.drawRect(humBarPosX - barWidth / 2 - i, humBarPosY - barHeight / 2 - i, barWidth + i * 2, barHeight + i * 2, COLOR_FRAME_BAR);
  }
}

void printLoadingTemperatureBar() {
  barThickness = 3;
  tft.drawFloat(desiredRoomTemp, 1, tempBarPosX + barWidth / 2 - 30, temperatureY, textFontSize);
  for (int i = 1; i <= barThickness; i++) {
    tft.drawRect(tempBarPosX - barWidth / 2 - i, tempBarPosY - barHeight / 2 - i, barWidth + i * 2, barHeight + i * 2, COLOR_FRAME_BAR);
  }
}
