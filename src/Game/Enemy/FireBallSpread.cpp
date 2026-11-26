#include "Game/Enemy/FireBallSpread.hpp"
#include "Game/Enemy/AnimScaleController.hpp"
#include "Game/Enemy/FireBallSpreadLava.hpp"
#include "Game/Enemy/WalkerStateBindStarPointer.hpp"
#include "Game/LiveActor/Nerve.hpp"
#include "Game/Map/HitInfo.hpp"
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

extern "C" void fn_80038020(TVec3f*, Triangle*, const TVec3f&, const TVec3f&, u32);
extern "C" void fn_8003E340(TVec3f*, const TVec3f&, const TVec3f&, f32, f32);

namespace {
    const GXColor cColor = {255, 192, 0, 255};
};

namespace NrvFireBallSpread {
    NEW_NERVE(FireBallSpreadNrvThrow, FireBallSpread, Throw);
    NEW_NERVE(FireBallSpreadNrvFreeze, FireBallSpread, Freeze);
    NEW_NERVE(FireBallSpreadNrvReflect, FireBallSpread, Reflect);
};  // namespace NrvFireBallSpread

FireBallSpread::FireBallSpread(const char* pName)
    : LiveActor(pName), mHost(), mScaleController(), mWalkerStateBindStarPointer(), _9C(0.0f, 1.0f, 0.0f), _A8(0.0f, 1.0f, 0.0f), _B4(1.0f), mTimer(),
      mIsFalling() {
}

void FireBallSpread::init(const JMapInfoIter& rIter) {
    MR::initActor(this, "FireBall", "Spread", false);

    MR::invalidateClipping(this);

    mLava = new FireBallSpreadLava(this, "拡散溶岩");
    mLava->initWithoutIter();

    initNerve(GET_NERVE(FireBallSpread, FireBallSpreadNrvThrow), 1);

    mScaleController = new AnimScaleController(nullptr);
    mWalkerStateBindStarPointer = new WalkerStateBindStarPointer(this, mScaleController);

    MR::initActorState(this, mWalkerStateBindStarPointer, GET_NERVE(FireBallSpread, FireBallSpreadNrvFreeze), "SupportFreeze");

    makeActorDead();
}

void FireBallSpread::appear() {
    LiveActor::appear();

    mTimer = 60;

    setNerve(GET_NERVE(FireBallSpread, FireBallSpreadNrvThrow));
}

void FireBallSpread::kill() {
    mIsFalling = false;

    MR::forceDeleteEffect(this, "FireBallSpread");
    MR::emitEffect(this, "FireBallSpreadBreak");

    MR::startActionSound(this, "OjFireBallBreak");

    LiveActor::kill();
}

void FireBallSpread::appearAndThrow(const TVec3f& rPos, f32 f1, f32 f2) {
    mPosition.set(rPos);

    MR::calcGravity(this);

    _9C.negate(mGravity);

    setVelocityToPlayer(f1);

    TPos3f mtx;
    mtx.makeRotate(_9C, MR::toRadian(f2));
    mtx.mult33(mVelocity, mVelocity);

    appear();
}

void FireBallSpread::fn_8017E660(const TVec3f& rPos, const TVec3f& rVel) {
    mPosition.set(rPos);

    MR::calcGravity(this);

    _9C.negate(mGravity);

    mVelocity.set(rVel);

    appear();
}

void FireBallSpread::fn_8017E6D0(const TVec3f& rPos, const TVec3f& rVel) {
    mPosition.set(rPos);

    MR::calcGravity(this);

    _9C.negate(mGravity);

    mVelocity.set(rVel);

    mIsFalling = true;

    appear();
}

bool FireBallSpread::fn_8017E750() const {
    return MR::isDead(this) && MR::isDead(mLava);
}

bool FireBallSpread::fn_8017E7B0() {
    if (!MR::isDead(mLava)) {
        mLava->kill();
        return true;
    }

    return false;
}

void FireBallSpread::control() {
    if (mTimer > 0) {
        mTimer--;
    }

    // MR::requestPointLight(this, mPosition, ::cColor);
}

void FireBallSpread::calcAndSetBaseMtx() {
    if (MR::isNearZero(mVelocity)) {
        return;
    }

    TVec3f dir;
    MR::normalize(&dir, mVelocity);

    TPos3f baseMtx;
    if (MR::isSameDirection(dir, _9C)) {
        MR::makeMtxFrontNoSupportPos(&baseMtx, dir, mPosition);
    } else {
        MR::makeMtxFrontUpPos(&baseMtx, dir, _9C, mPosition);
    }

    MR::setBaseTRMtx(this, baseMtx);
}

