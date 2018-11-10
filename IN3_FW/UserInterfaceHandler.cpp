#include "UserInterfaceHandler.h"


UserInterfaceHandler::UserInterfaceHandler()
{
    m_ui_view = std::unique_ptr<UserInterfaceView>(new UserInterfaceView());

    // TOERASE
    m_ui_view->drawSplashScreen("Hello world!");
}
