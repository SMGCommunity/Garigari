#include "LiveActor/LiveActor.hpp"
#include "LiveActor/HitSensor.hpp"
#include "LiveActor/HitSensorKeeper.hpp"
#include "LiveActor/Spine.hpp"
#include "LiveActor/ModelManager.hpp"
#include "LiveActor/J3DModel.hpp"
#include "LiveActor/StarPointerTarget.hpp"
#include "Util/LiveActorUtil.hpp"
#include "LiveActor/ActorActionKeeper.hpp"
#include "Map/StageSwitch.hpp"

#include "LiveActor/LiveActorGroup.hpp"
#include "LiveActor/RailRider.hpp"
#include "LiveActor/ActorLightCtrl.hpp"
#include "LiveActor/ClippingDirector.hpp"
#include "LiveActor/Binder.hpp"
#include "LiveActor/EffectKeeper.hpp"
#include "LiveActor/ActorSoundHolder.hpp"
#include "LiveActor/ShadowControllerList.hpp"

namespace MR {
    LiveActorGroup* getAllLiveActorGroup();
    void onBind(LiveActor*);
    void makeMtxTRS(MtxPtr, const LiveActor*);
    const f32 (*getCameraProjectionMtx())[4];
    void calcJ3DModel(LiveActor*);
    HitSensor* getTaken(const LiveActor*);
    void setBaseTRMtx(LiveActor*, MtxPtr);
    void setBaseTRMtx(LiveActor*, const TPos3f&);
    void makeMtxTR(MtxPtr, const LiveActor*);
    void makeMtxTransRotateY(MtxPtr, const LiveActor*);
    J3DModel* getJ3DModel(const LiveActor*);
    bool isCalcGravity(const LiveActor*);
    void updateLightCtrl(LiveActor*);
    void actorSoundMovement(LiveActor*);
    void requestCalcActorShadow(LiveActor*);
    void setCollisionMtx(LiveActor*);
    bool isClipped(const LiveActor*);
    void validateCollisionParts(LiveActor*);
    void invalidateCollisionParts(LiveActor*);
    void resetPosition(LiveActor*);
    void tryUpdateHitSensorsAll(LiveActor*);
    void addToClippingTarget(LiveActor*);
    void removeFromClippingTarget(LiveActor*);
    void clearHitSensors(LiveActor*);
    void onSwitchDead(LiveActor*);
    ResourceHolder* getModelResourceHolder(const LiveActor*);
    void disconnectToSceneTemporarily(NameObj*);
    void disconnectToDrawTemporarily(NameObj*);
    void connectToSceneTemporarily(NameObj*);
    void connectToDrawTemporarily(NameObj*);
    bool isNoEntryDrawBuffer(const LiveActor*);
    void updateHitSensorsAll(LiveActor*);
}
extern "C" void fn_80233EE0(EffectKeeper*);
extern "C" void fn_8022C160(ActorLightCtrl*);
extern "C" void fn_80034DA0(LiveActor*);
extern "C" void fn_80233C30(EffectKeeper*);

// Source-side helper preserves the retail one/zero/minus-one pool order.
// Calls inline; the unused out-of-line body is removed by the linker.
float getLiveActorDefaultScale() { return 1.0f; }
LiveActor::LiveActor(const char* name) : NameObj(name),
    mPosition(0.0f, 0.0f, 0.0f),
    mRotation(0.0f, 0.0f, 0.0f),
    mScale(getLiveActorDefaultScale(), getLiveActorDefaultScale(), getLiveActorDefaultScale()),
    mVelocity(0.0f, 0.0f, 0.0f),
    mGravity(0.0f, -1.0f, 0.0f),
    mActionKeeper(nullptr), mModelManager(nullptr), mSpine(nullptr),
    mSensorKeeper(nullptr), mBinder(nullptr), mRailRider(nullptr),
    mEffectKeeper(nullptr), mSoundHolder(nullptr),
    mShadowList(nullptr), mCollisionParts(nullptr), mSwitchCtrl(nullptr),
    mPointerTarget(nullptr), mLightCtrl(nullptr) {
    MR::getAllLiveActorGroup()->registerActor(this);
    MR::getClippingDirector()->registerActor(this);
}

