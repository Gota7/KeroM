#pragma once

#include "pxwr/Mutex.hpp"

// For thread locking.
class pxMutex
{
    pxwrMutex* mutex = nullptr;

public:

    // Destroy the mutex.
    ~pxMutex();

    // Initialize the mutex. Returns if successful.
    bool init();

    // Lock a mutex.
    void lock();

    // Try to lock a mutex. Returns if successful.
    bool trylock();

    // Unlock a mutex.
    void unlock();

};