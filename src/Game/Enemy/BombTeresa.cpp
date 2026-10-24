#include "Game/Enemy/BombTeresa.hpp"
#include "Game/Enemy/AnimScaleController.hpp"
#include "Game/Enemy/WalkerStateBindStarPointer.hpp"
#include "Game/LiveActor/Nerve.hpp"
#include "Game/Util/ActionSoundUtil.hpp"
#include "Game/Util/ActorAnimUtil.hpp"
#include "Game/Util/ActorInitUtil.hpp"
#include "Game/Util/ActorSensorUtil.hpp"
#include "Game/Util/ActorStateUtil.hpp"
#include "Game/Util/ActorSwitchUtil.hpp"
#include "Game/Util/CameraUtil.hpp"
#include "Game/Util/EffectUtil.hpp"
#include "Game/Util/GamePadUtil.hpp"
#include "Game/Util/JMapUtil.hpp"
#include "Game/Util/JointController.hpp"
#include "Game/Util/JointUtil.hpp"
#include "Game/Util/LiveActorUtil.hpp"
#include "Game/Util/MapUtil.hpp"
#include "Game/Util/MathUtil.hpp"
#include "Game/Util/MtxUtil.hpp"
#include "Game/Util/ObjUtil.hpp"
#include "Game/Util/PlayerUtil.hpp"
#include "Game/Util/SoundUtil.hpp"


void BombTeresa_FORCE_MATCH_SDATA2() {
    (void)1.0f;
    (void)0.0f;
    (void)0.5f;
    (void)3.0f;
    (void)2.0f;
    (void)0.1f;
    (void)0.6f;
}

namespace NrvBombTeresa {
    NEW_NERVE(BombTeresaNrvAppear, BombTeresa, Appear);
    NEW_NERVE(BombTeresaNrvShadowAppear, BombTeresa, ShadowAppear);
    NEW_NERVE(BombTeresaNrvBallAppear, BombTeresa, BallAppear);
    NEW_NERVE(BombTeresaNrvWait, BombTeresa, Wait);
    NEW_NERVE(BombTeresaNrvWander, BombTeresa, Wander);
    NEW_NERVE(BombTeresaNrvChase, BombTeresa, Chase);
    NEW_NERVE(BombTeresaNrvAttackTongueFailed, BombTeresa, AttackTongueFailed);
    NEW_NERVE(BombTeresaNrvDirectTackleSign, BombTeresa, DirectTackleSign);
    NEW_NERVE(BombTeresaNrvDirectTackle, BombTeresa, DirectTackle);
    NEW_NERVE(BombTeresaNrvDrift, BombTeresa, Drift);
    NEW_NERVE(BombTeresaNrvDriftRelease, BombTeresa, DriftRelease);
    NEW_NERVE(BombTeresaNrvBindStarPointer, BombTeresa, BindStarPointer);
    NEW_NERVE(BombTeresaNrvExplosion, BombTeresa, Explosion);
    NEW_NERVE(BombTeresaNrvDisperse, BombTeresa, Disperse);
    NEW_NERVE(BombTeresaNrvShock, BombTeresa, Shock);
    NEW_NERVE(BombTeresaNrvReadyRestart, BombTeresa, ReadyRestart);
};  // namespace NrvBombTeresa

BombTeresa::BombTeresa(const char* pName)
    : LiveActor(pName), mRootTongueDelegator(), mEndTongueDelegator(), mScaleController(), mBindStarPointer(), mBaseMtx(0.0f, 0.0f, 0.0f, 1.0f), mFront(0, 0, 1),
      _BC(0, 0, 0), mTonguePosition(0, 0, 0), mResetPosition(0, 0, 0), _E0(), _E4(), _E8(), mDriftCycleTimer(), mDoReleaseDrift(), mDisableRespawning(), _F2(true), mIsFromPolta() {
}

void BombTeresa::init(const JMapInfoIter& rIter) {
    MR::initActor(this, rIter, "BombTeresa", false);
    MR::setSensorFollowPos(this, "tungue", &mTonguePosition);
    MR::makeQuatAndFrontFromRotate(&mBaseMtx, &mFront, this);
    mResetPosition = mPosition;

    if (MR::isValidInfo(rIter)) {
        bool enableRespawing;
        MR::getJMapInfoArg1WithInit(rIter, &enableRespawing);
        mDisableRespawning = !enableRespawing;  // Feels like a quick dev patch lolll
    }

    initTongue();
    initNerve(GET_NERVE(BombTeresa, BombTeresaNrvAppear), 1);
    mScaleController = new AnimScaleController(nullptr);
    mBindStarPointer = new WalkerStateBindStarPointer(this, mScaleController);
    MR::initActorState(this, mBindStarPointer, GET_NERVE(BombTeresa, BombTeresaNrvBindStarPointer), "SupportFreeze");
    MR::initUseStageSwitchWriteDead(this, rIter);
    MR::useStageSwitchAwake(this, rIter);

    if (MR::isValidInfo(rIter)) {
        MR::useStageSwitchSyncAppear(this, rIter);
        return;
    }

    makeActorDead();
}

