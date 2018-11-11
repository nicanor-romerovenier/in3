#ifndef USERINTERFACEHANDLER_H
#define USERINTERFACEHANDLER_H

#include <memory>

#include "InputManager.h"
#include "UserInterfaceView.h"


class UserInterfaceHandler
{
public:
    UserInterfaceHandler();

private:
    std::unique_ptr<UserInterfaceView> m_ui_view;
    std::unique_ptr<InputManager> m_input_handler;
};

#endif // USERINTERFACEHANDLER_H
