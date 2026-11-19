#include "Game/MapObj/QuestionCoin.hpp"
#include "Game/LiveActor/LiveActor.hpp"
#include "Game/LiveActor/Nerve.hpp"
#include "Game/MapObj/CoinRotater.hpp"
#include "Game/MapObj/SpinDriverUtil.hpp"
#include "Game/NPC/ScoreAttackCounter.hpp"
#include "Game/Util/ActionSoundUtil.hpp"
#include "Game/Util/ActorAnimUtil.hpp"
#include "Game/Util/ActorCameraUtil.hpp"
#include "Game/Util/ActorInitUtil.hpp"
#include "Game/Util/ActorMovementUtil.hpp"
#include "Game/Util/ActorSensorUtil.hpp"
#include "Game/Util/ActorShadowUtil.hpp"
#include "Game/Util/ActorSwitchUtil.hpp"
#include "Game/Util/AreaObjUtil.hpp"
#include "Game/Util/EffectUtil.hpp"
#include "Game/Util/GravityUtil.hpp"
#include "Game/Util/JMapUtil.hpp"
#include "Game/Util/LiveActorUtil.hpp"
#include "Game/Util/MathUtil.hpp"
#include "Game/Util/MtxUtil.hpp"
#include "Game/Util/ObjUtil.hpp"
#include "Game/Util/PlayerUtil.hpp"

namespace {
    const f32 sHitRadius = 150.0f;
    const f32 sInWaterScale = 2.0f;
    const f32 sShadowHeightMargin = 300.0f;
    const f32 sShadowRadius = 120.0f;
    const s32 sBindStartBlendFrame = 0;
};  // namespace

namespace NrvQuestionCoin {
    NEW_NERVE(HostTypeWait, QuestionCoin, Wait);
    NEW_NERVE(HostTypeThrowActor, QuestionCoin, ThrowActor);
    NEW_NERVE(HostTypeCaught, QuestionCoin, Caught);
    NEW_NERVE(HostTypeKilled, QuestionCoin, Killed);
};  // namespace NrvQuestionCoin

QuestionCoin::QuestionCoin(const char* pName)
    : LiveActor(pName), mBindActor(), mCameraInfo(), mLaunchSpeed(), mIsWeakGravity(), mIsCalcShadow(), mPoseType(), mShadowLengthType(),
      mShadowPos(gZeroVec), mShadowDropLength() {
    mBaseMtx.identity();
    mActorMtx.identity();
    mLaunchQuat.set(0.0f, 0.0f, 0.0f, 1.0f);
    MR::createCoinRotater();
}

void QuestionCoin::init(const JMapInfoIter& rIter) {
    MR::initDefaultPos(this, rIter);
    initFromJMapInfoArg(rIter);

    if (mPoseType == 0) {
        MR::calcGravity(this);
        TPos3f mtx;
        MR::makeMtxTR(mtx.toMtxPtr(), mPosition, mRotation);
        TVec3f front;
        mtx.getZDir(front);
        MR::normalize(&front);
        MR::makeMtxUpFrontPos(&mBaseMtx, -mGravity, front, mPosition);
    } else {
        MR::makeMtxTR(mBaseMtx, this);
    }

    MR::initActor(this, rIter, "QuestionCoin", false);
    MR::startBpk(this, "QuestionCoin");
    MR::connectToSceneItemStrongLight(this);
    initEffectKeeper(0, nullptr, false);
    initSound(1, "QuestionCoin");
    initHitSensor(1);

    f32 radius = ::sHitRadius * mScale.x;
    HitSensor* sensor = MR::addHitSensor(this, "binder", ATYPE_QUESTION_COIN_BIND, 16, radius, TVec3f(0.0f, 210.0f * mScale.y, 0.0f));
    f32 diameter = 2.0f * radius;
    MR::setClippingTypeSphere(this, diameter, MR::getSensorPos2(sensor));

    initShadow();
    MR::initActorCamera(this, rIter, &mCameraInfo);
    initNerve(GET_NERVE(QuestionCoin, HostTypeWait));
    MR::needStageSwitchWriteDead(this, rIter);
    MR::useStageSwitchAwake(this, rIter);

    if (MR::initUseStageSwitchReadAppear(this, rIter)) {
        MR::listenStageSwitchOnAppear(this, MR::Functor(this, &QuestionCoin::appear));
        makeActorDead();
    } else {
        makeActorAppeared();
    }
}

