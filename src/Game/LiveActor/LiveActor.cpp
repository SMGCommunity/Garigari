#include "Game/LiveActor/LiveActor.hpp"
#include "Game/LiveActor/ActorActionKeeper.hpp"
#include "Game/LiveActor/ActorLightCtrl.hpp"
#include "Game/LiveActor/AllLiveActorGroup.hpp"
#include "Game/LiveActor/Binder.hpp"
#include "Game/LiveActor/ClippingDirector.hpp"
#include "Game/LiveActor/EffectKeeper.hpp"
#include "Game/LiveActor/HitSensor.hpp"
#include "Game/LiveActor/HitSensorKeeper.hpp"
#include "Game/LiveActor/LiveActorFlag.hpp"
#include "Game/LiveActor/LiveActorGroup.hpp"
#include "Game/LiveActor/ModelManager.hpp"
#include "Game/LiveActor/ShadowController.hpp"
#include "Game/LiveActor/Spine.hpp"
#include "Game/Map/StageSwitch.hpp"
#include "Game/NameObj/NameObj.hpp"
#include "Game/NameObj/NameObjExecuteHolder.hpp"
#include "Game/Util/ActorMovementUtil.hpp"
#include "Game/Util/ActorSensorUtil.hpp"
#include "Game/Util/ActorSwitchUtil.hpp"
#include "Game/Util/LiveActorUtil.hpp"
#include "Game/Util/ModelUtil.hpp"
#include "Game/Util/SoundUtil.hpp"

#include <JSystem/J3DGraphAnimator/J3DModel.hpp>
#include <revolution/types.h>

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
    if (!MR::isNoEntryDrawBuffer(this)) {
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

void LiveActor::movement() {
    if (mModelManager != nullptr && !mFlags.mIsNotReleasedAnimFrame) {
        mModelManager->update();

        if (mActionKeeper != nullptr) {
            mActionKeeper->updateAnimKeeper();
        }
    }

    if (MR::isCalcGravity(this)) {
        MR::calcGravity(this);
    }

    if (mSensorKeeper != nullptr) {
        mSensorKeeper->doObjCol();
    }

    if (mFlags.mIsDead)
        return;

    if (mSpine != nullptr) {
        mSpine->update();
    }

    if (mFlags.mIsDead)
        return;

    control();

    if (mFlags.mIsDead)
        return;

    updateBinder();

    if (mActionKeeper != nullptr) {
        mActionKeeper->update();
    }

    if (mEffectKeeper != nullptr) {
        mEffectKeeper->update();
    }

    if (mLightCtrl != nullptr) {
        MR::updateLightCtrl(this);
    }

    MR::tryUpdateHitSensorsAll(this);
    MR::actorSoundMovement(this);
    MR::requestCalcActorShadow(this);
}

void LiveActor::calcAnim() {
    if (!mFlags.mIsOnCalcAnim) {
        calcAnmMtx();

        if (mCollisionParts != nullptr) {
            MR::setCollisionMtx(this);
        }
    }
}

// NON_MATCHING
// decomp.me: https://decomp.me/scratch/YJeEP
// J3DModel::setBaseScale() is being inlined, even though it shouldn't be. Probably has something to do with the function being overridden in this
// file.
void LiveActor::calcAnmMtx() {
    if (mModelManager != nullptr) {
        MR::getJ3DModel(this)->setBaseScale(mScale);

        calcAndSetBaseMtx();

        mModelManager->calcAnim();
    }
}

// void J3DModel::setBaseScale(const Vec& rScale) override {
//     mBaseScale.x = rScale.x;
//     mBaseScale.y = rScale.y;
//     mBaseScale.z = rScale.z;
// }

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
