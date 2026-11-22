#include "Game/MapObj/RestartObj.hpp"
#include "Game/LiveActor/Nerve.hpp"
#include "Game/MapObj/MapObjConnector.hpp"
#include "Game/Player/YoshiLockOnManager.hpp"
#include "Game/Player/YoshiUtil.hpp"
#include "Game/System/GameSequenceFunction.hpp"
#include "Game/Util/ActionSoundUtil.hpp"
#include "Game/Util/ActorAnimUtil.hpp"
#include "Game/Util/ActorInitUtil.hpp"
#include "Game/Util/ActorMovementUtil.hpp"
#include "Game/Util/ActorSensorUtil.hpp"
#include "Game/Util/ActorSwitchUtil.hpp"
#include "Game/Util/EffectUtil.hpp"
#include "Game/Util/EventUtil.hpp"
#include "Game/Util/JMapIdInfo.hpp"
#include "Game/Util/JMapUtil.hpp"
#include "Game/Util/JointUtil.hpp"
#include "Game/Util/LiveActorUtil.hpp"
#include "Game/Util/MathUtil.hpp"
#include "Game/Util/ObjUtil.hpp"
#include "Game/Util/PlayerUtil.hpp"
#include "Game/Util/SupportPlayUtil.hpp"
#include "revolution/wpad.h"

namespace NrvRestartObj {
    NEW_NERVE(RestartObjNrvBefore, RestartObj, Before);
    NEW_NERVE(RestartObjNrvGet, RestartObj, Get);
    NEW_NERVE(RestartObjNrvAfter, RestartObj, After);
    NEW_NERVE(RestartObjNrvShake, RestartObj, Shake);
    NEW_NERVE(RestartObjNrvShakeAfter, RestartObj, ShakeAfter);
};  // namespace NrvRestartObj

namespace {
    static const TVec2f lbl_80729A08(12.0f, 10.0f);
};  // namespace

RestartObj::RestartObj(const char* pName) : LiveActor(pName), mIdInfo(), mConnector() {
}

void RestartObj::init(const JMapInfoIter& rIter) {
    MR::initActor(this, rIter, "RestartObj", false);
    s32 arg0 = -1;
    MR::getJMapInfoArg0NoInit(rIter, &arg0);
    mIdInfo = new JMapIdInfo(arg0, rIter);
    mConnector = new MapObjConnector(this);
    mYoshiTarget = MR::createYoshiLockOnTarget(this, MR::getJointMtx(this, "Pole3"), TVec3f(0.0f));
    changeTexture(*mIdInfo == *MR::getRestartMarioNo());

    if (*mIdInfo == *MR::getRestartMarioNo() && !GameSequenceFunction::isPadMode2()) {
        initNerve(GET_NERVE(RestartObj, RestartObjNrvAfter));
    } else {
        initNerve(GET_NERVE(RestartObj, RestartObjNrvBefore));
    }

    makeActorAppeared();
}

void RestartObj::exeBefore() {
    if (MR::isFirstStep(this)) {
        MR::startAction(this, "Before");
        MR::emitEffect(this, "Light");
    }

    if (!MR::isValidSwitchA(this) || MR::isOnSwitchA(this)) {
        MR::attachSupportTicoToTarget(this);
        YoshiFunction::tryYoshiEat(mYoshiTarget);
    }
}

void RestartObj::exeGet() {
    if (MR::isFirstStep(this)) {
        MR::tryRumblePadMiddle(this, WPAD_CHAN0);
        MR::setRestartMarioNo(*mIdInfo);
        GameSequenceFunction::collectTicoCoinIfSaved();
        MR::startAction(this, "Get");
        MR::startActionSound(this, "Get");
        changeTexture(true);
    }

    if (MR::isActionEnd(this)) {
        setNerve(GET_NERVE(RestartObj, RestartObjNrvAfter));
    }
}

void RestartObj::exeAfter() {
    if (MR::isFirstStep(this)) {
        MR::tryStartActionNotPlaying(this, "After");
    }
}

void RestartObj::exeShake() {
    if (MR::isFirstStep(this)) {
        MR::startAction(this, "Shake");
        MR::startActionSound(this, "Shake");
        MR::tryRumblePadWeak(this, WPAD_CHAN0);
    }

    if (MR::isActionEnd(this)) {
        setNerve(GET_NERVE(RestartObj, RestartObjNrvShakeAfter));
    }
}