void BombTeresa::initAfterPlacement() {
    MR::trySetMoveLimitCollision(this);
}

void BombTeresa::initTongue() {
    mRootTongueDelegator = MR::createJointDelegator< BombTeresa >(this, this, nullptr, &BombTeresa::rootTongueMtxCallBack, "Tongue1");
    mEndTongueDelegator = MR::createJointDelegatorWithNullChildFunc(this, &BombTeresa::endTongueMtxCallBack, "Tongue2");
}

void BombTeresa::makeActorAppeared() {
    MR::showModel(this);
    LiveActor::makeActorAppeared();
    MR::onCalcGravity(this);
    MR::invalidateClipping(this);
    MR::startBrk(this, "Normal");
    mScale.set(1.0f, 1.0f, 1.0f);
    mTonguePosition = mPosition;
    _E0 = 0.0f;
    setNerve(GET_NERVE(BombTeresa, BombTeresaNrvAppear));
}

void BombTeresa::control() {
    if (isNerve(GET_NERVE(BombTeresa, BombTeresaNrvWait)) || isNerve(GET_NERVE(BombTeresa, BombTeresaNrvWander)) ||
        isNerve(GET_NERVE(BombTeresa, BombTeresaNrvChase))) {
        MR::startActionSound(this, "EmLvBombtereMove");
    }

    mScaleController->updateNerve();
    if (isEnablePointBind()) {
        if (mBindStarPointer->tryStartPointBind()) {
            setNerve(GET_NERVE(BombTeresa, BombTeresaNrvBindStarPointer));
        }
    }
}

void BombTeresa::calcAndSetBaseMtx() {
    MR::setBaseTRMtx(this, mBaseMtx);
    MR::updateBaseScale(this, mScaleController);
    mRootTongueDelegator->registerCallBack();
    mEndTongueDelegator->registerCallBack();
}

void BombTeresa::updateNormalVelocity() {
    MR::addVelocityKeepHeightUseShadow(this, 150.0f, 0.4f, 40.0f, nullptr);
    MR::attenuateVelocity(this, 0.9f);
    MR::reboundVelocityFromCollision(this, 0.0f, 0.0f, 1.0f);
    MR::blendQuatUpFront(&mBaseMtx, -mGravity, mFront, 0.1f, 0.6f);
}

void BombTeresa::updateDriftReleaseVelocity() {
    MR::addVelocityKeepHeightUseShadow(this, 150.0f, 0.4f, 40.0f, nullptr);
    MR::attenuateVelocity(this, 0.9f);
    MR::reboundVelocityFromCollision(this, 0.0f, 0.0f, 1.0f);
    MR::blendQuatUpFront(&mBaseMtx, -mGravity, mFront, 0.1f, 0.6f);
}

bool BombTeresa::rootTongueMtxCallBack(TPos3f* pMtx, const JointControllerInfo& rInfo) {
    if (_E0 == 0.0f) {
        return false;
    }

    TVec3f pos;
    TVec3f tonguePos;
    TVec3f side;
    pMtx->getTrans(pos);
    MR::copyJointPos(this, "Tongue2", &tonguePos);
    pMtx->getXDir(side);
    TVec3f dir = tonguePos - pos;
    if (MR::normalizeOrZero(&dir)) {
        dir.set(side);
    }

    MR::turnMtxToXDirRate(pMtx, dir, (0.5f * _E0));
    f32 dist = MR::getEaseInOutValue(MR::normalize(pos.distance(tonguePos), 400.0f, 1000.0f), 1.0f, 0.5f, 1.0f);
    MR::preScaleMtx(pMtx->toMtxPtr(), TVec3f(1.0f, dist, dist));
    return true;
}

