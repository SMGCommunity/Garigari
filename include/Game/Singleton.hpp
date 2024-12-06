#pragma once

#include <revolution.h>

template<typename T>
class SingletonHolder {
public:
    static T* get() {
        return sInstance;
    }

    static void set(T *p) {
        sInstance = p;
    }

    static bool exists() {
        return sInstance != nullptr;
    }

    static T* sInstance;
};
