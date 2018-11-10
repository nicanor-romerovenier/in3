#ifndef INCUBATORMANAGER_H
#define INCUBATORMANAGER_H

#include <memory>

#include "StorageHandler.h"
#include "UserInterfaceHandler.h"


class IncubatorManager
{
public:
    IncubatorManager();

private:
    void configurePins();
    void initializePins();

    std::unique_ptr<StorageHandler> m_storage_handler;
    std::unique_ptr<UserInterfaceHandler> m_ui_handler;

    const uint8_t m_screen_backlight = 3;
    const uint8_t m_pulse = 14;
    const uint8_t m_ict = 25;
    const uint8_t m_heater = 16;
    const uint8_t m_power_en = 18;
    const uint8_t m_fan_1 = 9;
    const uint8_t m_fan_2 = 8;
    const uint8_t m_fan_3 = 15;
    const uint8_t m_sterilize = 28;
    const uint8_t m_humidifier = 27;
};

#endif // INCUBATORMANAGER_H
