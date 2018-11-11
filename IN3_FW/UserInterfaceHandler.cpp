#include "UserInterfaceHandler.h"
#include "Locale.h"


UserInterfaceHandler::UserInterfaceHandler()
{
    m_ui_view = std::unique_ptr<UserInterfaceView>(new UserInterfaceView());

    // TOERASE
    m_ui_view->drawSplashScreen(SPLASH_SCREEN_MESSAGE);
}
