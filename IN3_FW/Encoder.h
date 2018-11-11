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

    // TODO: Change to stdint types
    // TODO: Change HardwareTimer to unique_ptr
    // TODO: Change variable names
    // TODO: Change static void readEncoder to void readEncoder

    volatile int encodertimer;
    int encstate;
    int encflag;
    bool A_set;
    bool B_set;
    int16_t encoderpos;
    int encoderpinA;
    int encoderpinB;
    unsigned int lastEncoderPos;

    std::unique_ptr<HardwareTimer> m_timer;

    static const int ENCODER_RATE;

};

#endif // ENCODER_H
