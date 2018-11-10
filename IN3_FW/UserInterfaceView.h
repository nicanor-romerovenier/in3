#ifndef USERINTERFACEVIEW_H
#define USERINTERFACEVIEW_H

#include <memory>
#include <stdint.h>
#include <string>

// STM32 DMA Hardware-specific library
#include <Adafruit_ILI9341_STM.h>


class UserInterfaceView
{
public:
    UserInterfaceView();

    void drawSplashScreen(std::string message);

private:
    void setupScreen();

    std::unique_ptr<Adafruit_ILI9341_STM> m_screen;

    // Use hardware SPI lines+ - Pins from 4-6 are SPI
    const int8_t TFT_CS = 7;
    const int8_t TFT_DC = 31;
    const int8_t TFT_RST = 2;

    const uint16_t m_color_black = ILI9341_BLACK;
    const uint16_t m_color_navy = ILI9341_NAVY;
    const uint16_t m_color_white = ILI9341_WHITE;

    uint8_t m_text_font_size = 2;
};

#endif // USERINTERFACEVIEW_H
