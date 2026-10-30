#include "Game/MapObj/KoopaJrCastleGate.hpp"
#include "Game/LiveActor/LiveActor.hpp"
#include "Game/LiveActor/Nerve.hpp"
#include "Game/Util/ActorAnimUtil.hpp"
#include "Game/Util/ActorInitUtil.hpp"
#include "Game/Util/ActorSwitchUtil.hpp"
#include "Game/Util/DemoUtil.hpp"
#include "Game/Util/LiveActorUtil.hpp"

namespace NrvKoopaJrCastleGate {
    NEW_NERVE(KoopaJrCastleGateNrvWait, KoopaJrCastleGate, Wait);
    NEW_NERVE(KoopaJrCastleGateNrvMove, KoopaJrCastleGate, Move);
    NEW_NERVE(KoopaJrCastleGateNrvMoveFast, KoopaJrCastleGate, MoveFast);
    NEW_NERVE(KoopaJrCastleGateNrvWaitEnd, KoopaJrCastleGate, WaitEnd);
};  // namespace NrvKoopaJrCastleGate

KoopaJrCastleGate::KoopaJrCastleGate(const char* pName) : LiveActor(pName) {
}

void KoopaJrCastleGate::init(const JMapInfoIter& rIter) {
    MR::initActor(this, rIter, false);

    initNerve(GET_NERVE(KoopaJrCastleGate, KoopaJrCastleGateNrvWait));

    if (MR::tryRegisterDemoCast(this, rIter)) {
        MR::tryRegisterDemoActionNerve(this, GET_NERVE(KoopaJrCastleGate, KoopaJrCastleGateNrvMove), nullptr);
    }

    makeActorAppeared();
}

void KoopaJrCastleGate::exeWait() {
    if (!isNerve(GET_NERVE(KoopaJrCastleGate, KoopaJrCastleGateNrvWaitEnd))) {
        if (MR::isValidSwitchA(this) && MR::isOnSwitchA(this)) {
            MR::invalidateClipping(this);

            setNerve(GET_NERVE(KoopaJrCastleGate, KoopaJrCastleGateNrvMoveFast));
        }
    }
}

void KoopaJrCastleGate::exeMove() {
    if (MR::isFirstStep(this)) {
        MR::startAction(this, "Move");
    }

    if (MR::isActionEnd(this)) {
        MR::invalidateCollisionParts(this);

        setNerve(GET_NERVE(KoopaJrCastleGate, KoopaJrCastleGateNrvWaitEnd));
    }
}

void KoopaJrCastleGate::exeMoveFast() {
    if (MR::isFirstStep(this)) {
        MR::startAction(this, "MoveFast");

        if (MR::isValidSwitchB(this)) {
            MR::onSwitchB(this);
        }
    }

    if (MR::isActionEnd(this)) {
        MR::validateClipping(this);
        MR::invalidateCollisionParts(this);

        setNerve(GET_NERVE(KoopaJrCastleGate, KoopaJrCastleGateNrvWaitEnd));
    }
}

void KoopaJrCastleGate::exeWaitEnd() {
    exeWait();
}
