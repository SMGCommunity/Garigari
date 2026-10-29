#include "Game/MapObj/RockReflector.hpp"
#include "Game/LiveActor/Nerve.hpp"
#include "Game/Util/ActorAnimUtil.hpp"
#include "Game/Util/ActorInitUtil.hpp"
#include "Game/Util/ActorMovementUtil.hpp"
#include "Game/Util/ActorSensorUtil.hpp"
#include "Game/Util/LiveActorUtil.hpp"

namespace NrvRockReflector {
    NEW_NERVE(RockReflectorNrvWait, RockReflector, Wait);
    NEW_NERVE(RockReflectorNrvReflect, RockReflector, Reflect);
};  // namespace NrvRockReflector

namespace {
    const f32 sReboundArg0 = 1;
    const f32 sReboundArg1 = 0;
    const f32 sReboundArg2 = 1;
};  // namespace

RockReflector::RockReflector(const char* pName) : LiveActor(pName) {
}

void RockReflector::init(const JMapInfoIter& rIter) {
    MR::initActor(this, rIter, "RockReflector", false);

    initNerve(GET_NERVE(RockReflector, RockReflectorNrvWait));

    makeActorAppeared();
}

bool RockReflector::canReflect() const {
    return isNerve(GET_NERVE(RockReflector, RockReflectorNrvWait));
}

bool RockReflector::receiveOtherMsg(u32 msg, HitSensor* pSender, HitSensor* pReceiver) {
    if (MR::isMsgReflect(msg)) {
        if (canReflect()) {
            if (MR::reboundVelocityFromCollision(MR::getSensorHost(pSender), ::sReboundArg0, ::sReboundArg1, ::sReboundArg2)) {
                MR::attenuateVelocity(MR::getSensorHost(pSender), 0.98f);

                setNerve(GET_NERVE(RockReflector, RockReflectorNrvReflect));
            }
        }

        return true;
    }

    return false;
}

void RockReflector::exeWait() {
}

void RockReflector::exeReflect() {
    if (MR::isFirstStep(this)) {
        MR::startAction(this, "Reflect");
    }

    if (MR::isActionEnd(this)) {
        setNerve(GET_NERVE(RockReflector, RockReflectorNrvWait));
    }
}