bool BombTeresa::endTongueMtxCallBack(TPos3f* pMtx, const JointControllerInfo& rInfo) {
    if (_E0 == 0.0f) {
        return false;
    }

    TVec3f pos;
    TVec3f tonguePos;
    TVec3f side;
    pMtx->getTrans(pos);
    MR::copyJointPos(this, "Tongue1", &tonguePos);
    MR::vecBlend(&pos, pos, mTonguePosition, _E0);
    pMtx->getXDir(side);
    TVec3f dir = pos - tonguePos;
    if (MR::normalizeOrZero(&dir)) {
        dir.set(side);
    }

    MR::turnMtxToXDirRate(pMtx, dir, _E0);
    TVec3f side2;
    pMtx->getXDir(side2);
    pos += side2 * -35.0f * _E0;
    pMtx->setTrans(pos);
    f32 dist = MR::getEaseInOutValue(MR::normalize(pos.distance(tonguePos), 400.0f, 1000.0f), 1.0f, 0.5f, 1.0f);
    MR::preScaleMtx(pMtx->toMtxPtr(), TVec3f(1.0f, dist, dist));
    return true;
}

void BombTeresa::attackSensor(HitSensor* pSender, HitSensor* pReceiver) {
    if (MR::isSensorEye(pSender) && MR::isSensorPlayer(pReceiver)) {
        if (isTouchTongue() && !MR::sendArbitraryMsg(ACTMES_BOMB_TERESA_TONGUE_TOUCH, pReceiver, pSender)) {
            setNerve(GET_NERVE(BombTeresa, BombTeresaNrvAttackTongueFailed));
        }
    } else if (MR::isSensorEnemy(pSender)) {
        if (MR::isSensorPlayer(pReceiver)) {
            if (isEnableHitExplosionToPlayer() && MR::sendMsgEnemyAttackExplosion(pReceiver, pSender)) {
                MR::zeroVelocity(this);
                setNerve(GET_NERVE(BombTeresa, BombTeresaNrvExplosion));
            }
        } else if (isEnableHitExplosionToEnemy()) {
            if (MR::sendMsgEnemyAttackExplosion(pReceiver, pSender)) {
                MR::tryRumbleDefaultHit(this, WPAD_CHAN0);
                MR::zeroVelocity(this);
                setNerve(GET_NERVE(BombTeresa, BombTeresaNrvExplosion));
            } else {
                MR::sendMsgPush(pReceiver, pSender);
            }
        } else {
            MR::sendMsgPush(pReceiver, pSender);
        }
    }
}

bool BombTeresa::receiveMsgPush(HitSensor* pSender, HitSensor* pReceiver) {
    if (!MR::isSensorEnemy(pReceiver)) {
        return false;
    }

    if (MR::isSensorEnemy(pSender)) {
        TVec3f deltaPos = *MR::getSensorPos(pReceiver) - *MR::getSensorPos(pSender);

        if (MR::normalizeOrZero(&deltaPos)) {
            MR::getRandomVector(&deltaPos, 1.0f);
            MR::normalizeOrZero(&deltaPos);
        }

        mVelocity += deltaPos * 3.0f;
        return true;
    }

    return false;
}

bool BombTeresa::receiveMsgPlayerAttack(u32 msg, HitSensor* pSender, HitSensor* pReceiver) {
    if (MR::isMsgStarPieceAttack(msg) && isEnableStarPieceAttack()) {
        setNerve(GET_NERVE(BombTeresa, BombTeresaNrvDisperse));
        return true;
    }

    if (MR::isMsgSupportTicoSpin(msg) && isEnableDrift()) {
        setNerve(GET_NERVE(BombTeresa, BombTeresaNrvDisperse));
        return true;
    }

    if (MR::isMsgPlayerSpinAttackOrSupportTico(msg)) {
        return requestDrift();
    }

    if (MR::isMsgInvincibleAttack(msg) && isEnableShockWave()) {
        setNerve(GET_NERVE(BombTeresa, BombTeresaNrvDisperse));
        return true;
    }

    return false;
}

bool BombTeresa::receiveMsgEnemyAttack(u32 msg, HitSensor* pSender, HitSensor* pReceiver) {
    if (MR::isMsgToEnemyAttackBlow(msg) && isEnableHitExplosion()) {
        MR::zeroVelocity(this);
        setNerve(GET_NERVE(BombTeresa, BombTeresaNrvDisperse));
        return false;
    }

    if (MR::isMsgToEnemyAttackShockWave(msg) && isEnableShockWave()) {
        TVec3f deltaDir;
        MR::calcSensorDirectionNormalize(&deltaDir, pSender, pReceiver);
        mVelocity.set(deltaDir * 20.0f);
        setNerve(GET_NERVE(BombTeresa, BombTeresaNrvShock));
        return false;
    }

    if (MR::isMsgExplosionAttack(msg) && isEnableHitExplosion()) {
        MR::zeroVelocity(this);
        setNerve(GET_NERVE(BombTeresa, BombTeresaNrvExplosion));
        return true;
    }

    return false;
}

