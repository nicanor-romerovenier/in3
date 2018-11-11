#include "InputManager.h"


InputManager::InputManager()
{
    m_encoder = std::unique_ptr<Encoder>(new Encoder());
}
