#include "Game/LiveActor/LiveActor.hpp"
#include "Game/LiveActor/ActorActionKeeper.hpp"
#include "Game/LiveActor/ActorLightCtrl.hpp"
#include "Game/LiveActor/ActorSoundHolder.hpp"
#include "Game/LiveActor/AllLiveActorGroup.hpp"
#include "Game/LiveActor/Binder.hpp"
#include "Game/LiveActor/ClippingDirector.hpp"
#include "Game/LiveActor/EffectKeeper.hpp"
#include "Game/LiveActor/HitSensor.hpp"
#include "Game/LiveActor/HitSensorKeeper.hpp"
#include "Game/LiveActor/LiveActorFlag.hpp"
#include "Game/LiveActor/LiveActorGroup.hpp"
#include "Game/LiveActor/ModelManager.hpp"
#include "Game/LiveActor/RailRider.hpp"
#include "Game/LiveActor/ShadowController.hpp"
#include "Game/LiveActor/Spine.hpp"
#include "Game/Map/StageSwitch.hpp"
#include "Game/NameObj/NameObj.hpp"
#include "Game/NameObj/NameObjExecuteHolder.hpp"
#include "Game/Screen/StarPointerTarget.hpp"
#include "Game/Util/ActorMovementUtil.hpp"
#include "Game/Util/ActorSensorUtil.hpp"
#include "Game/Util/ActorSwitchUtil.hpp"
#include "Game/Util/CameraUtil.hpp"
#include "Game/Util/JMapInfo.hpp"
#include "Game/Util/LiveActorUtil.hpp"
#include "Game/Util/ModelUtil.hpp"
#include "Game/Util/SoundUtil.hpp"
#include "JSystem/JGeometry/TMatrix.hpp"

#include <JSystem/J3DGraphAnimator/J3DModel.hpp>
#include <JSystem/JGeometry/TVec.hpp>
#include <revolution/mtx.h>
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

void LiveActor::calcViewAndEntry() {
    if (!mFlags.mIsNoCalcView && mModelManager != nullptr && !mFlags.mIsNoCalcView) {
        mModelManager->calcView();
    }
}

// NON_MATCHING
// decomp.me: https://decomp.me/scratch/rl7mO
// compiler optimizing for isMsgEnemyAttack comparison
bool LiveActor::receiveMessage(u32 msg, HitSensor* pSender, HitSensor* pReceiver) {
    if (msg == ACTMES_PUSH) {
        return receiveMsgPush(pSender, pReceiver);
    }

    bool isMsgPlayerAttack = msg != ACTMES_PLAYER_ATTACK_START && msg < ACTMES_PLAYER_ATTACK_END;

    if (isMsgPlayerAttack) {
        return receiveMsgPlayerAttack(msg, pSender, pReceiver);
    }

    bool isMsgEnemyAttack = msg > ACTMES_ENEMY_ATTACK_START && msg < ACTMES_ENEMY_ATTACK_END;

    if (isMsgEnemyAttack) {
        return receiveMsgEnemyAttack(msg, pSender, pReceiver);
    }

    return receiveOtherMsg(msg, pSender, pReceiver);
}

void LiveActor::calcAndSetBaseMtx() {
    if (MR::getTaken(this) != nullptr) {
        MtxPtr takingMtx = MR::getTaken(this)->mHostActor->getTakingMtx();
        MR::setBaseTRMtx(this, takingMtx);
    } else {
        TPos3f mtx;

        if (mRotation.x == 0.0f && mRotation.z == 0.0f) {
            MR::makeMtxTransRotateY(mtx, this);
        } else {
            MR::makeMtxTR(mtx, this);
        }

        MR::setBaseTRMtx(this, mtx);
    }
}

MtxPtr LiveActor::getTakingMtx() const {
    return getBaseMtx();
}

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

MtxPtr LiveActor::getBaseMtx() const {
    if (MR::getJ3DModel(this) != nullptr) {
        return MR::getJ3DModel(this)->mBaseTransformMtx;
    }

    return nullptr;
}

void LiveActor::startClipped() {
    mFlags.mIsClipped = true;

    if (getSensorKeeper() != nullptr) {
        mSensorKeeper->invalidateBySystem();
    }

    if (mEffectKeeper != nullptr) {
        mEffectKeeper->stopEmitterOnClipped();
    }

    MR::disconnectToSceneTemporarily(this);

    if (!MR::isNoEntryDrawBuffer(this)) {
        MR::disconnectToDrawTemporarily(this);
    }
}

void LiveActor::endClipped() {
    mFlags.mIsClipped = false;

    if (getSensorKeeper() != nullptr) {
        mSensorKeeper->validateBySystem();
        MR::updateHitSensorsAll(this);
    }

    if (mEffectKeeper != nullptr) {
        mEffectKeeper->playEmitterOffClipped();
    }

    MR::connectToSceneTemporarily(this);
    if (!MR::isNoEntryDrawBuffer(this)) {
        MR::connectToDrawTemporarily(this);
    }
}

