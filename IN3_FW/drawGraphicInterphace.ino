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
      if (pos_text[i] == 0) {
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
              if (firstTempWrite) {
                tft.drawFloat(desiredIn3Temp, 1, temperatureX - 65, temperatureY, textFontSize);
              }
              else {
                tft.drawRightString(initialSensorsValue, initialSensorPosition, temperatureY, textFontSize);
              }
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
              if (firstHumWrite) {
                tft.drawFloat(desiredIn3Hum, 1, temperatureX - 65, temperatureY, textFontSize);
              }
              else {
                tft.drawRightString(initialSensorsValue, initialSensorPosition, humidityY, textFontSize);
              }
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
              tft.drawFloat(previousTemperature[cornerNTC], 1, valuePosition, ypos, textFontSize);
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

void setVariablesPosition() {
  humidityX = tft.width() - 43;
  humidityY = graphicHeight(humidityGraphicPosition);
  temperatureX = tft.width() - 79;
  temperatureY = graphicHeight(temperatureGraphicPosition);
}

void drawHeading() {
  tft.fillRect(0, 0, tft.width(), height_heading, COLOR_HEADING);
  if (page) {
    drawBack();
  }
  tft.setTextColor(COLOR_MENU);
  tft.drawCentreString("In3ator", tft.width() / 2, height_heading / 5, textFontSize);
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
  for (int i = 0; i < backlight_intensity; i++) {
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
  }
  for (int i = 0; i < numWords; i++) {
    tft.drawCentreString(words[i], tft.width() / 2, tft.height() / (2 + i) , textFontSize);
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
  if (language) {
    tft.drawCentreString("PULSA BOTON", tft.width() / 2, text_height, textFontSize);
    tft.drawCentreString("3 SEC SALIR", tft.width() / 2, text_height + 30, textFontSize);
  }
  else {
    tft.drawCentreString("PRESS BUTTON", tft.width() / 2, text_height, textFontSize);
    tft.drawCentreString("3 SEC TO STOP", tft.width() / 2, text_height + 30, textFontSize);
  }
}

int graphicHeight(int position) {
  return ((tft.height() - height_heading) / (2 * rectangles) + position * (tft.height() - height_heading) / (rectangles) + letter_height);
}

void printLoadingBar() {
  barWidth = tft.width() / 4 * 3;
  barHeight = 15;
  barPosX = tft.width() / 2;
  barPosY = tft.height() / 3;
  barThickness = 3;
  temperatureX = barPosX - barWidth / 2 - 30;
  temperatureY = barPosY + barHeight / 2 + 10;
  updateSensors();
  tft.drawFloat(desiredIn3Temp, 1, barPosX + barWidth / 2 - 30, temperatureY, textFontSize);
  for (int i = 1; i <= barThickness; i++) {
    tft.drawRect(barPosX - barWidth / 2 - i, barPosY - barHeight / 2 - i, barWidth + i * 2, barHeight + i * 2, COLOR_FRAME_BAR);
  }
}
