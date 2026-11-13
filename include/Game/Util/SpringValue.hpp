#pragma once

#include <revolution.h>

class SpringValue {
public:
    SpringValue();
    SpringValue(f32, f32, f32, f32, f32);

    void setParam(f32, f32, f32, f32, f32);
    f32 update();
    void clampSpring(f32 maxValue);

    // I refuse to believe this isn't header defined, as it's in two different TUs between SMG1 and SMG2
    void reset() {
        mSpringValue = mRestValue;
        mVelocity = 0.0f;
    }

    /* 0x00 */ f32 mRestValue;
    /* 0x04 */ f32 mSpringValue;
    /* 0x08 */ f32 mAccelFactor;
    /* 0x0C */ f32 mDamping;
    /* 0x10 */ f32 mVelocity;
};