bool BombTeresa::receiveOtherMsg(u32 msg, HitSensor* pSender, HitSensor* pReceiver) {
    if (msg == ACTMES_DISPERSE_BOMB_TERESA && isEnableDisperse()) {
        MR::zeroVelocity(this);
        setNerve(GET_NERVE(BombTeresa, BombTeresaNrvDisperse));
        return true;
    }

    if (MR::isMsgSpinStormRange(msg)) {
        return requestDrift();
    }

    return false;
}

bool BombTeresa::requestDrift() {
    if (isEnableDrift()) {
        MR::invalidateClipping(this);
        setNerve(GET_NERVE(BombTeresa, BombTeresaNrvDrift));
        return true;
    }

    return false;
}

bool BombTeresa::tryCheseEnd() {
    if (MR::isGreaterStep(this, 240) || MR::isPlayerElementModeTeresa() || isOutOfRange(2000.0f)) {
        setNerve(GET_NERVE(BombTeresa, BombTeresaNrvWait));
        return true;
    }

    return false;
}

bool BombTeresa::tryDirectTackle() {
    if (!MR::isPlayerDamaging() && MR::isNearPlayer(this, 900.0f) && MR::isFaceToPlayerHorizontalDegree(this, mFront, 30.0f)) {
        setNerve(GET_NERVE(BombTeresa, BombTeresaNrvDirectTackleSign));
        return true;
    }

    return false;
}

bool BombTeresa::tryAbortDrift() {
    if (MR::isExistMapCollision(mPosition, mTonguePosition - mPosition)) {
        setNerve(GET_NERVE(BombTeresa, BombTeresaNrvAttackTongueFailed));
        return true;
    }

    return false;
}

bool BombTeresa::tryDriftRelease() {
    if (mDoReleaseDrift) {
        setNerve(GET_NERVE(BombTeresa, BombTeresaNrvDriftRelease));
        return true;
    }

    return false;
}

bool BombTeresa::tryDriftReleaseEnd() {
    if (MR::isGreaterStep(this, 60)) {
        MR::deleteEffect(this, "SpinBlur");
        setNerve(GET_NERVE(BombTeresa, BombTeresaNrvWait));
        return true;
    }

    return false;
}

bool BombTeresa::tryExplosion() {
    if (MR::isBinded(this)) {
        if (MR::sendMsgEnemyAttackExplosionToBindedSensor(this, getSensor("Body"))) {
            MR::zeroVelocity(this);
            setNerve(GET_NERVE(BombTeresa, BombTeresaNrvExplosion));
            MR::forceDeleteEffect(this, "SpinBlur");
            return true;
        }
    }

    return false;
}

bool BombTeresa::tryRevival() {
    MR::startBrk(this, "Normal");
    if (mDisableRespawning) {
        MR::invalidateHitSensors(this);
        setNerve(GET_NERVE(BombTeresa, BombTeresaNrvReadyRestart));
        return true;
    }

    kill();
    return false;
}

void BombTeresa::exeAppear() {
    if (MR::isFirstStep(this)) {
        MR::validateHitSensor(this, "Body");
        MR::validateHitSensor(this, "tungue");
        MR::showModel(this);
        MR::startAction(this, "Appear");
        MR::emitEffect(this, "Appear");
        MR::startActionSound(this, "EmBombtereAppear");
        _E0 = 0.0f;
    }

    mTonguePosition = mPosition;
    updateNormalVelocity();
    if (MR::isActionEnd(this)) {
        setNerve(GET_NERVE(BombTeresa, BombTeresaNrvWait));
    }
}

void BombTeresa::exeShadowAppear() {
    if (MR::isFirstStep(this)) {
        MR::emitEffect(this, "Shadow");
        MR::hideModelAndOnCalcAnim(this);
        MR::startAction(this, "ShadowAppear");
    }

    if (!MR::isBindedGround(this)) {
        MR::addVelocityToGravity(this, 1.0f);
    }

    f32 v2;
    if (MR::isLessStep(this, 130)) {
        v2 = 0.995f;
    } else {
        v2 = 0.8f;
    }

    MR::attenuateVelocity(this, v2);
    MR::turnDirectionToPlayerDegree(this, &mFront, 3.0f);
    mTonguePosition = mPosition;
    MR::blendQuatUpFront(&mBaseMtx, -mGravity, mFront, 0.1f, 0.6f);
    if (MR::isGreaterStep(this, 120)) {
        MR::deleteEffect(this, "Shadow");
        setNerve(GET_NERVE(BombTeresa, BombTeresaNrvAppear));
    }
}

