#include "pxwr/Mutex.hpp"

pxwrMutex::~pxwrMutex()
{
    if (mutex)
    {
        delete mutex;
        mutex = nullptr;
    }
}

bool pxwrMutex::init()
{
    if (mutex) return false;
    mutex = new pxpMutex();
    return mutex->init();
}

void pxwrMutex::lock()
{
    if (mutex)
        mutex->lock();
}

bool pxwrMutex::trylock()
{
    if (mutex)
        return mutex->trylock();
    else
        return false;
}

void pxwrMutex::unlock()
{
    if (mutex) mutex->unlock();
}