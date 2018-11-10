#include "IncubatorManager.h"


IncubatorManager::IncubatorManager()
{
    m_storage_handler = std::unique_ptr<StorageHandler>(new StorageHandler());
    m_ui_handler = std::unique_ptr<UserInterfaceHandler>(new UserInterfaceHandler());

    this->configurePins();
    this->initializePins();
}

void IncubatorManager::configurePins()
{
    pinMode(m_screen_backlight, OUTPUT);
    pinMode(m_pulse, INPUT_PULLUP);
    pinMode(m_ict, OUTPUT);
    pinMode(m_heater, OUTPUT);
    pinMode(m_power_en, OUTPUT);
    pinMode(m_fan_1, OUTPUT);
    pinMode(m_fan_2, OUTPUT);
    pinMode(m_fan_3, OUTPUT);
    pinMode(m_sterilize, OUTPUT);
    pinMode(m_humidifier, OUTPUT);
}

void IncubatorManager::initializePins()
{
    analogWrite(m_screen_backlight, 100);
    digitalWrite(m_ict, LOW);
    digitalWrite(m_heater, LOW);
    digitalWrite(m_power_en, LOW);
    digitalWrite(m_fan_1, LOW);
    digitalWrite(m_fan_2, LOW);
    digitalWrite(m_fan_3, LOW);
    digitalWrite(m_sterilize, LOW);
    digitalWrite(m_humidifier, LOW);
}
