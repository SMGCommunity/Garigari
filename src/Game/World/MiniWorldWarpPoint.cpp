#include "Game/World/MiniWorldWarpPoint.hpp"
#include "Game/LiveActor/LiveActor.hpp"
#include "Game/Util/ActionSoundUtil.hpp"
#include "Game/Util/ActorAnimUtil.hpp"
#include "Game/Util/ActorInitUtil.hpp"
#include "Game/Util/EffectUtil.hpp"
#include "Game/Util/LiveActorUtil.hpp"
#include <decomp.h>

EXTERN_UNKNOWN_FUNC(bool, 804F26A0, WorldMapObjHolder*, s32)

MiniWorldWarpPoint::MiniWorldWarpPoint(WorldMapObjHolder* pObjHolder, s32 pointIndex, bool isWorldNext)
    : LiveActor("ワールドワープポイント"), mObjHolder(pObjHolder), mPointIndex(pointIndex), mIsWorldNext(isWorldNext) {
}

void MiniWorldWarpPoint::init(const JMapInfoIter& rIter) {
    MR::initActor(this, "MiniWorldWarpPoint", "WMap", false);
    makeActorAppeared();
}

void MiniWorldWarpPoint::makeActorAppeared() {
    if (!fn_804F26A0(mObjHolder, mPointIndex)) {
        return;
    }

    LiveActor::makeActorAppeared();
    MR::startAction(this, mIsWorldNext ? "Next" : "Previous");
}

void MiniWorldWarpPoint::makeActorDead() {
    LiveActor::makeActorDead();
    MR::forceDeleteEffectAll(this);
}

bool MiniWorldWarpPoint::tryStartSound(s32 distance) {
    if (MR::isDead(this)) {
        return false;
    }

    if (distance >= 2) {
        return false;
    }

    MR::startActionSound(this, "MarioShipBesideThis");
    return true;
}

void MiniWorldWarpPoint::setAllEffectDrawOrder(s32 drawOrder) {
    MR::setAllEffectDrawOrder(this, drawOrder);
}
