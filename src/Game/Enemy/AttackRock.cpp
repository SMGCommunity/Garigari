#include "Game/Enemy/AttackRock.hpp"
#include "Game/Enemy/AttackRockUtil.hpp"
#include "Game/Enemy/ATTACK_ROCK_TEMP.hpp"
#include "Game/LiveActor/BreakModel.hpp"
#include "Game/LiveActor/HitSensor.hpp"
#include "Game/LiveActor/ModelObj.hpp"
#include "Game/LiveActor/Nerve.hpp"
#include "Game/Util/ActionSoundUtil.hpp"
#include "Game/Util/ActorAnimUtil.hpp"
#include "Game/Util/ActorInitUtil.hpp"
#include "Game/Util/ActorMovementUtil.hpp"
#include "Game/Util/ActorSensorUtil.hpp"
#include "Game/Util/ActorShadowUtil.hpp"
#include "Game/Util/ActorStateUtil.hpp"
#include "Game/Util/BaseMatrixFollowTargetHolder.hpp"
#include "Game/Util/EffectUtil.hpp"
#include "Game/Util/JMapUtil.hpp"
#include "Game/Util/LiveActorUtil.hpp"
#include "Game/Util/MathUtil.hpp"
#include "Game/Util/PlayerUtil.hpp"
#include <decomp.h>

EXTERN_UNKNOWN_FUNC(void, 800CAF80, TVec3f*, const TVec3f&)
EXTERN_UNKNOWN_FUNC(void, 800CAFE0, TVec3f*, const TVec3f&)
EXTERN_UNKNOWN_FUNC(void, 800CB710, HitSensor*)
EXTERN_UNKNOWN_FUNC(void, 800CB090, TVec3f&)
EXTERN_UNKNOWN_FUNC(f32, 800CB410, TVec3f&)
EXTERN_UNKNOWN_FUNC(void, 800CB6D0, TVec3f&)
EXTERN_UNKNOWN_FUNC(void, 800CB710, HitSensor*)
EXTERN_UNKNOWN_FUNC(bool, 800CC1F0, HitSensor*, HitSensor*)
EXTERN_UNKNOWN_FUNC(void, 800CC210, HitSensor*, HitSensor*)
EXTERN_UNKNOWN_FUNC(void, 800CC220, LiveActor*, HitSensor*)
EXTERN_UNKNOWN_FUNC(bool, 800CC230, LiveActor*, HitSensor*)
EXTERN_UNKNOWN_FUNC(bool, 800CC270, u32)
EXTERN_UNKNOWN_FUNC(bool, 800CC280, u32)
EXTERN_UNKNOWN_FUNC(bool, 800CC290, u32)
EXTERN_UNKNOWN_FUNC(ProjmapEffectMtxSetter*, 80155660, LiveActor*)
EXTERN_UNKNOWN_FUNC(void, 801552A0, LiveActor*)
EXTERN_UNKNOWN_FUNC(bool, 80153400, void*);
EXTERN_UNKNOWN_FUNC(bool, 80153460, void*);
EXTERN_UNKNOWN_FUNC(void, 80155360, TVec3f&, TQuat4f&, HitSensor*, HitSensor*, f32)
EXTERN_UNKNOWN_FUNC(void, 801554D0, TPos3f&, LiveActor*)
EXTERN_UNKNOWN_FUNC(void, 80155540, ProjmapEffectMtxSetter*, TQuat4f&, TVec3f&)

namespace NrvAttackRock {
    NEW_NERVE(AttackRockFall, AttackRock, Fall);
    NEW_NERVE(AttackRockWait, AttackRock, Wait);
    NEW_NERVE(AttackRockFloat, AttackRock, Float);
    NEW_NERVE(AttackRockAttack, AttackRock, Attack);
    NEW_NERVE(AttackRockBreak, AttackRock, Break);
};  // namespace NrvAttackRock

AttackRock::AttackRock(const char* pName)
    : LiveActor(pName), _F0(0.0f, 0.0f, 0.0f, 1.0f), _100(0.0f, 0.0f, 0.0f, 1.0f), mBreakModel(), mDemoObj(), _118(), mFightNo(1), _128() {
    _90.identity();
    _C0.identity();
    _100.set(0.0f, 0.0f, 0.0f, 1.0f);
}

