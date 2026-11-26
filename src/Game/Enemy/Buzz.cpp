#include "Game/Enemy/Buzz.hpp"
#include "Game/Enemy/AnimScaleController.hpp"
#include "Game/Enemy/WalkerStateBindStarPointer.hpp"
#include "Game/LiveActor/Nerve.hpp"
#include "Game/Player/YoshiLockOnManager.hpp"
#include "Game/Player/YoshiUtil.hpp"
#include "Game/Util/ActorAnimUtil.hpp"
#include "Game/Util/ActorInitUtil.hpp"
#include "Game/Util/ActorMovementUtil.hpp"
#include "Game/Util/ActorSensorUtil.hpp"
#include "Game/Util/ActorStateUtil.hpp"
#include "Game/Util/JMapUtil.hpp"
#include "Game/Util/LiveActorUtil.hpp"
#include "Game/Util/RailUtil.hpp"
#include <decomp.h>

EXTERN_UNKNOWN_FUNC(void, 80014360, TVec3f*, LiveActor*, f32)
EXTERN_UNKNOWN_FUNC(void, 80052450, LiveActor*, f32, f32, f32)
EXTERN_UNKNOWN_FUNC(void, 8022BA10, LiveActor*)

namespace NrvBuzz {
    NEW_NERVE(BuzzNrvWait, Buzz, Wait);
    NEW_NERVE(BuzzNrvYoshiEaten, Buzz, YoshiEaten);
    NEW_NERVE(BuzzNrvSupportFreeze, Buzz, SupportFreeze);
    NEW_NERVE(BuzzNrvStarPieceHit, Buzz, StarPieceHit);
    NEW_NERVE(BuzzNrvAttackSuccess, Buzz, AttackSuccess);
    NEW_NERVE(BuzzNrvBlowDown, Buzz, BlowDown);
    NEW_NERVE(BuzzNrvStepDown, Buzz, StepDown);
};  // namespace NrvBuzz

Buzz::Buzz(const char* pName) : LiveActor(pName), mClippingCenter(0.0f, 0.0f, 0.0f), mFrontVec(0.0f, 0.0f, 1.0f), mRailSpeed(3.0f), mScaleController(), mWalkerStateBindStarPointer(), mYoshiLockOnTarget() {
}

void Buzz::init(const JMapInfoIter& rIter) {
    MR::initActor(this, rIter, false);

    MR::calcFrontVec(&mFrontVec, this);

    if (MR::isExistRail(this)) {
        MR::moveCoordAndTransToNearestRailPos(this);
        MR::initAndSetRailClipping(&mClippingCenter, this, 100.0f, 500.0f);
    }

    MR::getJMapInfoArg0NoInit(rIter, &mRailSpeed);

    initNerve(GET_NERVE(Buzz, BuzzNrvWait), 1);

    mScaleController = new AnimScaleController(nullptr);
    mWalkerStateBindStarPointer = new WalkerStateBindStarPointer(this, mScaleController);

    MR::initActorState(this, mWalkerStateBindStarPointer, GET_NERVE(Buzz, BuzzNrvSupportFreeze), "SupportFreeze");

    mYoshiLockOnTarget = MR::createYoshiLockOnTarget(this, nullptr, TVec3f(0.0f));

    makeActorAppeared();
}

void Buzz::control() {
    mScaleController->updateNerve();

    if (isYoshiEatable()) {
        YoshiFunction::tryYoshiEat(mYoshiLockOnTarget);
    }

    if (isSupportFreezable() && mWalkerStateBindStarPointer->tryStartPointBind()) {
        setNerve(GET_NERVE(Buzz, BuzzNrvSupportFreeze));
    }
}

void Buzz::calcAndSetBaseMtx() {
    LiveActor::calcAndSetBaseMtx();
    MR::calcAndSetBaseTRMtxFromGravityAndZAxis(this, mFrontVec);

    MR::updateBaseScale(this, mScaleController);
}

void Buzz::attackSensor(HitSensor* pSender, HitSensor* pReceiver) {
    if (MR::isSensorPlayer(pReceiver) && fn_80176300() && MR::sendMsgEnemyAttack(pReceiver, pSender)) {
        setNerve(GET_NERVE(Buzz, BuzzNrvAttackSuccess));
        return;
    }

    if (fn_80176310()) {
        MR::sendMsgPush(pReceiver, pSender);
    }
}

bool Buzz::receiveMsgPlayerAttack(u32 msg, HitSensor* pSender, HitSensor* pReceiver) {
    if (MR::isMsgLockOnStarPieceShoot(msg)) {
        return true;
    }

    if (MR::isMsgStarPieceAttack(msg) && fn_80176390()) {
        setNerve(GET_NERVE(Buzz, BuzzNrvStarPieceHit));
        return true;
    }

    if (MR::isMsgInvincibleAttack(msg) || MR::isMsgYoshiProjectile(msg)) {
        MR::calcSensorDirectionNormalize(&mFrontVec, pReceiver, pSender);
        MR::setVelocitySeparateHV(this, pSender, pReceiver, 30.0f, 30.0f);

        setNerve(GET_NERVE(Buzz, BuzzNrvBlowDown));

        return true;
    }

    return false;
}

