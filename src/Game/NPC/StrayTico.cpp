#include "Game/NPC/StrayTico.hpp"
#include "Game/LiveActor/Nerve.hpp"
#include "Game/LiveActor/PartsModel.hpp"
#include "Game/NPC/CollectTico.hpp"
#include "Game/Util.hpp"

namespace {
    static const f32 sPushAccel = 0.3f;
    static const f32 sWaitTurnDegree = 2.0f;
    static const f32 sChaseTurnDegree = 4.0f;
    static const f32 sChaseFric = 0.97f;
    static const f32 sChaseDistance = 400.0f;
    static const f32 sWarpTryDistance = 2000.0f;
    static const f32 sUpdateWarpDistance = 1600.0f;
    static const f32 sAwayDistance = 300.0f;
    static const f32 sUpVecBlendRate = 0.2f;
    static const f32 sFrontVecBlendRate = 0.2f;
    static const s32 sCompletePlacementTime = 40;
    static const s32 sCompleteRotateStartTime = 60;
    static const s32 sCompleteDemoTime = 200;
    static const f32 sCompleteDemoRotate = 4.0f;
    static const f32 sCompleteStartRadius = 450.0f;
};  // namespace

namespace NrvStrayTico {
    NEW_NERVE(StrayTicoNrvWait, StrayTico, Wait);
    NEW_NERVE(StrayTicoNrvGlad, StrayTico, Glad);
    NEW_NERVE(StrayTicoNrvChase, StrayTico, Chase);
    NEW_NERVE(StrayTicoNrvLauncherCamera, StrayTico, LauncherCamera);
    NEW_NERVE(StrayTicoNrvCompleteDemo, StrayTico, CompleteDemo);
    NEW_NERVE(StrayTicoNrvBindMove, StrayTico, BindMove);
    NEW_NERVE(StrayTicoNrvBindEnd, StrayTico, BindEnd);
};  // namespace NrvStrayTico

StrayTico::StrayTico(const char* pName, CollectTico* pHost)
    : LiveActor(pName), mHost(pHost), mItemBubbleModel(), mRotateQuat(0.0f, 0.0f, 0.0f, 1.0f), mFrontVec(0.0f, 0.0f, 1.0f), _B0(0.0f, 0.0f, 0.0f),
      _BC(0.0f, 0.0f, 0.0f), _C8(0.0f, 1.0f, 0.0f), _D4(0.0f, 0.0f, 1.0f), _EC(), _F0() {
}

void StrayTico::init(const JMapInfoIter& rIter) {
    MR::initDefaultPos(this, rIter);
    MR::initActor(this, rIter, "StrayTico", false);
    MR::connectToSceneNpc(this);
    MR::makeQuatAndFrontFromRotate(&mRotateQuat, &mFrontVec, this);
    _B0.set(mPosition);
    MR::calcGravity(this);
    initNerve(GET_NERVE(StrayTico, StrayTicoNrvWait));
    initSensor();
    initShadow();
    initEffectKeeper(0, nullptr, false);
    initSound(4, "StrayTico");
    initBinder(60.0f, 20.0f, 0);
    MR::offBind(this);
    MR::calcGravity(this);

    mItemBubbleModel = MR::createPartsModelMapObj(this, "アワ", "ItemBubble", nullptr);
    mItemBubbleModel->initFixedPosition(TVec3f(0.0f, 0.0f, 0.0f), TVec3f(0.0f, 0.0f, 0.0f), nullptr);

    MR::registerDemoSimpleCastAll(mItemBubbleModel);
    MR::startAction(mItemBubbleModel, "Move");
    MR::calcGravity(mItemBubbleModel);

    MR::initUseStageSwitchWriteA(this, rIter);

    if (MR::useStageSwitchSyncAppear(this, rIter)) {
        mItemBubbleModel->kill();
    } else {
        mItemBubbleModel->appear();
    }
    MR::useStageSwitchAwake(this, rIter);
}

void StrayTico::initSensor() {
    initHitSensor(2);
    MR::addHitSensorNpc(this, "Bubble", 8, 80.0f, TVec3f(0.0f, 0.0f, 0.0f));
    MR::addHitSensorNpc(this, "Body", 8, 45.0f, TVec3f(0.0f, 0.0f, 0.0f));
    MR::validateHitSensor(this, "Bubble");
    MR::invalidateHitSensor(this, "Body");
}

inline void StrayTico::setShadowDrop(const char* const pos) {
    const TVec3f offset(0.0f, 0.0f, 0.0f);
    MR::setShadowDropPositionAtJoint(this, nullptr, pos, offset);
}

void StrayTico::initShadow() {
    MR::initShadowVolumeOval(this, TVec3f(40.0f, 40.0f, 20.0f));
    setShadowDrop("PowerStarC");
    MR::onCalcShadow(this, nullptr);
}

