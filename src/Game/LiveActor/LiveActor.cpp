#include "Game/LiveActor/LiveActor.hpp"
#include "Game/LiveActor/HitSensor.hpp"
#include "Game/LiveActor/HitSensorKeeper.hpp"
#include "Game/LiveActor/LiveActorFlag.hpp"
#include "Game/LiveActor/LiveActorGroup.hpp"
#include "Game/LiveActor/Spine.hpp"
#include "Game/Map/StageSwitch.hpp"
#include "Game/NameObj/NameObj.hpp"
#include "Game/Util/ActorSensorUtil.hpp"
#include "Game/Util/LiveActorUtil.hpp"

#include <revolution/types.h>

// classes and functions from God knows where
class ClippingDirector {
public:
    void registerActor(LiveActor*);
};
namespace MR {
    // Used in LiveActor::LiveActor(const char*)
    LiveActorGroup* getAllLiveActorGroup();
    ClippingDirector* getClippingDirector();

    // Used in LiveActor::makeActorAppeared()
    void addToClippingTarget(LiveActor *pActor);
    void connectToDrawTemporarily(NameObj *pObj);
    void connectToSceneTemporarily(NameObj *pObj);
    void resetPosition(LiveActor *pActor);

    // Used in LiveActor::kill()
    void onSwitchDead(LiveActor* pActor);

    // Used in LiveActor::makeActorDead()
    void removeFromClippingTarget(LiveActor *pActor);
    void disconnectToDrawTemporarily(NameObj *pObj);
    void disconnectToSceneTemporarily(NameObj *pObj);
}  // namespace MR

LiveActor::LiveActor(const char* pName)
    : NameObj(pName), mPosition(0.0f, 0.0f, 0.0f), mRotation(0.0f, 0.0f, 0.0f), mScale(1.0f, 1.0f, 1.0f), mVelocity(0.0f, 0.0f, 0.0f),
      mGravity(0.0f, -1.0f, 0.0f), mActionKeeper(), mModelManager(), mSpine(), mSensorKeeper(), mBinder(), mRailRider(), mEffectKeeper(),
      mSoundHolder(), mShadowList(), mCollisionParts(), mSwitchCtrl(), mPointerTarget(), mLightCtrl() {
    MR::getAllLiveActorGroup()->registerActor(this);
    MR::getClippingDirector()->registerActor(this);
}

void LiveActor::init(const JMapInfoIter&) {
}

void LiveActor::appear() {
    makeActorAppeared();
}

void LiveActor::makeActorAppeared() {
    if (mSensorKeeper != nullptr) {
        mSensorKeeper->validateBySystem();
    }

    mFlags.mIsDead = false;

    if (MR::isClipped(this)) {
        endClipped();
    }

    if (mCollisionParts != nullptr) {
        MR::validateCollisionParts(this);
    }

    MR::resetPosition(this);

    if (mLightCtrl != nullptr) {
        mLightCtrl->reset();
    }

    MR::tryUpdateHitSensorsAll(this);
    MR::addToClippingTarget(this);
    MR::connectToSceneTemporarily(this);
    if(!MR::isNoEntryDrawBuffer(this)) {
        MR::connectToDrawTemporarily(this);
    }
}

void LiveActor::kill() {
    makeActorDead();
    if (mSwitchCtrl != nullptr && mSwitchCtrl->isValidSwitchDead() && mSwitchCtrl->_10) {
        MR::onSwitchDead(this);
    }
}

void LiveActor::makeActorDead() {
    mVelocity.z = 0.0f;
    mVelocity.y = 0.0f;
    mVelocity.x = 0.0f;
    MR::clearHitSensors(this);

    if (mSensorKeeper != nullptr) {
        mSensorKeeper->invalidateBySystem();
    }

    if (mBinder != nullptr) {
        mBinder->clear();
    }

    if (mEffectKeeper != nullptr) {
        mEffectKeeper->clear();
    }

    if (mCollisionParts != nullptr) {
        MR::invalidateCollisionParts(this);
    }

    mFlags.mIsDead = true;

    MR::removeFromClippingTarget(this);
    MR::disconnectToSceneTemporarily(this);
    MR::disconnectToDrawTemporarily(this);
}

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
