#pragma once

#include <revolution.h>
class Binder;
class LiveActor;
class ResourceHolder;
class EffectKeeper {
public:
    void clear();
    EffectKeeper(const char*, ResourceHolder*, int, const char*);
    void init(LiveActor*);
    void enableSort();
    void setBinder(const Binder*);
    void playEmitterOffClipped();
    u8 _0[0x34]; // Target allocation size; fields remain unrecovered.
};
