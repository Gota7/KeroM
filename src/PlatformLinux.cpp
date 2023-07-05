#ifdef __linux

#include "Platform.hpp"
#include <pthread.h>
#include <unistd.h>

namespace KeroPlatform
{

    int ChangeDir(char* path)
    {
        return chdir(path);
    }

    int MutexInit(KERO_MUTEX* mutex)
    {
        return pthread_mutex_init(mutex, nullptr);
    }

    int MutexDestroy(KERO_MUTEX* mutex)
    {
        return pthread_mutex_destroy(mutex);
    }

    int MutexLock(KERO_MUTEX* mutex)
    {
        return pthread_mutex_lock(mutex);
    }

    int MutexTryLock(KERO_MUTEX* mutex)
    {
        return pthread_mutex_trylock(mutex);
    }

    int MutexUnlock(KERO_MUTEX* mutex)
    {
        return pthread_mutex_unlock(mutex);
    }

}

#endif