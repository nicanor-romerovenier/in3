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
    Serial.print("encoderpos =");
    Serial.println(encoderpos);

//    if ( (gpio_read_bit(PIN_MAP[encoderpinA].gpio_device, PIN_MAP[encoderpinA].gpio_bit) ? HIGH : LOW) != A_set )
//    {
//        A_set = !A_set;
//        if ( A_set && !B_set )
//        {
//            if (millis() - encodertimer < -1)
//            {
//                encoderpos += 1;
//            }
//            else
//            {
//                encoderpos += 5;
//            }
//        }
//        encodertimer = millis();
//        last_something = millis();
//    }

//    if ( (gpio_read_bit(PIN_MAP[encoderpinB].gpio_device, PIN_MAP[encoderpinB].gpio_bit) ? HIGH : LOW) != B_set )
//    {
//        B_set = !B_set;
//        if ( B_set && !A_set )
//        {
//            if (millis() - encodertimer < -1)
//            {
//                encoderpos -= 1;
//            }
//            else
//            {
//                encoderpos -= 5;
//            }
//        }
//        encodertimer = millis();
//        last_something = millis();
//    }

//    Encoder::asleep();
}

void Encoder::asleep()
{
    pulsed = digitalRead(m_pulse);

    if (pulsed != pulsed_before) {
        last_something = millis();
    }

    pulsed_before = pulsed;

//    if (auto_lock) {
//        if (millis() - last_something > time_lock) {
//            analogWrite(SCREENBACKLIGHT, 0);
//        }
//        else {
//            analogWrite(SCREENBACKLIGHT, backlight_intensity);
//        }
//    }
}