bool Buzz::receiveOtherMsg(u32 msg, HitSensor* pSender, HitSensor* pReceiver) {
    if (MR::isMsgYoshiStartTongue(msg) && isYoshiEatable()) {
        setNerve(GET_NERVE(Buzz, BuzzNrvYoshiEaten));

        MR::zeroVelocity(this);

        return true;
    }

    if (MR::isMsgYoshiLoopTongue(msg)) {
        return true;
    }

    if (MR::isMsgYoshiReleaseEaten(msg)) {
        MR::setScale(this, 1.0f);
        MR::setRotation(this, nullptr);

        kill();

        return true;
    }

    if (MR::isMsgYoshiCancelEaten(msg)) {
        MR::setScale(this, 1.0f);
        MR::setRotation(this, nullptr);

        kill();

        return true;
    }

    return false;
}

bool Buzz::isSupportFreezable() const {
    if (isNerve(GET_NERVE(Buzz, BuzzNrvWait)) || isNerve(GET_NERVE(Buzz, BuzzNrvAttackSuccess))) {
        return true;
    }

    if (isNerve(GET_NERVE(Buzz, BuzzNrvStarPieceHit))) {
        return MR::isGreaterStep(this, 30);
    }

    return false;
}

bool Buzz::fn_80176300() const {
    return isNerve(GET_NERVE(Buzz, BuzzNrvWait));
}

bool Buzz::fn_80176310() const {
    if (isNerve(GET_NERVE(Buzz, BuzzNrvWait)) || isNerve(GET_NERVE(Buzz, BuzzNrvAttackSuccess)) || isNerve(GET_NERVE(Buzz, BuzzNrvStarPieceHit)) ||
        isNerve(GET_NERVE(Buzz, BuzzNrvSupportFreeze))) {
        return true;
    }

    return false;
}

bool Buzz::fn_80176390() const {
    if (isNerve(GET_NERVE(Buzz, BuzzNrvWait)) || isNerve(GET_NERVE(Buzz, BuzzNrvAttackSuccess)) || isNerve(GET_NERVE(Buzz, BuzzNrvStarPieceHit)) ||
        isNerve(GET_NERVE(Buzz, BuzzNrvSupportFreeze))) {
        return true;
    }

    return false;
}

bool Buzz::isYoshiEatable() const {
    if (isNerve(GET_NERVE(Buzz, BuzzNrvWait)) || isNerve(GET_NERVE(Buzz, BuzzNrvAttackSuccess)) || isNerve(GET_NERVE(Buzz, BuzzNrvStarPieceHit)) ||
        isNerve(GET_NERVE(Buzz, BuzzNrvSupportFreeze))) {
        return true;
    }

    return false;
}

void Buzz::exeWait() {
    if (MR::isFirstStep(this)) {
        MR::startAction(this, "Wait");
    }

    TVec3f vec18;
    fn_80014360(&vec18, this, 30.0f);
    MR::turnDirectionDegree(this, &mFrontVec, vec18, 2.0f);

    if (MR::isExistRail(this)) {
        fn_80052450(this, mRailSpeed, mRailSpeed * 0.2f, 100.0f);
    }
}

void Buzz::exeYoshiEaten() {
}

void Buzz::exeSupportFreeze() {
    MR::updateActorStateAndNextNerve(this, GET_NERVE(Buzz, BuzzNrvWait));
}

void Buzz::exeStarPieceHit() {
    if (MR::isFirstStep(this)) {
        MR::startAction(this, "StarPieceHit");
    }

    if (MR::isActionEnd(this)) {
        setNerve(GET_NERVE(Buzz, BuzzNrvWait));
    }
}

void Buzz::exeAttackSuccess() {
    if (MR::isFirstStep(this)) {
        MR::startAction(this, "AttackSuccess");
    }

    if (MR::isActionEnd(this)) {
        setNerve(GET_NERVE(Buzz, BuzzNrvWait));
    }
}

void Buzz::exeBlowDown() {
    if (MR::isFirstStep(this)) {
        MR::startAction(this, "BlowDown");
    }

    MR::reboundVelocityFromCollision(this, 0.0f, 0.0f, 1.0f);
    MR::addVelocityToGravityOrGround(this, 1.2f);
    MR::attenuateVelocity(this, 0.99f);

    if (MR::isGreaterStep(this, 20)) {
        fn_8022BA10(this);
        kill();
    }
}

void Buzz::exeStepDown() {
    if (MR::isFirstStep(this)) {
        MR::startAction(this, "StepDown");
    }

    if (MR::isActionEnd(this)) {
        kill();
    }
}
