#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <memory>

#include "Encoder.h"


class InputManager
{
public:
    InputManager();

private:
    std::unique_ptr<Encoder> m_encoder;
};

#endif // INPUTMANAGER_H
