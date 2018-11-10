#include "UserInterfaceView.h"


UserInterfaceView::UserInterfaceView()
{
    m_screen = std::unique_ptr<Adafruit_ILI9341_STM>(new Adafruit_ILI9341_STM(TFT_CS, TFT_DC, TFT_RST)); // Use hardware SPI

    m_screen->begin();
    this->setupScreen();
}

void UserInterfaceView::drawSplashScreen(std::string message)
{
    m_screen->drawCentreString((char*)message.c_str(), m_screen->width() / 2, m_screen->height() / 2, m_text_font_size);
}

void UserInterfaceView::setupScreen()
{
    m_screen->setRotation(1);
    m_screen->setTextSize(1);
    m_screen->fillScreen(m_color_navy);
    m_screen->setTextColor(m_color_white);
}

