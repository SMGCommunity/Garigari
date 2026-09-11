#pragma once

#include <revolution.h>

class LiveActor;

class ActorLightCtrl {
public:
    ActorLightCtrl(const LiveActor*);
    void setLightType(s32);

    void copy(const ActorLightCtrl *);

    u8 _0[0x58]; // Target allocation size; fields remain unrecovered.
};
