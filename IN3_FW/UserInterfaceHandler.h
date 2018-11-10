#ifndef USERINTERFACEHANDLER_H
#define USERINTERFACEHANDLER_H

#include <memory>

#include "UserInterfaceView.h"


class UserInterfaceHandler
{
public:
    UserInterfaceHandler();

private:
    std::unique_ptr<UserInterfaceView> m_ui_view;
};

#endif // USERINTERFACEHANDLER_H
