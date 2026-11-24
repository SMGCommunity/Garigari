#include "Game/Enemy/FireBall.hpp"
#include "Game/Enemy/AnimScaleController.hpp"
#include "Game/Enemy/WalkerStateBindStarPointer.hpp"
#include "Game/LiveActor/LiveActor.hpp"
#include "Game/LiveActor/Nerve.hpp"
#include "Game/Util/ActionSoundUtil.hpp"
#include "Game/Util/ActorAnimUtil.hpp"
#include "Game/Util/ActorInitUtil.hpp"
#include "Game/Util/ActorMovementUtil.hpp"
#include "Game/Util/ActorSensorUtil.hpp"
#include "Game/Util/ActorStateUtil.hpp"
#include "Game/Util/Color.hpp"
#include "Game/Util/EffectUtil.hpp"
#include "Game/Util/LiveActorUtil.hpp"
#include "Game/Util/MathUtil.hpp"
#include "Game/Util/MtxUtil.hpp"
#include "Game/Util/ObjUtil.hpp"
#include "Game/Util/PlayerUtil.hpp"
#include "Game/Util/SoundUtil.hpp"

extern "C" void fn_8003E340(TVec3f*, const TVec3f&, const TVec3f&, f32, f32);

namespace FireBallSpread {
    void fn_8017DF50(FireBall*);
}

namespace {
    const f32 cForceKillDistance = 7000.0f;
    const f32 cThrowOffsetY = 120.0f;
    const f32 cReflectSpeed = 100.0f;
    const f32 cReflectReduceRate = 0.96f;
    const s32 cReflectFrame = 30;
    const s32 cReflectInvalidFrame = 60;
    const GXColor cColor = {255, 192, 0, 255};
};  // namespace

namespace NrvFireBall {
    NEW_NERVE(FireBallNrvThrow, FireBall, Throw);
    NEW_NERVE(FireBallNrvFreeze, FireBall, Freeze);
    NEW_NERVE(FireBallNrvReflect, FireBall, Reflect);
};  // namespace NrvFireBall

FireBall::FireBall(const char* pName)
    : LiveActor(pName), mHost(), mScaleController(), mWalkerStateBindStarPointer(), _9C(0.0f, 1.0f, 0.0f), _A8(0.0f, 1.0f, 0.0f), _B4(1.0f) {
}

void FireBall::init(const JMapInfoIter& rIter) {
    MR::initActor(this, "FireBall", false);

    MR::invalidateClipping(this);

    initNerve(GET_NERVE(FireBall, FireBallNrvThrow), 1);

    mScaleController = new AnimScaleController(nullptr);
    mWalkerStateBindStarPointer = new WalkerStateBindStarPointer(this, mScaleController);

    MR::initActorState(this, mWalkerStateBindStarPointer, GET_NERVE(FireBall, FireBallNrvFreeze), "SupportFreeze");

    makeActorDead();
}

void FireBall::appear() {
    LiveActor::appear();
    setNerve(GET_NERVE(FireBall, FireBallNrvThrow));
}

void FireBall::kill() {
    MR::forceDeleteEffect(this, "FireBall");
    MR::emitEffect(this, "FireBallBreak");

    MR::startActionSound(this, "OjFireBallBreak");

    LiveActor::kill();
}

void FireBall::appearAndThrow(const TVec3f& rPos, f32 f1, f32 f2) {
    mPosition.set(rPos);

    MR::calcGravity(this);
    _A8.negate(mGravity);

    setVelocityToPlayer(f1);

    TPos3f mtx;
    mtx.makeRotate(_A8, f2);
    mtx.mult33(mVelocity, mVelocity);

    appear();
}

void FireBall::fn_8017DA20(const TVec3f& rPos, const TVec3f& rVel) {
    mPosition.set(rPos);

    MR::calcGravity(this);
    _A8.negate(mGravity);

    mVelocity.set(rVel);

    appear();
}

// void FireBall::control() {}

void FireBall::calcAndSetBaseMtx() {
    if (MR::isNearZero(mVelocity)) {
        return;
    }

    TVec3f dir;
    MR::normalize(&dir, mVelocity);

    TPos3f baseMtx;
    if (MR::isSameDirection(dir, _A8)) {
        MR::makeMtxFrontNoSupportPos(&baseMtx, dir, mPosition);
    } else {
        MR::makeMtxFrontUpPos(&baseMtx, dir, _A8, mPosition);
    }

    MR::setBaseTRMtx(this, baseMtx);
}