void FireBallSpread::attackSensor(HitSensor* pSender, HitSensor* pReceiver) {
    if (MR::isSensorPlayer(pReceiver) && MR::sendMsgEnemyAttackFire(pReceiver, pSender)) {
        kill();
        return;
    }

    if (MR::isSensorEnemy(pReceiver) && MR::getSensorHost(pReceiver) != mHost && MR::sendMsgEnemyAttackFire(pReceiver, pSender)) {
        kill();
    }
}

bool FireBallSpread::receiveMsgPlayerAttack(u32 msg, HitSensor* pSender, HitSensor* pReceiver) {
    if (MR::isMsgJetTurtleAttack(msg)) {
        kill();
        return false;
    }

    if (MR::isMsgSupportTicoSpin(msg)) {
        if (isNerve(GET_NERVE(FireBallSpread, FireBallSpreadNrvThrow)) || isNerve(GET_NERVE(FireBallSpread, FireBallSpreadNrvFreeze))) {
            fn_8017EDF0();

            setNerve(GET_NERVE(FireBallSpread, FireBallSpreadNrvReflect));

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

bool FireBallSpread::receiveMsgEnemyAttack(u32 msg, HitSensor* pSender, HitSensor* pReceiver) {
    if (mHost == nullptr) {
        return false;
    }

    if (MR::getSensorHost(pSender) != mHost) {
        return false;
    }

    if (mTimer > 0) {
        return false;
    }

    kill();

    return true;
}

HitSensor* FireBallSpread::isBindedAny() const {
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

bool FireBallSpread::tryToKill() {
    HitSensor* bindedSensor = isBindedAny();
    if (bindedSensor != nullptr) {
        MR::sendMsgEnemyAttack(bindedSensor, getSensor("Body"));

        MR::calcGravity(this);

        TVec3f vec(mPosition);
        Triangle triangle = Triangle();
        fn_80038020(&vec, &triangle, mPosition, mGravity * 300.0f, 24);

        mLava->appearLava(vec);

        kill();

        return true;
    }

    if (!MR::isNearPlayer(this, 7000.0f)) {
        kill();
        return true;
    }

    return false;
}

void FireBallSpread::setVelocityToPlayer(f32 f1) {
    TVec3f vec;
    vec.scale(120.0f, _9C);

    vec.add(*MR::getPlayerPos());
    vec.sub(mPosition);

    MR::normalize(&vec);
    mVelocity.scale(f1, vec);
}

void FireBallSpread::fn_8017EDF0() {
    if (MR::isNearZero(_A8)) {
        _A8.set(_9C);
    }

    fn_8003E340(&mVelocity, _9C, _A8, -20.0f, 20.0f);
    mVelocity.mult(100.0f);
}

void FireBallSpread::exeThrow() {
    if (MR::isFirstStep(this)) {
        MR::startAction(this, "Spin");
    }

    if (MR::changeShowModelFlagSyncNearClipping(this, 200.0f)) {
        MR::emitEffect(this, "FireBallSpread");
    } else {
        MR::deleteEffect(this, "FireBallSpread");
    }

    if (mIsFalling) {
        MR::startActionSound(this, "Fall");
    } else {
        MR::startActionSound(this, "Fly");
    }

    if (MR::isGreaterStep(this, 30) && mWalkerStateBindStarPointer->tryStartPointBind()) {
        _A8 = mVelocity;

        setNerve(GET_NERVE(FireBallSpread, FireBallSpreadNrvFreeze));

        return;
    }

    if (tryToKill()) {
        return;
    }
}

void FireBallSpread::exeFreeze() {
    if (MR::updateActorStateAndNextNerve(this, GET_NERVE(FireBallSpread, FireBallSpreadNrvThrow))) {
        mVelocity = _A8;
    }
}

void FireBallSpread::exeReflect() {
    if (MR::isFirstStep(this)) {
        MR::start2PAttackAssistSound();
        MR::startActionSound(this, "EmFireBubbleReflect");
    }

    mVelocity.mult(0.96f);

    if (!tryToKill() && MR::isStep(this, 60)) {
        kill();
    }
}
