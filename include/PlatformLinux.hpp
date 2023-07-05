#pragma once

#ifdef __linux

#include <pthread.h>

#undef KERO_MUTEX
#define KERO_MUTEX pthread_mutex_t

#endif