void LiveActor::initModelManagerWithAnm(const char* pStr1, const char* pStr2, const char* pStr3, bool param4) {
    mModelManager = new ModelManager(MR::getCameraProjectionMtx());
    mModelManager->init(pStr1, pStr2, param4);
    MR::getJ3DModel(this)->setBaseScale(mScale);
    LiveActor::calcAndSetBaseMtx();
    MR::calcJ3DModel(this);
    mActionKeeper = ActorActionKeeper::tryCreate(this, pStr3);
}

void LiveActor::initNerve(const Nerve* pNerve, s32 numStates) {
    mSpine = new Spine(this, pNerve, numStates);
}

void LiveActor::initHitSensor(s32 numSensors) {
    mSensorKeeper = new HitSensorKeeper(numSensors);
}

void LiveActor::initBinder(f32 radius, f32 offsetY, u32 planeNum) {
    mBinder = new Binder(getBaseMtx(), &mPosition, &mGravity, radius, offsetY, planeNum);
    MR::onBind(this);

    if (mEffectKeeper != nullptr) {
        mEffectKeeper->setBinder(mBinder);
    }
}

void LiveActor::initRailRider(const JMapInfoIter& rIter) {
    mRailRider = new RailRider(rIter);
}

void LiveActor::initEffectKeeper(s32 param1, const char* pName, bool param3) {
    mEffectKeeper = new EffectKeeper(getName(), MR::getModelResourceHolder(this), param1, pName);

    if (param3) {
        mEffectKeeper->enableSort();
    }

    mEffectKeeper->init(this);

    if (mBinder != nullptr) {
        mEffectKeeper->setBinder(mBinder);
    }
}

// NON_MATCHING
// decomp.me: https://decomp.me/scratch/rKHjj
// Wrong amount of bytes is being allocated for the new ActorSoundHolder.
// Will need to adjust ActorSoundHolder.hpp to fix this.
void LiveActor::initSound(s32 a1, const char* a2, const TVec3f* a3, const TVec3f& a4) {
    mSoundHolder = new ActorSoundHolder(this, a1, a2, a3, TVec3f(a4));
}

void LiveActor::initShadowControllerList(u32 size) {
    mShadowList = new ShadowControllerList(this, size);
}

// NON_MATCHING
// decomp.me: https://decomp.me/scratch/uVs99
// pMtx is not being saved to a non-volatile register.
// In the original assembly code, when MR::createCollisionPartsFromResourceHolder is called, six parameters are passed in:
// * pResourceHolder
// * pCollisionName
// * pBodySensor
// * The address 8 bytes into the stack (likely the local variable mtx)
// * pMtx
// * collisionScaleType
// However, the actual MR::createCollisionPartsFromResourceHolder() has only five parameters. In order to get the code to compile (and in order to
// match with Petari), pMtx is not passed into the function in the below C++ code. This is what causes pMtx to remain solely in a volatile register.
void LiveActor::initActorCollisionParts(const char* pCollisionName, HitSensor* pBodySensor, ResourceHolder* pResourceHolder, MtxPtr pMtx,
                                        bool autoEqualScale, bool notUsingScale) {
    MR::CollisionScaleType collisionScaleType;

    if (notUsingScale) {
        collisionScaleType = MR::CollisionScaleType_NotUsingScale;
    } else {
        collisionScaleType = MR::CollisionScaleType_Default;

        if (autoEqualScale) {
            collisionScaleType = MR::CollisionScaleType_AutoEqualScale;
        }
    }

    if (pResourceHolder != nullptr) {
        TPos3f mtx;

        if (pMtx != nullptr) {
            mtx.set(pMtx);
        } else {
            MR::makeMtxTRS(mtx.toMtxPtr(), this);
        }

        mCollisionParts = MR::createCollisionPartsFromResourceHolder(pResourceHolder, pCollisionName, pBodySensor, mtx, collisionScaleType);
    } else if (pMtx == nullptr) {
        mCollisionParts = MR::createCollisionPartsFromLiveActor(this, pCollisionName, pBodySensor, collisionScaleType);
    } else {
        mCollisionParts = MR::createCollisionPartsFromLiveActor(this, pCollisionName, pBodySensor, pMtx, collisionScaleType);
    }

    MR::invalidateCollisionParts(this);
}

void LiveActor::initStageSwitch(const JMapInfoIter& rIter) {
    mSwitchCtrl = MR::createStageSwitchCtrl(this, rIter);
}

void LiveActor::initActorStarPointerTarget(f32 num, const TVec3f* pVec, MtxPtr pMtx, TVec3f vec) {
    mPointerTarget = new StarPointerTarget(num, pVec, pMtx, TVec3f(vec));
}

void LiveActor::initActorLightCtrl() {
    mLightCtrl = new ActorLightCtrl(this);
}

void LiveActor::attackSensor(HitSensor*, HitSensor*) {
}

void LiveActor::updateBinder() {
    if (mBinder == nullptr) {
        mPosition += mVelocity;
    } else {
        if (mFlags.mIsOnBind) {
            mPosition += mVelocity;
            mBinder->clear();
        } else {
            mPosition += mBinder->bind(mVelocity);
        }
    }
}