void QuestionCoin::initAfterPlacement() {
    if (MR::isInWater(mPosition) && !MR::isInAreaObj("PlaneMode", mPosition)) {
        f32 binderRadius = MR::getSensorRadius(this, "binder");
        MR::setSensorRadius(this, "binder", ::sInWaterScale * binderRadius);
    }

    TPos3f rotation;
    rotation.setEuler(mRotation * (MR::pi() / 180.0f));
    TVec3f up;
    rotation.getYDir(up);
    TVec3f side;
    rotation.getXDir(side);
    TPos3f launchMtx;
    launchMtx.identity();
    MR::makeMtxUpSide(&launchMtx, up, side);
    launchMtx.getQuat(mLaunchQuat);

    f32 dropShadow = 1000.0f;
    if (mShadowLengthType == 1) {
        dropShadow = 1500.0f;
    } else if (mShadowLengthType == 2) {
        dropShadow = 2000.0f;
    }

    TVec3f gravity(gZeroVec);
    MR::calcGravityAndDropShadowVectorOrZero(this, &gravity, nullptr, 0);

    if (MR::isNearZero(gravity)) {
        gravity.set(-up);
    }

    mGravity.set(gravity);
    SpinDriverUtil::setShadowAndClipping(this, &mShadowPos, dropShadow, ::sShadowHeightMargin, &mShadowDropLength);
    MR::setShadowDropPositionPtr(this, nullptr, MR::getSensorPos2(this, "binder"));
}

void QuestionCoin::makeActorAppeared() {
    if (isNerve(GET_NERVE(QuestionCoin, HostTypeKilled))) {
        return;
    }

    LiveActor::makeActorAppeared();
}

void QuestionCoin::appear() {
    if (isNerve(GET_NERVE(QuestionCoin, HostTypeKilled))) {
        return;
    }

    LiveActor::appear();
    MR::showModel(this);
    MR::emitEffect(this, "Appear");

    if (MR::isValidSwitchDead(this)) {
        MR::offSwitchDead(this);
    }

    setNerve(GET_NERVE(QuestionCoin, HostTypeWait));
}

void QuestionCoin::kill() {
    mBindActor = nullptr;

    if (MR::isValidSwitchDead(this)) {
        MR::onSwitchDead(this);
    }

    LiveActor::kill();
    setNerve(GET_NERVE(QuestionCoin, HostTypeKilled));
}

void QuestionCoin::calcAndSetBaseMtx() {
    TPos3f maxPosition;
    maxPosition.identity();

    if (isNerve(GET_NERVE(QuestionCoin, HostTypeWait))) {
        maxPosition.concat(mBaseMtx, MR::getCoinInWaterRotateYMatrix());
    } else {
        maxPosition.set(mBaseMtx);
    }

    MR::setBaseTRMtx(this, maxPosition);
}

bool QuestionCoin::receiveMsgPlayerAttack(u32 msg, HitSensor* pSender, HitSensor* pReceiver) {
    return MR::isMsgStarPieceReflect(msg);
}

bool QuestionCoin::receiveOtherMsg(u32 msg, HitSensor* pSender, HitSensor* pReceiver) {
    if (MR::isMsgAutoRushBegin(msg) && isThrowActor() && isNerve(GET_NERVE(QuestionCoin, HostTypeWait))) {
        mBindActor = MR::getSensorHost(pSender);
        mActorMtx.set(mBindActor->getBaseMtx());
        setNerve(GET_NERVE(QuestionCoin, HostTypeThrowActor));
        return true;
    }

    if (MR::isMsgItemGet(msg) && !isThrowActor() && isNerve(GET_NERVE(QuestionCoin, HostTypeWait))) {
        setNerve(GET_NERVE(QuestionCoin, HostTypeCaught));
        return true;
    }

    if (MR::isMsgUpdateBaseMtx(msg)) {
        if (isNerve(GET_NERVE(QuestionCoin, HostTypeThrowActor))) {
            updateActorMtx();
        }
        return true;
    }

    return false;
}

