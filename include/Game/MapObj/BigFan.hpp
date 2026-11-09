#pragma once

#include "Game/LiveActor/LiveActor.hpp"
#include "Game/LiveActor/ModelObj.hpp"

class BigFan : public LiveActor {
public:
    BigFan(const char* pName);
    void init(const JMapInfoIter&);
    void initWindModel();
    void calcWindInfo(TVec3f*, const TVec3f&);
    void control();
    void start();

    void exeStart();
    void exeWait();
    void exeStop();

    inline bool isStartOrWait();

    /* 0x90 */ ModelObj* mWindModel;
    /* 0x94 */ TVec3f mClippingCenter;
    /* 0xA0 */ f32 mWindLength;
    /* 0xA4 */ f32 mWindSpeed;
    /* 0xA8 */ bool mIsTeresaGalaxy;
};

namespace BigFanFunction {
    void createBigFanHolder();
    void registerBigFan(BigFan* pBigFan);
}  // namespace BigFanFunction
