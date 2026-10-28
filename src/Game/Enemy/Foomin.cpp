#include "Game/Enemy/Foomin.hpp"
#include "Game/Enemy/SupportTicoStop.hpp"
#include "Game/LiveActor/Nerve.hpp"
#include "Game/Util/ActorAnimUtil.hpp"
#include "Game/Util/ActorInitUtil.hpp"
#include "Game/Util/ActorSwitchUtil.hpp"
#include "Game/Util/JMapUtil.hpp"
#include "Game/Util/LiveActorUtil.hpp"
#include "Game/Util/RailUtil.hpp"
#include "Game/Util/ActorMovementUtil.hpp"

namespace NrvFoomin {
    NEW_NERVE(FoominNrvWait, Foomin, Wait);
    NEW_NERVE(FoominNrvWaitDelay, Foomin, WaitDelay);
    NEW_NERVE(FoominNrvAttackSign, Foomin, AttackSign);
    NEW_NERVE(FoominNrvAttack, Foomin, Attack);
}; // namespace nrvFoomin


Foomin::Foomin(const char* pName) : LiveActor(pName), mSupportTicoStop(), mFrontVec(0.0f, 0.0f, 1.0f), mMovementSpeed(250), mFirstFlipDelay() {}

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

    initNerve(GET_NERVE(Foomin, FoominNrvWaitDelay));

    makeActorAppeared();
}

void Foomin::makeActorAppeared() {
    if (mFirstFlipDelay > 0) {
        setNerve(GET_NERVE(Foomin, FoominNrvWaitDelay));
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