void RestartObj::exeShakeAfter() {
    if (MR::isFirstStep(this)) {
        MR::tryStartActionNotPlaying(this, "After");
    }

    if (MR::isStep(this, 5)) {
        setNerve(GET_NERVE(RestartObj, RestartObjNrvAfter));
    }
}

void RestartObj::initAfterPlacement() {
    mConnector->attachToUnder();
}

void RestartObj::calcAndSetBaseMtx() {
    LiveActor::calcAndSetBaseMtx();
    mConnector->connect();
    MR::calcUpVec(&mGravity, this);
    mGravity.negate();
}

void RestartObj::updateHitSensor(HitSensor* pSensor) {
    TVec3f up(0.0f, 1.0f, 0.0f);
    MR::calcUpVec(&up, this);
    TVec3f above(0.0f, 0.0f, 0.0f);
    above.scaleAdd(400.0f, up, mPosition);
    MR::calcPerpendicFootToLineInside((TVec3f*)MR::getSensorPos2(pSensor), *MR::getPlayerPos(), mPosition, above);
}

void RestartObj::attackSensor(HitSensor* pSender, HitSensor* pReceiver) {
    if (MR::isPlayerInRush() || MR::isPlayerElementModeHopper()) {
        if (MR::isSensorPlayerOrRide(pReceiver) && !MR::isSensorGhost(pReceiver) && MR::isEqualSensor(pSender, this, "Body") &&
            isNerve(GET_NERVE(RestartObj, RestartObjNrvBefore)) && !isNerve(GET_NERVE(RestartObj, RestartObjNrvGet))) {
            setNerve(GET_NERVE(RestartObj, RestartObjNrvGet));
        }
    } else if (MR::isEqualSensor(pSender, this, "Shake")) {
        if (isNerve(GET_NERVE(RestartObj, RestartObjNrvShakeAfter))) {
            setNerve(GET_NERVE(RestartObj, RestartObjNrvShakeAfter));
        } else if (isNerve(GET_NERVE(RestartObj, RestartObjNrvAfter))) {
            setNerve(GET_NERVE(RestartObj, RestartObjNrvShake));
        }
    }
}

bool RestartObj::receiveMsgPlayerAttack(u32 msg, HitSensor* pSender, HitSensor* pReceiver) {
    if (isNerve(GET_NERVE(RestartObj, RestartObjNrvBefore)) && MR::isValidSwitchA(this) && !MR::isOnSwitchA(this)) {
        return false;
    }

    if (!MR::isEqualSensor(pReceiver, this, "Spin")) {
        return false;
    }

    if (isNerve(GET_NERVE(RestartObj, RestartObjNrvGet)) || isNerve(GET_NERVE(RestartObj, RestartObjNrvShake))) {
        return false;
    }

    if (MR::isMsgPlayerSpinAttackOrSupportTico(msg)) {
        if (isNerve(GET_NERVE(RestartObj, RestartObjNrvBefore))) {
            setNerve(GET_NERVE(RestartObj, RestartObjNrvGet));
        } else {
            setNerve(GET_NERVE(RestartObj, RestartObjNrvShake));
        }

        return true;
    }

    return false;
}

bool RestartObj::receiveOtherMsg(u32 msg, HitSensor* pSender, HitSensor* pReceiver) {
    if (!MR::isSensorPlayerOrRide(pSender)) {
        return false;
    }

    if (!isNerve(GET_NERVE(RestartObj, RestartObjNrvBefore))) {
        return false;
    }

    if (isNerve(GET_NERVE(RestartObj, RestartObjNrvBefore)) && MR::isValidSwitchA(this) && !MR::isOnSwitchA(this)) {
        return false;
    }

    if (MR::isEqualSensor(pReceiver, this, "Body") && MR::isMsgPlayerKick(msg)) {
        setNerve(GET_NERVE(RestartObj, RestartObjNrvGet));
        return true;
    }

    if (MR::isMsgYoshiStartTongue(msg)) {
        setNerve(GET_NERVE(RestartObj, RestartObjNrvGet));
        return false;
    }

    return false;
}

void RestartObj::changeTexture(bool isGet) {
    f32 frame = 0.0f;

    if (isGet) {
        if (MR::isPlayerLuigi()) {
            frame = 2.0f;
        } else {
            frame = 1.0f;
        }
    }

    MR::startBtpAndSetFrameAndStop(this, "Change", frame);
}
