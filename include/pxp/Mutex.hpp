#pragma once

#include "Platform.hpp"

// For thread locking.
class pxpMutex
{
    KERO_MUTEX mutex;
    bool initialized = false;

public:

    // Initialize the mutex. Returns if successful.
    bool init();

    // Destroy the mutex.
    ~pxpMutex();

    // Lock a mutex. Returns if successful.
    bool lock();

    // Try to lock a mutex. Returns if successful.
    bool trylock();

    // Unlock a mutex. Returns if successful.
    bool unlock();

};