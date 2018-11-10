#ifndef INCUBATORMANAGER_H
#define INCUBATORMANAGER_H

#include <memory>

#include "StorageManager.h"


class IncubatorManager
{
public:
    IncubatorManager();

private:
    std::unique_ptr<StorageManager> m_storage_manager;
};

#endif // INCUBATORMANAGER_H