void StrayTico::appear() {
    LiveActor::appear();
    startGlad();
}

void StrayTico::control() {
    MR::blendQuatUpFront(&mRotateQuat, -mGravity, mFrontVec, ::sUpVecBlendRate, ::sFrontVecBlendRate);

    if (isNerve(GET_NERVE(StrayTico, StrayTicoNrvCompleteDemo))) {
        return;
    }

    if (isNerve(GET_NERVE(StrayTico, StrayTicoNrvWait))) {
        MR::startActionSound(this, "SmLvStrayticoWait");
    } else {
        MR::startActionSound(this, "SmLvStrayticoWaitGrp");
    }
}

void StrayTico::calcAndSetBaseMtx() {
    MR::setBaseTRMtx(this, mRotateQuat);
}

void StrayTico::startGlad() {
    mItemBubbleModel->kill();
    MR::onCalcGravity(this);
    MR::onCalcShadow(this, nullptr);
    MR::onBind(this);
    MR::invalidateClipping(this);
    MR::validateHitSensor(this, "Body");
    MR::invalidateHitSensor(this, "Bubble");
    setNerve(GET_NERVE(StrayTico, StrayTicoNrvGlad));
}

void StrayTico::launch(const TPos3f& pos) {
    if (!isNerve(&NrvStrayTico::StrayTicoNrvChase::sInstance))
        return;

    TVec3f position, up;
    pos.getTrans(position);
    pos.getYDir(up);
    MR::resetPosition(this, position);
    MR::setVelocity(this, up * 10);
}

void StrayTico::updateWarp() {
    bool isNotNearPlayer = !MR::isNearPlayerAnyTime(this, ::sWarpTryDistance);

    if (!isNotNearPlayer) {
        return;
    }

    bool isNotNearPlayer2 = !MR::isNearPlayer(_B0, ::sUpdateWarpDistance);

    if (isNotNearPlayer2) {
        _B0.set(*MR::getPlayerCenterPos());
    }

    if (MR::isJudgedToClipFrustum(mPosition, 200.0f) && MR::isJudgedToClipFrustum(_B0, 200.0f)) {
        MR::resetPosition(this, _B0);
    }
}

void StrayTico::updateChase() {
    bool isNotNearPlayer = !MR::isNearPlayerAnyTime(this, ::sChaseDistance);

    if (isNotNearPlayer) {
        MR::addVelocityMoveToTargetHorizon(this, *MR::getPlayerPos(), 0.5f);
        MR::tryStartBck(this, "Chase", nullptr);
    } else if (MR::isNearPlayerAnyTime(this, ::sAwayDistance)) {
        MR::addVelocityAwayFromTarget(this, *MR::getPlayerPos(), 0.5f);
        MR::tryStartBck(this, "Chase", nullptr);
    } else {
        MR::tryStartBck(this, "Wait", nullptr);
    }

    TVec3f playerFrontVec;
    MR::getPlayerFrontVec(&playerFrontVec);

    MR::turnDirectionDegree(this, &mFrontVec, playerFrontVec, ::sChaseTurnDegree);
    MR::addVelocityKeepHeight(this, *MR::getPlayerPos(), 150.0f, 0.5f, 200.0f);
    MR::attenuateVelocity(this, ::sChaseFric);
    MR::reboundVelocityFromCollision(this, 0.0f, 0.0f, 1.0f);
}

void StrayTico::attackSensor(HitSensor* pSender, HitSensor* pReceiver) {
    if (!isNerve(GET_NERVE(StrayTico, StrayTicoNrvWait)) && MR::isSensorNpc(pReceiver) && MR::sendMsgPush(pReceiver, pSender)) {
        MR::addVelocityAwayFromTarget(this, *MR::getSensorPos(pReceiver), ::sPushAccel);
    }

    if (isNerve(GET_NERVE(StrayTico, StrayTicoNrvWait)) && MR::isSensorPlayer(pReceiver)) {
        MR::tryRumblePadMiddle(this, WPAD_CHAN0);
        MR::emitEffect(this, "Break");
        MR::startActionSound(this, "OjItemBubbleBreak");
        startGlad();
    }
}

bool StrayTico::receiveMsgPlayerAttack(u32 msg, HitSensor* pSender, HitSensor* pReceiver) {
    if (MR::isMsgStarPieceAttack(msg) && isNerve(GET_NERVE(StrayTico, StrayTicoNrvWait))) {
        MR::limitedStarPieceHitSound();

        return true;
    }

    if (MR::isMsgStarPieceReflect(msg) && !isNerve(GET_NERVE(StrayTico, StrayTicoNrvWait))) {
        if (isNerve(GET_NERVE(StrayTico, StrayTicoNrvChase))) {
            TVec3f sensorDir;
            MR::calcSensorDirectionNormalize(&sensorDir, pSender, pReceiver);
            MR::setVelocity(this, sensorDir * 10.0f);
        }

        return true;
    }

    return false;
}