void QuestionCoin::startClipped() {
    MR::forceDeleteEffect(this, "Light");
    LiveActor::startClipped();
}

void QuestionCoin::endClipped() {
    LiveActor::endClipped();
    MR::emitEffect(this, "Light");
}

void QuestionCoin::initFromJMapInfoArg(const JMapInfoIter& rIter) {
    MR::getJMapInfoArg0NoInit(rIter, &mLaunchSpeed);
    s32 arg1 = -1;
    MR::getJMapInfoArg1NoInit(rIter, &arg1);
    mIsWeakGravity = arg1 == 0;
    MR::getJMapInfoArg2NoInit(rIter, &mPoseType);
    MR::getJMapInfoArg3NoInit(rIter, &mShadowLengthType);
    s32 arg4 = -1;
    MR::getJMapInfoArg4NoInit(rIter, &arg4);
    mIsCalcShadow = arg4 != -1;
}

void QuestionCoin::initShadow() {
    MR::initShadowVolumeSphere(this, ::sShadowRadius * mScale.x);

    if (mIsCalcShadow) {
        MR::onCalcShadow(this, nullptr);
    }
}

void QuestionCoin::updateActorMtx() {
    f32 rate = 1.0f;

    if (MR::isLessEqualStep(this, ::sBindStartBlendFrame) && ::sBindStartBlendFrame > 0) {
        rate = MR::calcNerveRate(this, ::sBindStartBlendFrame);
    }

    TQuat4f startQuat;
    mActorMtx.getQuat(startQuat);
    TQuat4f quat = static_cast< TVec4f >(startQuat);  // TODO: FAKEMATCH
    quat.slerp(mLaunchQuat, rate);
    TVec3f startPos;
    mActorMtx.getTrans(startPos);
    TVec3f position;
    position.lerp(startPos, *MR::getSensorPos(this, "binder"), rate);
    TPos3f mtx;
    mtx.setQT(quat, position);
    MR::setBaseTRMtx(mBindActor, mtx);
}

void QuestionCoin::exeWait() {
}

void QuestionCoin::exeThrowActor() {
    if (MR::isFirstStep(this)) {
        MR::emitEffect(this, "Get");
        MR::startActionSound(this, "SyQuestionCoin");
        MR::tryRumblePadMiddle(this, 0);
        MR::hideModel(this);
        ScoreAttackFunction::score1000Points(this);
        MR::startAction(mBindActor, "QuestionCoinJumpStart");
        MR::startActionSoundPlayer("JumpObj", -1, -1);

        if (MR::isExistActorCamera(mCameraInfo)) {
            MR::startActorCameraNoTarget(this, mCameraInfo, -1);
        }
    }

    if (MR::isStep(this, 3)) {
        TRot3f rotation;
        MR::makeMtxRotate(rotation, mRotation);
        TVec3f velocity;
        rotation.getYDir(velocity);
        velocity.setLength(mLaunchSpeed);
        mBindActor->mVelocity.set(velocity);
        MR::startAction(mBindActor, "QuestionCoinJump");

        if (mIsWeakGravity) {
            MR::endBindAndPlayerForceWeakGravityJump(this, velocity);
        } else {
            MR::endBindAndPlayerJump(this, velocity, 3);
        }

        MR::endActorCameraAtLanding(this, mCameraInfo, -1);
        kill();
    }
}

void QuestionCoin::exeCaught() {
    if (MR::isFirstStep(this)) {
        MR::emitEffect(this, "Get");
        MR::startActionSound(this, "SyQuestionCoin");
        MR::tryRumblePadMiddle(this, 0);
        MR::hideModel(this);
        ScoreAttackFunction::score1000Points(this);
        kill();
    }
}

void QuestionCoin::exeKilled() {
}
