#pragma once

#include <revolution.h>

class SpringValue {
public:
    SpringValue();
    SpringValue(f32, f32, f32, f32, f32);

    void setParam(f32, f32, f32, f32, f32);
    f32 update();

    // I refuse to believe this isn't header defined, as it's in two different TUs between SMG1 and SMG2
    void reset() {
        mSpringValue = mRestValue;
        mVelocity = 0.0f;
    }

    f32 mRestValue;
    f32 mSpringValue;
    f32 mAccelFactor;
    f32 mDamping;
    f32 mVelocity;
};
