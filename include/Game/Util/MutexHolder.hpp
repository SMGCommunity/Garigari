#pragma once

#include <revolution/os/OSMutex.h>

class JKRHeap;

namespace MR {
    template < int T >
    class MutexHolder {
    public:
        static OSMutex sMutex;
    };

    template < int T >
    OSMutex MutexHolder< T >::sMutex;
};  // namespace MR
