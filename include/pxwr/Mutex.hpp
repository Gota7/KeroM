#pragma once

#include "pxp/Mutex.hpp"

// For thread locking.
class pxwrMutex
{
    pxpMutex* mutex = nullptr;

public:

    // Destroy the mutex.
    ~pxwrMutex();

    // Initialize the mutex. Returns if successful.
    bool init();

    // Lock a mutex.
    void lock();

    // Try to lock a mutex. Returns if successful.
    bool trylock();

    // Unlock a mutex.
    void unlock();

};