#pragma once

#include "Game/LiveActor/LiveActor.hpp"

class GrandGalaxyMapIcon : public LiveActor {
public:
    GrandGalaxyMapIcon(const char*, const char*);

    virtual void control();

    void fn_804E0020();  // Something effect
    void setRotation(const TVec3f&);
    void setScale(f32);

    /* 0x90 */ f32 mOffsetX;
    /* 0x94 */ f32 mOffsetY;
    /* 0x98 */ f32 mSize;
    /* 0x9C */ f32 mBoundingRadius;
    /* 0xA0 */ bool mCanRotate;
};
