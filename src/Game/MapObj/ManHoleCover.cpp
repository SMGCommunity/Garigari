
#include "Game/MapObj/ManholeCover.hpp"
#include "Game/LiveActor/Nerve.hpp"
#include "Game/MapObj/MapObjConnector.hpp"
#include "Game/Util/ActorAnimUtil.hpp"
#include "Game/Util/ActorInitUtil.hpp"
#include "Game/Util/ActorMovementUtil.hpp"
#include "Game/Util/ActorSensorUtil.hpp"
#include "Game/Util/ActorSwitchUtil.hpp"
#include "Game/Util/LiveActorUtil.hpp"
#include "Game/Util/PlayerUtil.hpp"
#include "decomp.h"

EXTERN_UNKNOWN_FUNC(void, 8000E850, TVec3f*, LiveActor*)

namespace {
    static const s32 sRattleTime = 45;
};

namespace NrvManholeCover {
    NEW_NERVE(HostTypeWait, ManholeCover, Wait);
    NEW_NERVE(HostTypeOpen, ManholeCover, Open);
    NEW_NERVE(HostTypeRattle, ManholeCover, Rattle);
};  // namespace NrvManholeCover

ManholeCover::ManholeCover(const char* pName) : LiveActor(pName), mConnector(), _94(), _95() {
    mConnector = new MapObjConnector(this);
}

void ManholeCover::init(const JMapInfoIter& rIter) {
    MR::initActor(this, rIter, false);
    initNerve(GET_NERVE(ManholeCover, HostTypeWait));

    TVec3f axisY;

    MR::calcActorAxisY(&axisY, this);

    mGravity.set(-axisY);

    makeActorAppeared();
}

void ManholeCover::initAfterPlacement() {
    mConnector->attachToBack();
}

void ManholeCover::control() {
    _94 = _95;
    _95 = false;
}

void ManholeCover::calcAndSetBaseMtx() {
    LiveActor::calcAndSetBaseMtx();
    mConnector->connect();
}

bool ManholeCover::receiveMsgPlayerAttack(u32 msg, HitSensor* pSender, HitSensor* pReceiver) {
    if (MR::isMsgPlayerHipDropFloor(msg) || MR::isMsgPlayerUpperPunch(msg)) {
        if (isNerve(GET_NERVE(ManholeCover, HostTypeWait)) || isNerve(GET_NERVE(ManholeCover, HostTypeRattle)) ||
            (isNerve(GET_NERVE(ManholeCover, HostTypeOpen)) && MR::isGreaterEqualStep(this, 20))) {
            f32 dist;
            f32 dot;
            MR::calcSensorDistanceGravity(&dist, &dot, pSender, pReceiver, mGravity);
            if (dist < 230.0f) {
                if (_94) {
                    setNerve(GET_NERVE(ManholeCover, HostTypeRattle));
                } else {
                    setNerve(GET_NERVE(ManholeCover, HostTypeOpen));
                }
                return true;
            }
        }
    }

    return false;
}

bool ManholeCover::receiveOtherMsg(u32 msg, HitSensor* pSender, HitSensor* pReceiver) {
    // TODO: actor message enum
    if (msg == 0xD1 && !_94) {
        return true;
    }

    if (msg == 0xD2) {
        _95 = true;
        return true;
    }

    if (MR::isMsgSpinStormRange(msg) && isNerve(GET_NERVE(ManholeCover, HostTypeWait))) {
        setNerve(GET_NERVE(ManholeCover, HostTypeRattle));
        return true;
    }

    return false;
}

void ManholeCover::exeWait() {
}

void ManholeCover::exeOpen() {
    if (MR::isFirstStep(this)) {
        MR::startAction(this, "Rotation");
        MR::invalidateCollisionParts(this);
    }

    if (MR::isValidSwitchA(this)) {
        TVec3f vec;
        fn_8000E850(&vec, this);
        TVec3f upVec;
        MR::calcUpVec(&upVec, this);

        if (vec.dot(upVec) > 0.0f) {
            if (MR::isOnSwitchA(this)) {
                MR::offSwitchA(this);
            }
        } else if (!MR::isOnSwitchA(this)) {
            MR::onSwitchA(this);
        }
    }

    if (MR::isStep(this, 20)) {
        MR::validateCollisionParts(this);
    }

    if (MR::isActionEnd(this)) {
        MR::validateCollisionParts(this);
        setNerve(GET_NERVE(ManholeCover, HostTypeWait));
    }
}

void ManholeCover::exeRattle() {
    if (MR::isFirstStep(this)) {
        MR::startAction(this, "Vibration");
    }

    if (MR::isGreaterStep(this, ::sRattleTime) && MR::isActionEnd(this)) {
        setNerve(GET_NERVE(ManholeCover, HostTypeWait));
    }
}
