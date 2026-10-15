#ifndef METROTRK_PORTABLE_MUTEX_TRK_H
#define METROTRK_PORTABLE_MUTEX_TRK_H

#include "trk.h"

static inline DSError TRKReleaseMutex(void* mutex) {
    return DS_NoError;
}

static inline DSError TRKAcquireMutex(void* mutex) {
    return DS_NoError;
}

static inline DSError TRKInitializeMutex(void* mutex) {
    return DS_NoError;
}

#endif /* METROTRK_PORTABLE_MUTEX_TRK_H */
