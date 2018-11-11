#include "UserInterfaceView.h"


UserInterfaceView::UserInterfaceView()
{
    m_screen = std::unique_ptr<Adafruit_ILI9341_STM>(new Adafruit_ILI9341_STM(m_TFT_CS, m_TFT_DC, m_TFT_RST)); // Use hardware SPI

    m_screen->begin();
    this->setupScreen();
}

void UserInterfaceView::drawSplashScreen(const char* message)
{
    // We need to copy the const string since the Adafruit_ILI9341_STM library is not const-correct
    char *message_copy = new char[strlen(message)+1];
    strcpy(message_copy, message);

    m_screen->drawCentreString(message_copy, m_screen->width() / 2, m_screen->height() / 2, m_text_font_size);

    free(message_copy);
}

void UserInterfaceView::setupScreen()
{
    m_screen->setRotation(1);
    m_screen->setTextSize(1);
    m_screen->fillScreen(m_color_navy);
    m_screen->setTextColor(m_color_white);
}

