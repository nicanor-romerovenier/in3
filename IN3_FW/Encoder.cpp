#include "Encoder.h"
#include "Arduino.h"


Encoder::Encoder()
{
    m_timer = std::unique_ptr<HardwareTimer>(new HardwareTimer(1));

    this->initializeEncoder();

    Serial.println("EncoderHandler::EncoderHandler()");
}

void Encoder::initializeEncoder()
{
    encodertimer = millis(); // acceleration measurement

    encstate = HIGH;
    encflag = HIGH;
    A_set = false;
    B_set = false;
    encoderpos = 0;
    pinMode(encoderpinA, INPUT_PULLUP);
    pinMode(encoderpinB, INPUT_PULLUP);
    lastEncoderPos = 1;

    // timer setup for encoder
    m_timer->pause();
    m_timer->setPeriod(ENCODER_RATE); // in microseconds
    m_timer->setChannel1Mode(TIMER_OUTPUT_COMPARE);
    m_timer->setCompare(TIMER_CH1, 1);  // Interrupt 1 count after each update
    m_timer->attachCompare1Interrupt(Encoder::readEncoders);
    m_timer->refresh();
    m_timer->resume();
}

void Encoder::readEncoders()
{
    Serial.println("EncoderHandler::readEncoders()");
}
