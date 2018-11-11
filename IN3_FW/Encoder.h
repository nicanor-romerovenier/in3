#ifndef ENCODER_H
#define ENCODER_H

#include <memory>
#include <stdint.h>

#include <HardwareTimer.h>


class Encoder
{
public:
    Encoder();

private:
    void initializeEncoder();
    static void readEncoders();
    static void asleep();

    // TODO: Change to stdint types
    // TODO: Change HardwareTimer to unique_ptr
    // TODO: Change variable names
    // TODO: readEncoder -> Detect encoder and call its own functions
    // TODO: Get rid of static stuff

    static volatile int encodertimer;
    int encstate;
    int encflag;
    static bool A_set;
    static bool B_set;
    static int16_t encoderpos;
    static int encoderpinA;
    static int encoderpinB;
    unsigned int lastEncoderPos;
    static long last_something;
    static bool pulsed;
    static bool pulsed_before;
    static bool auto_lock;

    static const uint8_t m_pulse = 14;

    std::unique_ptr<HardwareTimer> m_timer;

    static const int ENCODER_RATE;

};

#endif // ENCODER_H