void LiveActor::init(const JMapInfoIter &) {}

void LiveActor::appear() {
    makeActorAppeared();
}

void LiveActor::makeActorAppeared() {
    if (getSensorKeeper() != nullptr) {
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
        fn_8022C160(mLightCtrl);
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
    mVelocity.x = mVelocity.y = mVelocity.z = 0.0f;
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
        fn_80034DA0(this);
    }
    if (mSensorKeeper != nullptr) {
        mSensorKeeper->doObjCol();
    }
    if (mFlags.mIsDead) { return; }
    if (mSpine != nullptr) {
        mSpine->update();
    }
    if (mFlags.mIsDead) { return; }
    control();
    if (mFlags.mIsDead) { return; }
    updateBinder();
    if (mActionKeeper != nullptr) {
        mActionKeeper->update();
    }
    if (mEffectKeeper != nullptr) {
        fn_80233C30(mEffectKeeper);
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
void LiveActor::calcAnmMtx() {
    if (mModelManager != nullptr) {
        MR::getJ3DModel(this)->setBaseScale(mScale);
        calcAndSetBaseMtx();
        mModelManager->calcAnim();
    }
}
void J3DModel::setBaseScale(const Vec& scale) {
    mBaseScale = scale;
}
void LiveActor::calcViewAndEntry() {
    if (!mFlags.mIsNoCalcView) {
        if (mModelManager != nullptr) {
            if (!mFlags.mIsNoCalcView) {
                mModelManager->calcView();
            }
        }
    }
}
namespace {
    inline bool isPlayerAttackMessage(u32 msg) { return msg != 0 && msg < 0x26; }
    inline bool isEnemyAttackMessage(u32 msg) { bool result = false; if (0x59 < msg && 0x75 > msg) { result = true; } return result; }
}
bool LiveActor::receiveMessage(u32 msg, HitSensor* sender, HitSensor* receiver) {
    if (msg == 0x33) {
        return receiveMsgPush(sender, receiver);
    }
    if (isPlayerAttackMessage(msg)) {
        return receiveMsgPlayerAttack(msg, sender, receiver);
    }
    if (isEnemyAttackMessage(msg)) {
        return receiveMsgEnemyAttack(msg, sender, receiver);
    }
    return receiveOtherMsg(msg, sender, receiver);
}
void LiveActor::calcAndSetBaseMtx() {
    if (MR::getTaken(this)) {
        MR::setBaseTRMtx(this, MR::getTaken(this)->mHostActor->getTakingMtx());
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

void LiveActor::setNerve(const Nerve *pNerve) {
    mSpine->setNerve(pNerve);
}

bool LiveActor::isNerve(const Nerve *pNerve) const {
    return mSpine->getCurrentNerve() == pNerve;
}

s32 LiveActor::getNerveStep() const {
    return mSpine->mCurrentStep;
}

HitSensor* LiveActor::getSensor(const char *pSensorName) const {
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
        fn_80233EE0(mEffectKeeper);
    }
    MR::disconnectToSceneTemporarily(this);
    if (MR::isNoEntryDrawBuffer(this)) {
        return;
    }
    MR::disconnectToDrawTemporarily(this);
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
    if (MR::isNoEntryDrawBuffer(this)) {
        return;
    }
    MR::connectToDrawTemporarily(this);
}
void LiveActor::initModelManagerWithAnm(const char* model, const char* animation, const char* action, bool flag) {
    mModelManager = new ModelManager(MR::getCameraProjectionMtx());
    mModelManager->init(model, animation, flag);
    MR::getJ3DModel(this)->setBaseScale(mScale);
    LiveActor::calcAndSetBaseMtx();
    MR::calcJ3DModel(this);
    mActionKeeper = ActorActionKeeper::tryCreate(this, action);
}

void LiveActor::initNerve(const Nerve *pNerve, s32 numStates) {
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
void LiveActor::initRailRider(const JMapInfoIter& iter) {
    mRailRider = new RailRider(iter);
}
void LiveActor::initEffectKeeper(s32 count, const char* name, bool sort) {
    mEffectKeeper = new EffectKeeper(getName(), MR::getModelResourceHolder(this), count, name);
    if (sort) {
        mEffectKeeper->enableSort();
    }
    mEffectKeeper->init(this);
    if (mBinder != nullptr) {
        mEffectKeeper->setBinder(mBinder);
    }
}
void LiveActor::initSound(s32 count, const char* name, const TVec3f* position, const TVec3f& offset) {
    mSoundHolder = new ActorSoundHolder(this, count, name, position, TVec3f(offset));
}
void LiveActor::initShadowControllerList(u32 count) {
    mShadowList = new ShadowControllerList(this, count);
}
namespace {
    inline void copyCollisionMatrix(__REGISTER void* pDest, __REGISTER const void* pSrc) {
#ifdef __MWERKS__
        register f32 f_5, f_4, f_3, f_2, f_1, f_0;

        __asm {
            psq_l     f_0, 0(pSrc), 0, 0
            psq_l     f_1, 8(pSrc), 0, 0
            psq_l     f_2, 0x10(pSrc), 0, 0
            psq_l     f_3, 0x18(pSrc), 0, 0
            psq_l     f_4, 0x20(pSrc), 0, 0
            psq_l     f_5, 0x28(pSrc), 0, 0
            psq_st    f_0, 0(pDest), 0, 0
            psq_st    f_1, 8(pDest), 0, 0
            psq_st    f_2, 0x10(pDest), 0, 0
            psq_st    f_3, 0x18(pDest), 0, 0
            psq_st    f_4, 0x20(pDest), 0, 0
            psq_st    f_5, 0x28(pDest), 0, 0
        }
        ;
#endif
    }

}

void LiveActor::initActorCollisionParts(const char* name, HitSensor* sensor, ResourceHolder* resource, MtxPtr matrix, bool equalScale, bool noScale) {
    MR::CollisionScaleType scaleType;
    if (noScale) {
        scaleType = MR::CollisionScaleType_NotUsingScale;
    } else {
        scaleType = MR::CollisionScaleType_Default;
        if (equalScale) {
            scaleType = MR::CollisionScaleType_AutoEqualScale;
        }
    }
    if (resource != nullptr) {
        TPos3f mtx;
        if (matrix != nullptr) {
            copyCollisionMatrix(&mtx, matrix);
        } else {
            MR::makeMtxTRS(mtx, this);
        }
        mCollisionParts = MR::createCollisionPartsFromResourceHolder(resource, name, sensor, mtx, matrix, scaleType);
    } else if (matrix == nullptr) {
        mCollisionParts = MR::createCollisionPartsFromLiveActor(this, name, sensor, scaleType);
    } else {
        mCollisionParts = MR::createCollisionPartsFromLiveActor(this, name, sensor, matrix, scaleType);
    }
    MR::invalidateCollisionParts(this);
}

void LiveActor::initStageSwitch(const JMapInfoIter &rIter) {
    mSwitchCtrl = MR::createStageSwitchCtrl(this, rIter);
}

void LiveActor::initActorStarPointerTarget(f32 radius, const TVec3f* position, MtxPtr matrix, TVec3f offset) {
    mPointerTarget = new StarPointerTarget(radius, position, matrix, offset);
}
void LiveActor::initActorLightCtrl() {
    mLightCtrl = new ActorLightCtrl(this);
}

void LiveActor::attackSensor(HitSensor *, HitSensor *) {
    
}

void LiveActor::updateBinder() {
    if (mBinder == nullptr) {
        mPosition += mVelocity;
    } else if (mFlags.mIsOnBind) {
        mPosition += mVelocity;
        mBinder->clear();
    } else {
        mPosition += mBinder->bind(mVelocity);
    }
}

