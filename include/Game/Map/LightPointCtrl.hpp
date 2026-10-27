#pragma once

#include "Game/Util/Color.hpp"

#include <JSystem/JGeometry/TVec.hpp>
#include <revolution/types.h>

class LiveActor;

class PointLightInfo {
public:
    bool operator=(const PointLightInfo&);
};

class LightPointCtrl {
public:
    LightPointCtrl();

    void loadPointLight();
    void update();
    void requestPointLight(const LiveActor*, TVec3f, Color8, f32, s32);
    void updatePointLight();
    void clearPointLight(PointLightInfo*);
    void blendPointLight(PointLightInfo*, const PointLightInfo&, const PointLightInfo&, f32);
    void tryBlendStart();
    bool isUpdateCandidateActor(const LiveActor*) const;
};

class ZoneLightID {
public:
    ZoneLightID();

    /* 0x0 */ u32 _0;
    /* 0x4 */ u32 _4;
};
