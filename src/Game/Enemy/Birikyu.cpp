#include "Game/Enemy/Birikyu.hpp"
#include "Game/LiveActor/Nerve.hpp"
#include "Game/Util/ActionSoundUtil.hpp"
#include "Game/Util/ActorInitUtil.hpp"
#include "Game/Util/ActorSensorUtil.hpp"
#include "Game/Util/ActorShadowUtil.hpp"
#include "Game/Util/EffectUtil.hpp"
#include "Game/Util/JMapUtil.hpp"
#include "Game/Util/LiveActorUtil.hpp"
#include "Game/Util/MathUtil.hpp"
#include "Game/Util/MtxUtil.hpp"
#include "Game/Util/RailUtil.hpp"
#include "Game/Util/SoundUtil.hpp"

namespace {
    static const s32 sAttackTime = 90;
    static const f32 sMoveRadius = 400.0f;
    static const f32 sMoveSpeedDefault = 10.0f;
};  // namespace

namespace NrvBirikyu {
    NEW_NERVE(HostTypeNrvMove, Birikyu, Move);
    NEW_NERVE(HostTypeNrvMoveCircle, Birikyu, MoveCircle);
    NEW_NERVE(HostTypeNrvAttack, Birikyu, Attack);
    NEW_NERVE(HostTypeNrvAttackWait, Birikyu, AttackWait);
    NEW_NERVE(HostTypeNrvWaitAtEdge, Birikyu, WaitAtEdge);
    NEW_NERVE(HostTypeNrvStopPointing, Birikyu, StopPointing);
    NEW_NERVE(HostTypeNrvKill, Birikyu, Kill);
};  // namespace NrvBirikyu

Birikyu::Birikyu(const char* pName)
    : LiveActor(pName), mObjectName(), _90(), mRailClipCenter(gZeroVec), mOrbitCenter(gZeroVec), mHasShadow(), mIsConnected(), mUp(0.0f, 1.0f, 0.0f),
      mFront(0.0f, 0.0f, 1.0f), mOrbitAngle(), mMoveSpeed(::sMoveSpeedDefault) {
}

void Birikyu::init(const JMapInfoIter& rIter) {
    MR::getObjectName(&mObjectName, rIter);
    /*     initModelManagerWithAnm(mObjectName, nullptr, "test", false);
        MR::connectToSceneEnemy(this); */
    MR::initActor(this, rIter, _90, false);
    initFromJmpArgs(rIter);
    initRail(rIter);
    MR::invalidateShadowAll(this);
    MR::joinToGroupArray(this, rIter, nullptr, 64);
    // ActorStateParamScale actorStateParamScale = new ActorStateParamScale(this);
    // actorStateParamScale.init(rIter);

    initNerve(&NrvBirikyu::HostTypeNrvMove::sInstance);

    if (mIsConnected) {
        initNerve(GET_NERVE(Birikyu, HostTypeNrvMove));
    } else {
        initNerve(GET_NERVE(Birikyu, HostTypeNrvMoveCircle));
    }

    appear();
}

void Birikyu::initAfterPlacement() {
    if (!mIsConnected) {
        return MR::moveCoordAndTransToNearestRailPos(this);
    }

    mOrbitCenter.set(mPosition);
    TPos3f matrix;
    matrix.identity();
    MR::makeMtxRotate(matrix, mRotation);
    matrix.getYDir(mUp);
    MR::normalize(&mUp);
    matrix.getZDir(mFront);
    MR::normalize(&mFront);
    MR::setPosition(this, mOrbitCenter + mFront * ::sMoveRadius);
}

void Birikyu::appear() {
    LiveActor::appear();
    MR::emitEffect(this, mObjectName);
}

void Birikyu::control() {
    // Requires ActorStateParamScale
}

void Birikyu::movement() {
    // Requires ActorStateParamScale
}

