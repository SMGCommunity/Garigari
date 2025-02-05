#pragma once

#include <revolution.h>

class ActorLightCtrl {
public:
    void setLightType(s32);

    void copy(const ActorLightCtrl *);
};
