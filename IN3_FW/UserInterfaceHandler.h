#ifndef USERINTERFACEHANDLER_H
#define USERINTERFACEHANDLER_H

#include <memory>

#include "InputHandler.h"
#include "UserInterfaceView.h"


class UserInterfaceHandler
{
public:
    UserInterfaceHandler();

private:
    std::unique_ptr<UserInterfaceView> m_ui_view;
    std::unique_ptr<InputHandler> m_input_handler;
};

#endif // USERINTERFACEHANDLER_H