void Birikyu::attackSensor(HitSensor* pSender, HitSensor* pReceiver) {
    if (MR::isSensorPlayerOrYoshiOrRide(pReceiver) || MR::isSensorEnemy(pReceiver)) {
        if (MR::sendMsgEnemyAttackElectric(pReceiver, pSender)) {
            if (LiveActor::isNerve(&NrvBirikyu::HostTypeNrvStopPointing::sInstance)) {
                return;
            }

            MR::sendMsgToGroupMember(ACTMES_GROUP_MOVE_STOP, this, getSensor("Body"), "Body");
            setNerve(GET_NERVE(Birikyu, HostTypeNrvAttack));
        } else {
            MR::sendMsgPush(pReceiver, pSender);
        }
    }
}

bool Birikyu::receiveMsgPlayerAttack(u32 msg, HitSensor* pSender, HitSensor* pReceiver) {
    if (MR::isMsgStarPieceReflect(msg)) {
        return true;
    }

    if (MR::isMsgInvincibleAttack(msg) && !isNerve(&NrvBirikyu::HostTypeNrvKill::sInstance)) {
        setNerve(&NrvBirikyu::HostTypeNrvKill::sInstance);
        return true;
    }

    return false;
}

bool Birikyu::receiveOtherMsg(u32 msg, HitSensor* pSender, HitSensor* pReceiver) {
    if (msg == ACTMES_GROUP_MOVE_STOP && MR::getSensorHost(pSender) != this) {
        bool isMoving = isNerve(GET_NERVE(Birikyu, HostTypeNrvMove)) || isNerve(GET_NERVE(Birikyu, HostTypeNrvMoveCircle));

        if (isMoving) {
            setNerve(GET_NERVE(Birikyu, HostTypeNrvAttackWait));
            return true;
        }
    }

    if (msg == ACTMES_GROUP_MOVE_START && MR::getSensorHost(pSender) != this) {
        bool isMoving = isNerve(GET_NERVE(Birikyu, HostTypeNrvMove)) || isNerve(GET_NERVE(Birikyu, HostTypeNrvMoveCircle));

        if (!isMoving) {
            goMove();
            return true;
        }
    }

    return false;
}

void Birikyu::startClipped() {
    LiveActor::startClipped();
    MR::forceDeleteEffect(this, mObjectName);
}

void Birikyu::endClipped() {
    LiveActor::endClipped();
    MR::emitEffect(this, mObjectName);
}

void Birikyu::initFromJmpArgs(const JMapInfoIter& rIter) {
    MR::getJMapInfoArg0NoInit(rIter, &mMoveSpeed);
    s32 num = -1;
    MR::getJMapInfoArg2NoInit(rIter, &num);
    mHasShadow = num == true;
}

void Birikyu::initRail(const JMapInfoIter& rIter) {
    mIsConnected = MR::isConnectedWithRail(rIter);

    if (mIsConnected) {
        MR::initAndSetRailClipping(&mRailClipCenter, this, 100.0f, 500.0f);
    }
}

bool Birikyu::tryStopPointing() {
    // if (MR::isStarPointerPointing2PAttachTarget(this)) {
    MR::sendMsgToGroupMember(ACTMES_GROUP_MOVE_STOP, this, getSensor("Body"), "Body");
    setNerve(GET_NERVE(Birikyu, HostTypeNrvStopPointing));

    return true;
    //}

    return false;
}

void Birikyu::goMove() {
    if (mIsConnected) {
        setNerve(GET_NERVE(Birikyu, HostTypeNrvMove));
    } else {
        setNerve(GET_NERVE(Birikyu, HostTypeNrvMoveCircle));
    }
}

void Birikyu::endStopPointing() {
    if (MR::isRegisteredEffect(this, "Touch")) {
        MR::deleteEffect(this, "Touch");
    }

    MR::sendMsgToGroupMember(ACTMES_GROUP_MOVE_START, this, getSensor("Body"), "Body");
}

void Birikyu::exeMove() {
    MR::startActionSound(this, "OjLvBirikyuMove");

    if (tryStopPointing()) {
        return;
    }

    if (MR::isRailReachedGoal(this)) {
        MR::reverseRailDirection(this);

        s32 waitTime = 0;
        MR::getCurrentRailPointArg0NoInit(this, &waitTime);

        if (waitTime > 0) {
            setNerve(GET_NERVE(Birikyu, HostTypeNrvWaitAtEdge));
            return;
        }

        MR::emitEffect(this, "Clash");
    }
}