void BombTeresa::exeBallAppear() {
    if (MR::isFirstStep(this)) {
        MR::validateHitSensor(this, "Body");
        MR::validateHitSensor(this, "tungue");
        MR::emitEffect(this, "Ball");
        MR::startAction(this, "BallAppear");
        MR::showModel(this);
        _E0 = 0.0f;
    }

    mTonguePosition = mPosition;
    MR::addVelocityToGravity(this, 1.0f);
    bool v2 = MR::reboundVelocityFromCollision(this, 0.95f, 2.0f, 1.0f);
    MR::attenuateVelocity(this, 0.99f);
    if (v2) {
        MR::startActionSound(this, "EmBombtereBound");
    }

    if (MR::isLessStep(this, 160)) {
        MR::rotateQuatRollBall(&mBaseMtx, mVelocity, -mGravity, 70.0f);
        mBaseMtx.getZDir(mFront);
    } else {
        mFront.orthogonalize(mGravity);
        if (MR::normalizeOrZero(&mFront)) {
            MR::makeAxisVerticalZX(&mFront, mGravity);
        }

        MR::blendQuatUpFront(&mBaseMtx, -mGravity, mFront, 0.1f, 0.1f);
    }

    if (MR::isGreaterStep(this, 70)) {
        MR::deleteEffect(this, "Ball");
        MR::emitEffect(this, "Appear");
        MR::startActionSound(this, "EmBombtereAppear");
        MR::showModel(this);
        setNerve(GET_NERVE(BombTeresa, BombTeresaNrvDirectTackleSign));
    }
}

void BombTeresa::exeWait() {
    if (MR::isFirstStep(this)) {
        MR::validateClipping(this);
        MR::startAction(this, "Wait");
        MR::startBrk(this, "Normal");
        _E0 = 0.0f;
    }

    mTonguePosition = mPosition;
    updateNormalVelocity();
    if (MR::isInDeath(this, TVec3f(0.0f, 0.0f, 0.0f))) {
        tryRevival();
    } else if (MR::isNearPlayerAnyTime(this, 1800.0f)) {
        setNerve(GET_NERVE(BombTeresa, BombTeresaNrvChase));
    } else if (mIsFromPolta) {
        if (MR::isGreaterStep(this, 60)) {
            setNerve(GET_NERVE(BombTeresa, BombTeresaNrvWander));
        }
    }
}

void BombTeresa::exeWander() {
    if (MR::isFirstStep(this)) {
        MR::startAction(this, "Wait");
        MR::startBrk(this, "Normal");
        _E0 = 0.0f;
    }

    mTonguePosition = mPosition;

    MR::rotateDirectionGravityDegree(this, &mFront, getNerveStep() % 600 < 400 ? 0.5f : -0.5f);
    MR::addVelocityMoveToDirection(this, mFront, 0.5f);
    updateNormalVelocity();
    if (MR::isInDeath(this, TVec3f(0.0f, 0.0f, 0.0f))) {
        tryRevival();
    } else if (MR::isNearPlayerAnyTime(this, 1800.0f)) {
        setNerve(GET_NERVE(BombTeresa, BombTeresaNrvChase));
    }
}

void BombTeresa::exeChase() {
    if (MR::isFirstStep(this)) {
        MR::startAction(this, "Wait");
        MR::startActionSound(this, "EvBombtereLaugh");
        _E0 = 0.0f;
    }

    MR::turnDirectionToPlayerDegree(this, &mFront, 1.4f);
    MR::addVelocityMoveToDirection(this, mFront, (0.9f * MR::calcNerveRate(this, 60)));
    mTonguePosition = mPosition;
    updateNormalVelocity();
    if (!tryCheseEnd() && tryDirectTackle()) {
        return;
    }
}

void BombTeresa::exeAttackTongueFailed() {
    if (MR::isFirstStep(this)) {
        MR::startAction(this, "Return");
    }

    MR::startActionSound(this, "EmLvBombtereTongueBack");
    _E0 = MR::calcNerveEaseInOutValue(this, 0, 1.0f, 0.0f);
    updateNormalVelocity();
    if (MR::isGreaterStep(this, 40)) {
        setNerve(GET_NERVE(BombTeresa, BombTeresaNrvWait));
    }
}