void AttackRock::init(const JMapInfoIter& rIter) {
    MR::initActor(this, rIter, "AttackRock", true);
    MR::makeQuatFromRotate(&_F0, this);
    _118 = AttackRockUtil::createProjMapEffectMtxSetter(this);
    MR::setEffectHostMtx(this, "Attack", _C0);
    fn_800CB710(getSensor("Body"));
    MR::addBaseMatrixFollowTarget(this, rIter, nullptr, MR::createBaseMatrixFollowValidateDelegator(this, &AttackRock::isValidFollow));
    AttackRockUtil::initAttackRockBinder(this);
    MR::excludeCalcShadowToMyCollision(this, nullptr);
    mBreakModel = MR::createBreakModel(this, getBaseMtx());
    mDemoObj = MR::createDemoObj("盛り土モデル", "AttackRockHill", nullptr);
    mDemoObj->makeActorDead();
    mFightNo = 1;
    MR::getJMapInfoArg0WithInit(rIter, &mFightNo);
    if (mFightNo < 1) {
        mFightNo = 1;
    }

    initNerve(GET_NERVE(AttackRock, AttackRockWait), 2);
    // MR::initActorState(this, ActorStateBaseInterface *pActorState, GET_NERVE(AttackRock, AttackRockFall), "KoopaFall");
    // MR::initActorState(this, ActorStateBaseInterface *pActorState, GET_NERVE(AttackRock, AttackRockFloat), "Float");
    MR::invalidateClipping(this);
    makeActorDead();
}

void AttackRock::makeActorAppeared() {
    LiveActor::makeActorAppeared();
}

void AttackRock::makeActorDead() {
    LiveActor::makeActorDead();
    mDemoObj->makeActorDead();
}

void AttackRock::control() {
    if (MR::isOnGroundPlayer()) {
        if (MR::isActorOnPlayer(this)) {
            _128 = true;
        } else {
            _128 = false;
        }
    }

    AttackRockUtil::updateEffectMtx(&_C0, this);
}

void AttackRock::calcAndSetBaseMtx() {
    MR::setBaseTRMtx(this, _F0);
    AttackRockUtil::updateProjMapEffectMtx(_118, _100, mPosition);
}

void AttackRock::attackSensor(HitSensor* pSender, HitSensor* pReceiver) {
    if (MR::isSensorEnemy(pReceiver) && MR::isEqualSensor(pSender, this, "Body") && isNerve(GET_NERVE(AttackRock, AttackRockAttack))) {
        fn_800CC210(pReceiver, pSender);
        if (fn_800CC1F0(pReceiver, pSender)) {
            setBreak();
            return;
        }
    }

    if (isNerve(GET_NERVE(AttackRock, AttackRockFall))) {
        // TODO: some virtual function on _11C
    }
}

f32 AttackRock::getUnkf32() {
    return 300.0f;
}

bool AttackRock::innerOrOuter() {
    if (isNerve(GET_NERVE(AttackRock, AttackRockFall)) || isNerve(GET_NERVE(AttackRock, AttackRockWait))) {
        return true;
    }

    if (isNerve(GET_NERVE(AttackRock, AttackRockFloat)) && !fn_80153400(_120)) {
        return true;
    }

    return false;
}

void AttackRock::setBreak() {
    const char* brkName;
    if (innerOrOuter()) {
        brkName = "Outer";
    } else {
        brkName = "Inner";
    }

    MR::startBrk(mBreakModel, brkName);
    setNerve(GET_NERVE(AttackRock, AttackRockBreak));
}

bool AttackRock::receiveMsgPlayerAttack(u32 msg, HitSensor* pSender, HitSensor* pReceiver) {
    if (MR::isMsgPlayerHipDropFloor(msg) && isNerve(GET_NERVE(AttackRock, AttackRockFloat)) && fn_80153400(_120)) {
        AttackRockUtil::startAttack(&mVelocity, _100, pSender, pReceiver, 120.0f);
        setNerve(GET_NERVE(AttackRock, AttackRockAttack));
        return true;
    }

    return false;
}