bool StrayTico::receiveMsgPush(HitSensor* pSender, HitSensor* pReceiver) {
    if (!isNerve(GET_NERVE(StrayTico, StrayTicoNrvWait)) && MR::isSensorNpc(pSender)) {
        MR::addVelocityAwayFromTarget(this, *MR::getSensorPos(pSender), ::sPushAccel);

        return true;
    }

    return false;
}

bool StrayTico::receiveOtherMsg(u32 msg, HitSensor* pSender, HitSensor* pReceiver) {
    if (isEnableSpin() && MR::isMsgSpinStormRange(msg)) {
        MR::addVelocityClockwiseToTarget(this, *MR::getSensorPos(pSender), 2.0f);
        MR::addVelocityMoveToTargetHorizon(this, *MR::getSensorPos(pSender), 1.0f);

        return true;
    }

    if (MR::isMsgItemNigeroTake(msg)) {
        return isNigeroTakeable();
    }

    if (MR::isMsgItemStartMove(msg)) {
        return tryStartBindMove();
    }

    if (MR::isMsgItemEndMove(msg)) {
        return tryEndBindMove();
    }

    if (MR::isMsgItemNigeroDrop(msg)) {
        return tryNigeroDrop();
    }

    return false;
}


bool StrayTico::tryStartBindMove() {
    if (isNigeroTakeable()) {
        MR::invalidateClipping(this);
        setNerve(GET_NERVE(StrayTico, StrayTicoNrvBindMove));
        return true;
    }

    return false;
}

bool StrayTico::tryEndBindMove() {
    if (isNerve(GET_NERVE(StrayTico, StrayTicoNrvBindMove))) {
        MR::zeroVelocity(this);
        MR::offCalcGravity(this);
        MR::offCalcShadow(this, nullptr);
        MR::offCalcGravity(mItemBubbleModel);
        MR::offCalcShadow(mItemBubbleModel, nullptr);
        setNerve(GET_NERVE(StrayTico, StrayTicoNrvWait));
        return true;
    }
    return false;
}

bool StrayTico::tryNigeroDrop() {
    if (isNerve(GET_NERVE(StrayTico, StrayTicoNrvBindMove))) {
        MR::onBind(this);
        setNerve(GET_NERVE(StrayTico, StrayTicoNrvBindEnd));
        return true;
    }
    return false;
}

bool StrayTico::requestCompleteDemo(const TVec3f& rParam1, const TVec3f& rParam2, f32 param3) {
    _E0 = mPosition;
    _BC = rParam1;
    _C8 = rParam2;
    _EC = param3;

    MR::normalize(&_C8);
    MR::makeAxisVerticalZX(&_D4, _C8);

    TVec3f vec;
    vec.killElement2(rParam1 - mPosition, _C8);

    if (MR::normalizeOrZero(&vec)) {
        vec = _D4;
    }

    _F0 = _180_PI * MR::diffAngleSigned(vec, _D4, _C8);

    setNerve(GET_NERVE(StrayTico, StrayTicoNrvCompleteDemo));

    return true;
}

void StrayTico::exeWait() {
    if (MR::isFirstStep(this)) {
        MR::startAction(this, "Wait");
        MR::zeroVelocity(this);
    }

    if (MR::isNearPlayer(this, 1000.0f)) {
        MR::turnDirectionToTargetDegree(this, &mFrontVec, *MR::getPlayerPos(), ::sWaitTurnDegree);
    }
}

void StrayTico::exeGlad() {
    if (MR::isFirstStep(this)) {
        MR::startAction(this, "Glad");
        s32 noRescuedCount = mHost->calcNoRescuedCount();
        const s32 rescuedCount = mHost->mTicoNum - noRescuedCount;
        MR::startActionSound(this, "SmStrayticoSpin");
        MR::startActionSound(this, "SmStrayticoGet", rescuedCount);

        if (noRescuedCount == 1) {
            setNerve(GET_NERVE(StrayTico, StrayTicoNrvChase));
            return;
        }
    }

    if (MR::isActionEnd(this)) {
        if (MR::isValidSwitchA(this)) {
            MR::onSwitchA(this);
        }

        setNerve(GET_NERVE(StrayTico, StrayTicoNrvChase));
        MR::startActionSound(this, "SvStrayticoGlad");
    }
}

