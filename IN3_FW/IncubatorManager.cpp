#include "IncubatorManager.h"


IncubatorManager::IncubatorManager()
{
    m_storage_manager = std::unique_ptr<StorageManager>(new StorageManager());
}