void BombTeresa::exeDirectTackleSign() {
    if (MR::isFirstStep(this)) {
        MR::startActionSound(this, "EvBombtereTackle");
        MR::startAction(this, "TackleSign");
        _E0 = 0.0f;
    }

    MR::turnDirectionToPlayerDegree(this, &mFront, 10.0f);
    MR::addVelocityKeepHeight(this, *MR::getPlayerCenterPos(), 100.0f, 0.6f, 100.0f);
    updateNormalVelocity();
    mTonguePosition = mPosition;
    if (MR::isActionEnd(this)) {
        setNerve(GET_NERVE(BombTeresa, BombTeresaNrvDirectTackle));
    }
}

void BombTeresa::exeDirectTackle() {
    if (MR::isFirstStep(this)) {
        MR::startAction(this, "Tackle");
        _E0 = 0.0f;
    }

    MR::startActionSound(this, "EmLvBombtereTackle");
    MR::turnDirectionToPlayerDegree(this, &mFront, 0.8f);
    MR::addVelocityMoveToDirection(this, mFront, (1.5f * MR::calcNerveRate(this, 50)));
    MR::addVelocityKeepHeight(this, *MR::getPlayerCenterPos(), 100.0f, 0.6f, 100.0f);
    updateNormalVelocity();
    mTonguePosition = mPosition;
    if (MR::isGreaterStep(this, 120)) {
        setNerve(GET_NERVE(BombTeresa, BombTeresaNrvWander));
    }
}

void BombTeresa::exeDrift() {
    TVec3f v14;
    TPos3f handRMtx;
    TVec3f v15;
    if (MR::isFirstStep(this)) {
        MR::startAction(this, "Spin");
        MR::startBrk(this, "Normal");
        MR::emitEffect(this, "SpinBlur");
        MR::startActionSound(this, "EmBombtereTongueCatch");
        _F2 = MR::isLeftSideFromPlayer(this) == false;
        mDriftCycleTimer = 40;
        mDoReleaseDrift = false;
        _E4 = 7.0f;
        _E8 = 7.0f;
        _E0 = 1.0f;
    }

    v14.cross(mGravity, mFront);
    v15.cross(mGravity, *MR::getPlayerPos() - MR::getCamPos());

    if (MR::isNearZero(v14)) {
        MR::makeAxisVerticalZX(&v14, mGravity);
    }

    if (MR::isNearZero(v15)) {
        MR::makeAxisVerticalZX(&v15, mGravity);
    }

    MR::normalize(&v14);
    MR::normalize(&v15);
    if (v14.dot(v15) >= 0.8f) {
        MR::startActionSound(this, "EmLvBombtereSwing");
    }

    MR::calcPlayerJointMtx(&handRMtx, "HandR");
    TVec3f v13;
    handRMtx.getTrans(v13);
    TVec3f v12;
    handRMtx.getZDir(v12);
    if (!MR::normalizeOrZero(&v12)) {
        v13.scaleAdd(20.0f, v12, v13);
    }

    MR::vecBlend(&mTonguePosition, mTonguePosition, v13, MR::calcNerveEaseInRate(this, 15));
    MR::turnDirectionToTarget(this, &mFront, *MR::getPlayerPos(), 0.0f);

    if (mDriftCycleTimer <= 0) {
        if (MR::isPadSwing(WPAD_CHAN0)) {
            MR::tryRumblePadMiddle(this, WPAD_CHAN0);
            mDriftCycleTimer = 40;
            _E4 += 20.0f;
            _E8 += 20.0f;
            if (MR::isGreaterStep(this, 190)) {
                mDoReleaseDrift = true;
            }
        }
    }

    addTeresaSpinPullVelocity(MR::calcNerveEaseInOutValue(this, 190, 240, 150.0f, 70.0f));
    updateNormalVelocity();
    if (MR::isStep(this, 190)) {
        MR::startBrk(this, "CountDown");
    }

    _E8 = MR::getInterpolateValue(0.15f, _E8, 7.0f);
    if (MR::isLessStep(this, 190)) {
        _E4 = MR::getInterpolateValue(0.15f, _E4, 7.0f);
    } else {
        if (_E4 > 7.0f) {
            _E4 = MR::getInterpolateValue(0.15f, _E4, 7.0f);
        }

        _E4 *= 0.992f;
    }

    mDriftCycleTimer--;
    if (!tryExplosion() && !tryDriftRelease() && tryAbortDrift()) {
        return;
    }
}

