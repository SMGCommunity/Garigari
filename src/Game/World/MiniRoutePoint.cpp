#include "Game/World/MiniRoutePoint.hpp"
#include "Game/LiveActor/LiveActor.hpp"
#include "Game/Util/ActorAnimUtil.hpp"
#include "Game/Util/ActorInitUtil.hpp"
#include "Game/Util/DemoUtil.hpp"
#include "Game/Util/LiveActorUtil.hpp"
#include <decomp.h>

EXTERN_UNKNOWN_FUNC(80008450, const LiveActor*, const char*, s32, s32, s32);
EXTERN_UNKNOWN_FUNC(804E8C40, const LiveActor*);
EXTERN_UNKNOWN_FUNC(804E8C50, const LiveActor*, f32, f32);
EXTERN_UNKNOWN_FUNC(804E8C80, const LiveActor*, f32, f32);

namespace {
    static const f32 cShadowDropDistance = -700.0f;
}

MiniRoutePoint::MiniRoutePoint() : LiveActor("中継点"), _90(-1), _98(), _99() {
}

void MiniRoutePoint::init(const JMapInfoIter& rIter) {
    MR::initActor(this, "MiniRoutePoint", false);
    MR::setClippingFarMax(this);
    MR::registerDemoSimpleCastAll(this);

    mShadowActor = new LiveActor("中継点影");
    MR::initActor(mShadowActor, "MiniRoutePointShadow", false);
    MR::setClippingFarMax(mShadowActor);

    MR::invalidateClipping(this);
    MR::invalidateClipping(mShadowActor);
    makeActorDead();
}

void MiniRoutePoint::makeActorAppeared() {
    MR::setScale(this, _98 ? 0.4f : 1.0f);
    mScale.y = 1.0f;

    MR::setScale(mShadowActor, mScale);
    MR::setRotation(mShadowActor, mRotation);

    LiveActor::makeActorAppeared();
    mShadowActor->makeActorAppeared();
}

void MiniRoutePoint::makeActorDead() {
    LiveActor::makeActorDead();
    mShadowActor->makeActorDead();
}

bool MiniRoutePoint::isPointing() const {
    if (MR::isDead(this)) {
        return false;
    }

    return fn_804E8C40(this);
}

bool MiniRoutePoint::fn_804E55D0() {
    if (MR::isDead(this)) {
        return false;
    }

    fn_804E8C50(this, 0.1f, _98 ? 0.7f : 1.2f);
    mScale.y = 1.0f;
    return true;
}

void MiniRoutePoint::setPosition(const TVec3f& rPosition) {
    MR::setPosition(this, rPosition);
    MR::setPosition(mShadowActor, TVec3f(rPosition.x, rPosition.y + cShadowDropDistance, rPosition.z));
}

void MiniRoutePoint::setOpen(bool open) {
    if (open) {
        MR::startAction(this, "Open");

        if (_99) {
            MR::startBrk(this, "TicoBuild");
        } else {
            MR::startBrk(this, "Normal");
        }
    } else {
        MR::startAction(this, "Close");
    }
}

bool MiniRoutePoint::isOpen() const {
    return MR::isAnyAnimPlaying(this, "Open");
}

bool MiniRoutePoint::startSoundRoadExtend() {
    fn_80008450(this, "RoadExtend", -1, -1, -1);
    return true;
}

bool MiniRoutePoint::startSoundPointOn() {
    fn_80008450(this, "PointOn", -1, -1, -1);
    return true;
}

bool MiniRoutePoint::startSoundPointOff() {
    fn_80008450(this, "PointOff", -1, -1, -1);
    return true;
}

void MiniRoutePoint::control() {
    fn_804E8C80(this, 0.5f, _98 ? 0.4f : 1.0f);
    mScale.y = 1.0f;
    MR::setScale(mShadowActor, mScale);
    MR::setRotation(mShadowActor, mRotation);
}