bool AttackRock::receiveOtherMsg(u32 msg, HitSensor* pSender, HitSensor* pReceiver) {
    if (MR::isMsgKoopaCastAttackRockStart(msg)) {
        if (MR::isDead(this)) {
            fn_800CB090(mPosition);
            MR::resetPosition(this);
            MR::zeroVelocity(this);
            setNerve(GET_NERVE(AttackRock, AttackRockFall));
            MR::offBind(this);
            MR::hideModel(this);
            appear();
            return true;
        } else {
            return false;
        }
    }

    if (fn_800CC270(msg)) {
        return !MR::isDead(this);
    }

    if (fn_800CC280(msg)) {
        // TODO: virtual function call of _11C
        // virtual function call of _120
        mBreakModel->makeActorDead();
        mDemoObj->makeActorDead();
        makeActorDead();
        return true;
    }

    if (fn_800CC290(msg) && isNerve(GET_NERVE(AttackRock, AttackRockFall))) {
        setBreak();
        return true;
    }

    if (isNerve(GET_NERVE(AttackRock, AttackRockFall))) {
        // TODO: virtual function call of _11C
        // dummy, actually returns result of function call
        return true;
    }

    if (isNerve(GET_NERVE(AttackRock, AttackRockFloat))) {
        // TODO: virtual function call of _120
        // dummy, actually returns result of function call
        return true;
    }

    if (MR::isMsgKoopaPunchAttack(msg) && MR::isEqualSensor(pSender, this, "Body") && !isNerve(GET_NERVE(AttackRock, AttackRockBreak))) {
        fn_800CB6D0(mPosition);
        setBreak();
        return true;
    }

    if (MR::isMsgKoopaReleaseAttackRock(msg) && isNerve(GET_NERVE(AttackRock, AttackRockWait))) {
        setNerve(GET_NERVE(AttackRock, AttackRockFloat));
        return true;
    }

    return false;
}

void AttackRock::exeFall() {
    MR::startActionSound(this, "PgFall");
    MR::updateActorStateAndNextNerve(this, GET_NERVE(AttackRock, AttackRockWait));
}

void AttackRock::exeWait() {
    if (MR::isFirstStep(this)) {
        MR::startAction(this, "Wait");
        MR::invalidateShadow(this, nullptr);
    }
}

void AttackRock::exeFloat() {
    if (MR::updateActorState(this)) {
        kill();
    }
}

void AttackRock::exeAttack() {
    if (MR::isFirstStep(this)) {
        MR::startAction(this, "Attack");
        MR::onBind(this);
        MR::invalidateCollisionParts(this);
    }

    if (MR::isBinded(this)) {
        fn_800CC220(this, getSensor("Body"));
        if (!fn_800CC230(this, getSensor("Body"))) {
            fn_800CB6D0(mPosition);
            setBreak();
            return;
        }
    }

    f32 f1 = fn_800CB410(mPosition);

    MR::setShadowVolumeSphereRadius(this, nullptr, MR::getLinerValueFromMinMax(f1, 700.0f, 2100.0f, 285.0f * mScale.y, 15.0f * mScale.y));

    TVec3f vec1;
    fn_800CAF80(&vec1, mPosition);
    TVec3f vec2;
    fn_800CAFE0(&vec2, mPosition);

    MR::setShadowProjection(this, nullptr, vec2, vec1, f1 < 2100.0f);
    if (MR::reboundVelocityFromCollision(this, 0.8f, 0.0f, 1.0f)) {
        MR::emitEffectHit(this, MR::getBindedHitPos(this), MR::getBindedFixReactionVector(this), "GroundHit");
        MR::startActionSound(this, "Bound");
        MR::attenuateVelocity(this, 0.7f);
    }

    if (MR::isGreaterStep(this, 120)) {
        setBreak();
    }
}

void AttackRock::exeBreak() {
    if (MR::isFirstStep(this)) {
        MR::startAction(this, "Break");
        mBreakModel->appear();
        mDemoObj->kill();
        MR::invalidateCollisionParts(this);
        MR::invalidateHitSensors(this);
        MR::invalidateShadow(this, nullptr);
        MR::zeroVelocity(this);
    }

    if (MR::isStep(this, 1)) {
        MR::hideModelAndOnCalcAnim(this);
    }

    if (MR::isGreaterStep(this, 10)) {
        kill();
    }
}

bool AttackRock::isValidFollow(s32 id) const {
    if (isNerve(GET_NERVE(AttackRock, AttackRockWait))) {
        return id != 0;
    }

    if (isNerve(GET_NERVE(AttackRock, AttackRockFloat))) {
        if (id == 0 && !_128) {
            return false;
        }

        return fn_80153460(_120);
    }

    return false;
}
