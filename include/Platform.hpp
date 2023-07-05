#pragma once

// Mutex type, make sure to re-define!
#define KERO_MUTEX void*

// Include platform-specific headers to redefine above types.
#include "PlatformLinux.hpp"

// For platform-specific functions.
namespace KeroPlatform
{

    // Change working directory to a given path.
    int ChangeDir(char* path);

    // Initialize a mutex. Returns nonzero if error.
    int MutexInit(KERO_MUTEX* mutex);

    // Destroy a mutex. Returns nonzero if error.
    int MutexDestroy(KERO_MUTEX* mutex);

    // Lock a mutex. Returns nonzero if error.
    int MutexLock(KERO_MUTEX* mutex);

    // Try to lock a mutex. Returns nonzero if error.
    int MutexTryLock(KERO_MUTEX* mutex);

    // Unlock a mutex. Returns nonzero if error.
    int MutexUnlock(KERO_MUTEX* mutex);

}