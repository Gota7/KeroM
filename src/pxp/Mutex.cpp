#include "pxp/Mutex.hpp"

#include "Platform.hpp"

bool pxpMutex::init()
{
    if (KeroPlatform::MutexInit(&mutex)) return false;
    initialized = true;
    return true;
}

pxpMutex::~pxpMutex()
{
    initialized = false;
    KeroPlatform::MutexDestroy(&mutex);
}

bool pxpMutex::lock()
{
    if (!initialized) return false;
    return !KeroPlatform::MutexLock(&mutex);
}

bool pxpMutex::trylock()
{
    if (!initialized) return false;
    return !KeroPlatform::MutexTryLock(&mutex);
}

bool pxpMutex::unlock()
{
    if (!initialized) return false;
    return !KeroPlatform::MutexUnlock(&mutex);
}