void Birikyu::exeMoveCircle() {
    MR::startActionSound(this, "OjLvBirikyuMove");
    if (tryStopPointing()) {
        return;
    }

    mOrbitAngle = MR::repeat(mOrbitAngle + (mMoveSpeed / ::sMoveRadius), 0.0f, TWO_PI);

    TPos3f rotationMtx;
    rotationMtx.identity();
    rotationMtx.makeRotate(mUp, mOrbitAngle);

    TVec3f orbitOffset = mFront * ::sMoveRadius;
    rotationMtx.mult(orbitOffset, orbitOffset);

    MR::setPosition(this, mOrbitCenter + orbitOffset);
}

void Birikyu::exeWaitAtEdge() {
    MR::startActionSound(this, "OjLvBirikyuMove");

    s32 waitTime = 0;
    MR::getCurrentRailPointArg0NoInit(this, &waitTime);

    if (MR::isStep(this, waitTime)) {
        setNerve(GET_NERVE(Birikyu, HostTypeNrvMove));
    }
}

void Birikyu::exeAttack() {
    if (MR::isFirstStep(this)) {
        mVelocity.zero();
        MR::emitEffect(this, "Hit");
    }

    MR::startActionSound(this, "OjLvBirikyuMove");

    if (MR::isStep(this, ::sAttackTime)) {
        MR::sendMsgToGroupMember(ACTMES_GROUP_MOVE_START, this, getSensor("Body"), "Body");
        goMove();
    }
}

void Birikyu::exeStopPointing() {
    if (MR::isFirstStep(this)) {
        MR::startDPDHitSound();
        if (MR::isRegisteredEffect(this, "Touch")) {
            MR::emitEffect(this, "Touch");
        }
    }

    MR::startDPDFreezeLevelSound(this);

    // if (!MR::isStarPointerPointing2PAttachTarget(this)) {
    goMove();
    // }
}

void Birikyu::exeKill() {
    if (!MR::isFirstStep(this)) {
        // fn_80034910
    }
}

BirikyuWithFace::BirikyuWithFace(const char* pName) : Birikyu(pName), mSideType(), mGravityType(-1) {
}

void BirikyuWithFace::init(const JMapInfoIter& rIter) {
    Birikyu::init(rIter);

    s32 num = -1;
    MR::getJMapInfoArg1NoInit(rIter, &num);
    mSideType = num == 1;
    MR::getJMapInfoArg3NoInit(rIter, &mGravityType);

    if (mGravityType > 1) {
        return;
    }

    MR::onCalcGravity(this);
}

void BirikyuWithFace::initAfterPlacement() {
    Birikyu::initAfterPlacement();

    if (mGravityType == 1) {
        MR::calcGravity(this);
        MR::offCalcGravity(this);
    }
}

void BirikyuWithFace::calcAndSetBaseMtx() {
    if (mGravityType == -1) {
        LiveActor::calcAndSetBaseMtx();
        return;
    }

    TPos3f mtx;
    mtx.identity();

    if (mIsConnected) {
        TVec3f sideVec(MR::getRailDirection(this));

        if (mSideType) {
            sideVec.negate();
        }

        if (!MR::isRailGoingToEnd(this)) {
            sideVec.negate();
        }

        TVec3f upVec = mUp;

        if (mGravityType <= 1) {
            upVec.set(-mGravity);
        }

        if (MR::isSameDirection(upVec, sideVec)) {
            MR::makeMtxSideFront(&mtx, sideVec, mFront);
        } else {
            MR::makeMtxSideUp(&mtx, sideVec, upVec);
        }
    } else {
        mtx.makeRotate(mUp, mOrbitAngle);
    }

    mtx.setTrans(mPosition);
    MR::setBaseTRMtx(this, mtx);
}
