#pragma once

#include "Game/System/NerveExecutor.hpp"
#include <JSystem/JGeometry.hpp>

class LiveActor;

class AnimScaleParam {
public:
    AnimScaleParam();

    /* 0x00 */ f32 _0;
    /* 0x04 */ f32 _4;
    /* 0x08 */ f32 _8;
    /* 0x0C */ f32 _C;
    /* 0x10 */ f32 _10;
    /* 0x14 */ f32 _14;
    /* 0x18 */ f32 _18;
    /* 0x1C */ f32 _1C;
    /* 0x20 */ f32 _20;
    /* 0x24 */ f32 _24;
    /* 0x28 */ f32 _28;
    /* 0x2C */ u32 _2C;
    /* 0x30 */ f32 _30;
};

class AnimScaleController : public NerveExecutor {
public:
    AnimScaleController(AnimScaleParam*);

    void update();
    void updateScale(f32, f32);
    void startCrush();
    void startAnim();
    void startAndAddScaleVelocityY(f32);

    void setParamTight();
    void startHitReaction();
    void startDpdHitVibration();
    bool isHitReaction(s32) const;

    void stopAndReset();
    void resetScale();

    bool tryStop();

    void exeAnim();
    inline void exeStop();
    void exeDpdVibration();
    void exeHitReaction();
    void exeCrush();

    /* 0x08 */ AnimScaleParam* _8;
    /* 0x0C */ TVec3f _C;
    /* 0x18 */ f32 _18;
};

// TODO: Is this here or in a standard util header? The function itself seems to be situated in the AnimScaleController TU
namespace MR {
    void updateBaseScale(LiveActor* pActor, AnimScaleController* pScaleController);
} // namespace MR