void FireBall::attackSensor(HitSensor* pSender, HitSensor* pReceiver) {
    if (MR::isSensorPlayer(pReceiver) && MR::sendMsgEnemyAttackFire(pReceiver, pSender)) {
        kill();
        return;
    }

    if (MR::isSensorEnemy(pReceiver) && MR::getSensorHost(pReceiver) != mHost && MR::sendMsgEnemyAttackFire(pReceiver, pSender)) {
        kill();
    }
}

bool FireBall::receiveMsgPlayerAttack(u32 msg, HitSensor* pSender, HitSensor* pReceiver) {
    if (MR::isMsgJetTurtleAttack(msg)) {
        kill();
        return false;
    }

    if (MR::isMsgSupportTicoSpin(msg)) {
        if (isNerve(GET_NERVE(FireBall, FireBallNrvThrow)) || isNerve(GET_NERVE(FireBall, FireBallNrvFreeze))) {
            FireBallSpread::fn_8017DF50(this);  // FIXME

            setNerve(GET_NERVE(FireBall, FireBallNrvReflect));

            return true;
        }

        return false;
    }

    if (MR::isMsgLockOnStarPieceShoot(msg)) {
        return true;
    }

    if (MR::isMsgStarPieceAttack(msg)) {
        kill();
        return true;
    }

    return false;
}

HitSensor* FireBall::isBindedAny() const {
    if (MR::isBindedGround(this)) {
        return MR::getGroundSensor(this);
    }

    if (MR::isBindedWall(this)) {
        return MR::getWallSensor(this);
    }

    if (MR::isBindedRoof(this)) {
        return MR::getRoofSensor(this);
    }

    return nullptr;
}

bool FireBall::tryToKill() {
    HitSensor* bindedSensor = isBindedAny();
    if (bindedSensor != nullptr) {
        MR::sendMsgEnemyAttack(bindedSensor, getSensor("Body"));

        kill();

        return true;
    }

    if (!MR::isNearPlayer(this, ::cForceKillDistance)) {
        kill();
        return true;
    }

    return false;
}

void FireBall::setVelocityToPlayer(f32 f1) {
    TVec3f vec;
    vec.scale(::cThrowOffsetY, _A8);

    TVec3f diff(vec);
    diff.add(*MR::getPlayerPos());
    diff.sub(mPosition);

    MR::normalize(&diff);
    mVelocity.scale(f1, diff);
}

void FireBallSpread::fn_8017DF50(FireBall* pFireBall) {
    if (MR::isNearZero(pFireBall->_9C)) {
        pFireBall->_9C.set(pFireBall->_A8);
    }

    fn_8003E340(&pFireBall->mVelocity, pFireBall->_A8, pFireBall->_9C, -20.0f, 20.0f);
    pFireBall->mVelocity *= ::cReflectSpeed;
}

void FireBall::exeThrow() {
    if (MR::isFirstStep(this)) {
        MR::startAction(this, "Spin");
    }

    if (MR::changeShowModelFlagSyncNearClipping(this, 200.0f)) {
        MR::emitEffect(this, "FireBall");
    } else {
        MR::deleteEffect(this, "FireBall");
    }

    MR::startActionSound(this, "Fly");

    if (MR::isGreaterStep(this, ::cReflectFrame) && mWalkerStateBindStarPointer->tryStartPointBind()) {
        _9C = mVelocity;

        setNerve(GET_NERVE(FireBall, FireBallNrvFreeze));

        return;
    }

    if (tryToKill()) {
        return;
    }
}

void FireBall::exeFreeze() {
    if (MR::updateActorStateAndNextNerve(this, GET_NERVE(FireBall, FireBallNrvThrow))) {
        mVelocity = _9C;
    }
}

void FireBall::exeReflect() {
    if (MR::isFirstStep(this)) {
        MR::start2PAttackAssistSound();
        MR::startActionSound(this, "EmFireBubbleReflect");
    }

    mVelocity.mult(::cReflectReduceRate);

    if (!tryToKill() && MR::isStep(this, ::cReflectInvalidFrame)) {
        kill();
    }
}
