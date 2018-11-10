#include "IncubatorManager.h"


IncubatorManager::IncubatorManager()
{
    m_storage_handler = std::unique_ptr<StorageHandler>(new StorageHandler());
}