void StrayTico::exeChase() {
    if (MR::isFirstStep(this)) {
        MR::validateHitSensor(this, "Body");
        MR::invalidateHitSensor(this, "Bubble");
        MR::onBind(this);
        MR::tryStartBck(this, "Chase", nullptr);
        _B0.set(*MR::getPlayerCenterPos());
    }

    updateWarp();
    updateChase();

    if (MR::isActiveLauncherCamera() || MR::isActiveLauncherFlightCamera()) {
        setNerve(GET_NERVE(StrayTico, StrayTicoNrvLauncherCamera));
    }
}

void StrayTico::exeLauncherCamera() {
    if (MR::isFirstStep(this)) {
        MR::invalidateHitSensors(this);
        MR::offBind(this);
    }

    TVec3f vec;
    vec.scaleAdd(-400.0f, MR::getCamZdir(), *MR::getPlayerPos());

    MR::addVelocityMoveToTargetHorizon(this, vec, 0.5f);
    MR::addVelocityKeepHeight(this, vec, 150.0f, 0.5f, 200.0f);
    MR::attenuateVelocity(this, ::sChaseFric);

    if (MR::isActiveLauncherCamera()) {
        return;
    }

    if (MR::isActiveLauncherFlightCamera()) {
        return;
    }

    setNerve(GET_NERVE(StrayTico, StrayTicoNrvChase));
}

void StrayTico::exeBindMove() {
    if (MR::isFirstStep(this)) {
        MR::onCalcGravity(this);
        MR::onCalcShadow(this, nullptr);
        MR::onCalcGravity(mItemBubbleModel);
        MR::onCalcShadow(mItemBubbleModel, nullptr);
    }
    MR::zeroVelocity(this);
}

void StrayTico::exeBindEnd() {
    MR::addVelocityToGravity(this, 1.0f);
    MR::attenuateVelocity(this, 0.995f);

    if (MR::isBindedGround(this)) {
        MR::zeroVelocity(this);
        MR::offCalcGravity(this);
        MR::offCalcShadow(this, nullptr);
        MR::offCalcGravity(mItemBubbleModel);
        MR::offCalcShadow(mItemBubbleModel, nullptr);
        setNerve(GET_NERVE(StrayTico, StrayTicoNrvWait));
    }
}

void StrayTico::exeCompleteDemo() {
    if (MR::isFirstStep(this)) {
        MR::invalidateHitSensors(this);
        MR::tryStartBck(this, "CompleteDemo", nullptr);
        MR::offBind(this);
        MR::zeroVelocity(this);
    }

    if (MR::isLessStep(this, ::sCompletePlacementTime)) {
        TVec3f vec;
        MR::rotateVecDegree(&vec, _D4 * ::sCompleteStartRadius, _C8, _EC);
        vec.add(_BC);
        MR::vecBlend(&mPosition, _E0, vec, MR::calcNerveEaseInOutRate(this, ::sCompletePlacementTime));
    } else if (MR::isGreaterStep(this, ::sCompleteRotateStartTime)) {
        MR::rotateVecDegree(&mPosition, _D4 * MR::calcNerveValue(this, ::sCompleteRotateStartTime, ::sCompleteDemoTime, ::sCompleteStartRadius, 0.0f),
                            _C8,
                            MR::repeatDegree(_EC + MR::calcNerveEaseInValue(this, ::sCompleteRotateStartTime, ::sCompleteDemoTime, 0.0f, 900.0f)));
        mPosition.add(_BC);
    }

    TVec3f vec;
    MR::getPlayerFrontVec(&vec);
    MR::turnDirectionDegree(this, &mFrontVec, vec, ::sCompleteDemoRotate);
}

bool StrayTico::isNigeroTakeable() const {
    return isNerve(GET_NERVE(StrayTico, StrayTicoNrvWait));
}

bool StrayTico::isEnableSpin() const {
    if (isNerve(GET_NERVE(StrayTico, StrayTicoNrvWait)) || isNerve(GET_NERVE(StrayTico, StrayTicoNrvGlad)) ||
        isNerve(GET_NERVE(StrayTico, StrayTicoNrvBindEnd)) || isNerve(GET_NERVE(StrayTico, StrayTicoNrvLauncherCamera))) {
        return false;
    }

    return true;
}

bool StrayTico::isRescued() const {
    if (isNerve(GET_NERVE(StrayTico, StrayTicoNrvChase)) || isNerve(GET_NERVE(StrayTico, StrayTicoNrvLauncherCamera))) {
        return true;
    }

    return false;
}

bool StrayTico::isCompleteDemoEnd() const {
    if (isNerve(GET_NERVE(StrayTico, StrayTicoNrvCompleteDemo)) && MR::isGreaterStep(this, ::sCompleteDemoTime)) {
        return true;
    }

    return false;
}

void StrayTico::noticeEnd() {
    if (MR::isValidSwitchA(this)) {
        MR::onSwitchA(this);
    }
}