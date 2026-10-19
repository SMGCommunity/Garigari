#include "Game/LiveActor/LiveActor.hpp"
#include "Game/LiveActor/HitSensor.hpp"
#include "Game/LiveActor/HitSensorKeeper.hpp"
#include "Game/LiveActor/LiveActorFlag.hpp"
#include "Game/LiveActor/LiveActorGroup.hpp"
#include "Game/LiveActor/Spine.hpp"
#include "Game/Map/StageSwitch.hpp"
#include "Game/NameObj/NameObj.hpp"

#include <revolution/types.h>

// sdata stuff??
f32 lbl_807DC480;
f32 lbl_807DC484;
f32 lbl_807DC488;

// classes and functions from God knows where
class ClippingDirector {
public:
    void registerActor(LiveActor*);
};
namespace MR {
    LiveActorGroup* getAllLiveActorGroup();
    ClippingDirector* getClippingDirector();
}

// NON_MATCHING
// decomp.me: https://decomp.me/scratch/6d1My
LiveActor::LiveActor(const char* pName) : NameObj(pName) {
    f32 f2 = lbl_807DC484;
    f32 f1 = lbl_807DC480;
    f32 f0 = lbl_807DC488;

    mPosition.x = f2;
    mPosition.y = f2;
    mPosition.z = f2;
    mRotation.x = f2;
    mRotation.y = f2;
    mRotation.z = f2;
    mScale.x = f1;
    mScale.y = f1;
    mScale.z = f1;
    mVelocity.x = f2;
    mVelocity.y = f2;
    mVelocity.z = f2;
    mGravity.x = f2;
    mGravity.y = f0;
    mGravity.z = f2;
    mActionKeeper = nullptr;
    mModelManager = nullptr;
    mSpine = nullptr;
    mSensorKeeper = nullptr;
    mBinder = nullptr;
    mRailRider = nullptr;
    mEffectKeeper = nullptr;
    mSoundHolder = nullptr;
    LiveActorFlag r3;
    mShadowList = nullptr;
    mCollisionParts = nullptr;
    mSwitchCtrl = nullptr;
    mPointerTarget = nullptr;
    mLightCtrl = nullptr;

    MR::getAllLiveActorGroup()->registerActor(this);
    MR::getClippingDirector()->registerActor(this);
}

void LiveActor::init(const JMapInfoIter&) {
}

void LiveActor::appear() {
    makeActorAppeared();
}

// LiveActor::makeActorAppeared
// LiveActor::kill
// LiveActor::makeActorDead
// LiveActor::movement
// LiveActor::calcAnim
// LiveActor::calcAnmMtx
// J3DModel::setBaseScale
// LiveActor::calcViewAndEntry
// LiveActor::receiveMessage
// LiveActor::calcAndSetBaseMtx
// LiveActor::getTakingMtx

void LiveActor::setNerve(const Nerve* pNerve) {
    mSpine->setNerve(pNerve);
}

bool LiveActor::isNerve(const Nerve* pNerve) const {
    return mSpine->getCurrentNerve() == pNerve;
}

s32 LiveActor::getNerveStep() const {
    return mSpine->mStep;
}

HitSensor* LiveActor::getSensor(const char* pSensorName) const {
    if (mSensorKeeper != nullptr) {
        return mSensorKeeper->getSensor(pSensorName);
    }

    return nullptr;
}

// LiveActor::getBaseMtx
// LiveActor::startClipped
// LiveActor::endClipped
// LiveActor::initModelManagerWithAnm

void LiveActor::initNerve(const Nerve* pNerve, s32 numStates) {
    mSpine = new Spine(this, pNerve, numStates);
}

void LiveActor::initHitSensor(s32 numSensors) {
    mSensorKeeper = new HitSensorKeeper(numSensors);
}

// LiveActor::initBinder
// LiveActor::initRailRider
// LiveActor::initEffectKeeper
// LiveActor::initSound
// LiveActor::initShadowControllerList
// LiveActor::initActorCollisionParts

void LiveActor::initStageSwitch(const JMapInfoIter& rIter) {
    mSwitchCtrl = MR::createStageSwitchCtrl(this, rIter);
}

// LiveActor::initActorStarPointerTarget
// LiveActor::initActorLightCtrl

void LiveActor::attackSensor(HitSensor*, HitSensor*) {
}

// LiveActor::updateBinder
