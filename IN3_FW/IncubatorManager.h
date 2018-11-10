#ifndef INCUBATORMANAGER_H
#define INCUBATORMANAGER_H

#include <memory>

#include "StorageHandler.h"
#include "UserInterfaceHandler.h"


class IncubatorManager
{
public:
    IncubatorManager();

private:
    std::unique_ptr<StorageHandler> m_storage_handler;
    std::unique_ptr<UserInterfaceHandler> m_user_interface_handler;
};

#endif // INCUBATORMANAGER_H
