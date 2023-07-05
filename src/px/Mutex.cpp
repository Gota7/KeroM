#include "px/Mutex.hpp"

pxMutex::~pxMutex()
{
    if (mutex)
    {
        delete mutex;
        mutex = nullptr;
    }
}

bool pxMutex::init()
{
    if (mutex) return false;
    mutex = new pxwrMutex();
    return mutex->init();
}

void pxMutex::lock()
{
    if (mutex)
        mutex->lock();
}

bool pxMutex::trylock()
{
    if (mutex)
        return mutex->trylock();
    else
        return false;
}

void pxMutex::unlock()
{
    if (mutex) mutex->unlock();
}