void BombTeresa::exeDriftRelease() {
    if (MR::isFirstStep(this)) {
        MR::startAction(this, "Drift");
        MR::tryRumblePadStrong(this, WPAD_CHAN0);
        MR::startActionSound(this, "EmBombtereThrow");
    }

    _E0 = MR::calcNerveEaseInOutValue(this, 12, 1.0f, 0.0f);
    if (MR::isLessStep(this, 0)) {
        addTeresaSpinPullVelocity(150.0f);
        updateNormalVelocity();
    } else {
        updateDriftReleaseVelocity();
    }

    if (!tryExplosion() && tryDriftReleaseEnd()) {
        return;
    }
}

void BombTeresa::exeBindStarPointer() {
    MR::updateActorStateAndNextNerve(this, GET_NERVE(BombTeresa, BombTeresaNrvWait));
}

void BombTeresa::exeExplosion() {
    if (MR::isFirstStep(this)) {
        MR::shakeCameraNormalStrong();
        MR::tryRumblePadStrong(this, WPAD_CHAN0);
        MR::deleteEffect(this, "SpinBlur");
        MR::emitEffect(this, "Explosion");
        MR::hideModel(this);
        MR::startActionSound(this, "EmBombtereExplosion");
        _E0 = 0.0f;
        MR::zeroVelocity(this);
    }

    mTonguePosition = mPosition;
    if (MR::isGreaterStep(this, 20)) {
        tryRevival();
    }
}

void BombTeresa::exeShock() {
    if (MR::isFirstStep(this)) {
        MR::emitEffect(this, "SpinBlur");
        _E0 = 0.0f;
    }

    mTonguePosition = mPosition;
    MR::attenuateVelocity(this, 0.98f);
    if (MR::isGreaterStep(this, 20)) {
        MR::deleteEffect(this, "SpinBlur");
        MR::emitEffect(this, "MisFire");
        MR::startActionSound(this, "EmBombtereHide");
        MR::hideModel(this);
        tryRevival();
    }
}

void BombTeresa::exeDisperse() {
    if (MR::isFirstStep(this)) {
        MR::deleteEffect(this, "SpinBlur");
        MR::emitEffect(this, "MisFire");
        MR::startActionSound(this, "EmBombtereHide");
        MR::hideModel(this);
        _E0 = 0.0f;
        MR::zeroVelocity(this);
    }

    mTonguePosition = mPosition;
    if (MR::isGreaterStep(this, 40)) {
        tryRevival();
    }
}

void BombTeresa::exeReadyRestart() {
    if (MR::isFirstStep(this)) {
        MR::startAction(this, "Hide");
        MR::resetPosition(this, mResetPosition);
        MR::makeQuatAndFrontFromRotate(&mBaseMtx, &mFront, this);
        MR::zeroVelocity(this);
    }

    mTonguePosition = mPosition;
    if (MR::isGreaterStep(this, 120)) {
        setNerve(GET_NERVE(BombTeresa, BombTeresaNrvAppear));
    }
}

bool BombTeresa::isTouchTongue() const NO_INLINE {
    return isNerve(GET_NERVE(BombTeresa, BombTeresaNrvDrift));
}

bool BombTeresa::isEnableDrift() const NO_INLINE {
    if (isNerve(GET_NERVE(BombTeresa, BombTeresaNrvBallAppear)) || isNerve(GET_NERVE(BombTeresa, BombTeresaNrvShadowAppear)) ||
        isNerve(GET_NERVE(BombTeresa, BombTeresaNrvDrift)) || isNerve(GET_NERVE(BombTeresa, BombTeresaNrvDriftRelease)) ||
        isNerve(GET_NERVE(BombTeresa, BombTeresaNrvExplosion)) || isNerve(GET_NERVE(BombTeresa, BombTeresaNrvShock)) ||
        isNerve(GET_NERVE(BombTeresa, BombTeresaNrvDisperse)) || isNerve(GET_NERVE(BombTeresa, BombTeresaNrvReadyRestart))) {
        return false;
    }

    return true;
}

bool BombTeresa::isEnablePointBind() const NO_INLINE {
    if (isNerve(GET_NERVE(BombTeresa, BombTeresaNrvWait)) || isNerve(GET_NERVE(BombTeresa, BombTeresaNrvWander)) ||
        isNerve(GET_NERVE(BombTeresa, BombTeresaNrvChase)) || isNerve(GET_NERVE(BombTeresa, BombTeresaNrvAttackTongueFailed)) ||
        isNerve(GET_NERVE(BombTeresa, BombTeresaNrvDirectTackleSign)) || isNerve(GET_NERVE(BombTeresa, BombTeresaNrvDirectTackle)) ||
        isNerve(GET_NERVE(BombTeresa, BombTeresaNrvDriftRelease))) {
        return true;
    }

    return false;
}

