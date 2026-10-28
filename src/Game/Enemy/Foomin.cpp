#include "Game/Enemy/Foomin.hpp"
#include "Game/Enemy/SupportTicoStop.hpp"
#include "Game/LiveActor/Nerve.hpp"
#include "Game/Util/ActorAnimUtil.hpp"
#include "Game/Util/ActorInitUtil.hpp"
#include "Game/Util/ActorMovementUtil.hpp"
#include "Game/Util/ActorSwitchUtil.hpp"
#include "Game/Util/EffectUtil.hpp"
#include "Game/Util/JMapUtil.hpp"
#include "Game/Util/LiveActorUtil.hpp"
#include "Game/Util/MathUtil.hpp"
#include "Game/Util/PlayerUtil.hpp"
#include "Game/Util/RailUtil.hpp"
#include "decomp.h"


EXTERN_UNKNOWN_FUNC(void, 80052450, LiveActor*, f32, f32, f32)

namespace NrvFoomin {
    NEW_NERVE(FoominNrvWait, Foomin, Wait);
    NEW_NERVE(FoominNrvWaitRail, Foomin, WaitRail);
    NEW_NERVE(FoominNrvAttackSign, Foomin, AttackSign);
    NEW_NERVE(FoominNrvAttack, Foomin, Attack);
};  // namespace NrvFoomin

Foomin::Foomin(const char* pName) : LiveActor(pName), mSupportTicoStop(), mFrontVec(0.0f, 0.0f, 1.0f), mMovementSpeed(250), mFirstFlipDelay() {
}

void Foomin::init(const JMapInfoIter& rIter) {
    MR::initActor(this, rIter, "Foomin", false);
    if (MR::isExistRail(this)) {
        MR::moveCoordAndTransToNearestRailPos(this);
    }

    MR::calcFrontVec(&mFrontVec, this);

    mSupportTicoStop = new SupportTicoStop(this, nullptr);

    s32 firstFlipDelayArg = 0;

    MR::getJMapInfoArg0NoInit(rIter, &firstFlipDelayArg);

    if (firstFlipDelayArg >= 0) {
        mFirstFlipDelay = firstFlipDelayArg;
    }

    s32 movementSpeedArg = -1;

    MR::getJMapInfoArg1NoInit(rIter, &movementSpeedArg);

    if (movementSpeedArg >= 0) {
        mMovementSpeed = movementSpeedArg;
    }

    initNerve(GET_NERVE(Foomin, FoominNrvWaitRail));

    makeActorAppeared();
}

void Foomin::makeActorAppeared() {
    if (mFirstFlipDelay > 0) {
        setNerve(GET_NERVE(Foomin, FoominNrvWaitRail));
    } else {
        setNerve(GET_NERVE(Foomin, FoominNrvWait));
    }

    LiveActor::makeActorAppeared();
}

void Foomin::control() {
    mSupportTicoStop->updateNerve();
}

void Foomin::exeWait() {
    if (MR::isFirstStep(this)) {
        MR::startAction(this, "Wait");
        MR::validateClipping(this);
    }

    if (!MR::isValidSwitchA(this) || MR::isOnSwitchA(this)) {
        if (MR::isGreaterStep(this, mFirstFlipDelay)) {
            setNerve(GET_NERVE(Foomin, FoominNrvAttackSign));
        }
    }
}

void Foomin::exeWaitRail() {
    if (MR::isFirstStep(this)) {
        MR::startAction(this, "Wait");
        MR::validateClipping(this);
    }

    if (mSupportTicoStop->tryAttachTouch()) {
        return;
    }

    if (!MR::isValidSwitchA(this) || MR::isOnSwitchA(this)) {
        if (MR::isGreaterStep(this, 120)) {
            setNerve(GET_NERVE(Foomin, FoominNrvAttackSign));
        }
    }

    calcRailPos();
}

void Foomin::exeAttackSign() {
    if (MR::isFirstStep(this)) {
        MR::startAction(this, "AttackSign");
        MR::invalidateClipping(this);
    }
    if (mSupportTicoStop->tryAttachTouch()) {
        return;
    }

    calcRailPos();

    if (MR::isActionEnd(this)) {
        setNerve(GET_NERVE(Foomin, FoominNrvAttack));
    }
}

// Stack problems
// https://decomp.me/scratch/b2Eu7
void Foomin::exeAttack() {
    if (MR::isFirstStep(this)) {
        MR::startAction(this, "Attack");
    }

    if (MR::isLessStep(this, 25) && MR::isActorOnPlayer(this)) {
        TVec3f frontVec(0.0f);
        MR::calcFrontVec(&frontVec, this);

        TVec3f stack_20 = -frontVec * -0.5f;

        TVec3f stack_2C = -mGravity;

        TVec3f playerJumpVel(stack_2C);

        playerJumpVel.add(stack_20);

        MR::normalize(&playerJumpVel);

        MR::forceJumpPlayer(playerJumpVel * 35.0f);

        MR::startBckPlayer("Blow", nullptr);

        MR::startLevelSoundPlayer("Thrown", -1, -1);

        MR::emitEffect(this, "Shrink");
        MR::invalidateCollisionParts(this);
    }

    calcRailPos();

    if (MR::isActionEnd(this)) {
        MR::validateCollisionParts(this);
        setNerve(GET_NERVE(Foomin, FoominNrvWaitRail));
    }
}

void Foomin::calcAndSetBaseMtx() {
    MR::calcAndSetBaseTRMtxFromGravityAndZAxis(this, mFrontVec);
}

void Foomin::calcRailPos() {
    if (MR::isExistRail(this)) {
        f32 movementRate = 0.01f * mMovementSpeed;

        fn_80052450(this, movementRate, 0.2f * movementRate, 100.0f);
    }
}