bool BombTeresa::isEnableDisperse() const NO_INLINE {
    if (isNerve(GET_NERVE(BombTeresa, BombTeresaNrvDrift))) {
        return false;
    }

    return isEnableDrift();
}

bool BombTeresa::isEnableHitExplosionToPlayer() const NO_INLINE {
    if (isNerve(GET_NERVE(BombTeresa, BombTeresaNrvDrift))) {
        return MR::isGreaterStep(this, 190);
    }

    return isEnableHitExplosion();
}

bool BombTeresa::isEnableHitExplosionToEnemy() const NO_INLINE {
    if (isNerve(GET_NERVE(BombTeresa, BombTeresaNrvDrift)) || isNerve(GET_NERVE(BombTeresa, BombTeresaNrvDriftRelease))) {
        return true;
    }

    return false;
}

bool BombTeresa::isEnableHitExplosion() const NO_INLINE {
    if (isNerve(GET_NERVE(BombTeresa, BombTeresaNrvBallAppear)) || isNerve(GET_NERVE(BombTeresa, BombTeresaNrvShadowAppear)) ||
        isNerve(GET_NERVE(BombTeresa, BombTeresaNrvExplosion)) || isNerve(GET_NERVE(BombTeresa, BombTeresaNrvShock)) ||
        isNerve(GET_NERVE(BombTeresa, BombTeresaNrvDisperse)) || isNerve(GET_NERVE(BombTeresa, BombTeresaNrvDrift)) ||
        isNerve(GET_NERVE(BombTeresa, BombTeresaNrvReadyRestart))) {
        return false;
    }

    return true;
}

bool BombTeresa::isEnableStarPieceAttack() const NO_INLINE {
    if (isNerve(GET_NERVE(BombTeresa, BombTeresaNrvBallAppear)) || isNerve(GET_NERVE(BombTeresa, BombTeresaNrvShadowAppear)) ||
        isNerve(GET_NERVE(BombTeresa, BombTeresaNrvExplosion)) || isNerve(GET_NERVE(BombTeresa, BombTeresaNrvShock)) ||
        isNerve(GET_NERVE(BombTeresa, BombTeresaNrvDisperse)) || isNerve(GET_NERVE(BombTeresa, BombTeresaNrvDrift)) ||
        isNerve(GET_NERVE(BombTeresa, BombTeresaNrvReadyRestart))) {
        return false;
    }

    return true;
}

bool BombTeresa::isEnableShockWave() const NO_INLINE {
    if (isNerve(GET_NERVE(BombTeresa, BombTeresaNrvExplosion)) || isNerve(GET_NERVE(BombTeresa, BombTeresaNrvShock)) ||
        isNerve(GET_NERVE(BombTeresa, BombTeresaNrvDisperse))) {
        return false;
    }

    return true;
}

bool BombTeresa::appearNormal(const TVec3f& rPosition, const TVec3f& rVelocity) {
    if (!MR::isDead(this)) {
        return false;
    }

    setNerve(GET_NERVE(BombTeresa, BombTeresaNrvAppear));
    MR::setPosition(this, rPosition);
    appear();
    MR::showModel(this);
    mVelocity.set(rVelocity);
    MR::invalidateClipping(this);
    MR::trySetMoveLimitCollision(this);
    return true;
}

bool BombTeresa::appearShadow(const TVec3f& rPosition, const TVec3f& rVelocity) {
    if (!appearNormal(rPosition, rVelocity)) {
        return false;
    }

    MR::invalidateHitSensors(this);
    MR::hideModelAndOnCalcAnim(this);
    setNerve(GET_NERVE(BombTeresa, BombTeresaNrvShadowAppear));
    return true;
}

void BombTeresa::addTeresaSpinPullVelocity(f32 arg0) {
    TVec3f playerCenterPos = TVec3f(*MR::getPlayerCenterPos());
    MR::addVelocityClockwiseToTarget(this, playerCenterPos, _E4);
    MR::addVelocityMoveToTarget(this, playerCenterPos, 0.0f, _E8, 0.0f, 150.0f);
    MR::addVelocityKeepHeight(this, playerCenterPos, arg0, 3.0f, 100.0f);
}

bool BombTeresa::requestDisperse() {
    if (isNerve(GET_NERVE(BombTeresa, BombTeresaNrvExplosion)) || isNerve(GET_NERVE(BombTeresa, BombTeresaNrvShock)) ||
        isNerve(GET_NERVE(BombTeresa, BombTeresaNrvDisperse))) {
        return false;
    }

    setNerve(GET_NERVE(BombTeresa, BombTeresaNrvDisperse));
    return true;
}
