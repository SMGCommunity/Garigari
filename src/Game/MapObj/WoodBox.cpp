#include "Game/MapObj/WoodBox.hpp"
#include "Game/LiveActor/BreakModel.hpp"
#include "Game/LiveActor/LiveActor.hpp"
#include "Game/LiveActor/ModelObj.hpp"
#include "Game/LiveActor/Nerve.hpp"
#include "Game/MapObj/BenefitItemOneUp.hpp"
#include "Game/Util/ActionSoundUtil.hpp"
#include "Game/Util/ActorAnimUtil.hpp"
#include "Game/Util/ActorInitUtil.hpp"
#include "Game/Util/ActorMovementUtil.hpp"
#include "Game/Util/ActorSensorUtil.hpp"
#include "Game/Util/ActorSwitchUtil.hpp"
#include "Game/Util/DemoUtil.hpp"
#include "Game/Util/EffectUtil.hpp"
#include "Game/Util/JMapUtil.hpp"
#include "Game/Util/LiveActorUtil.hpp"
#include "Game/Util/MtxUtil.hpp"
#include "Game/Util/ObjUtil.hpp"
#include "Game/Util/SupportPlayUtil.hpp"
#include "JSystem/JGeometry/TMatrix.hpp"
#include "JSystem/JGeometry/TVec.hpp"
#include "revolution/mtx.h"
#include "revolution/types.h"

class BenefitItemObj;

namespace NrvWoodBox {
    NEW_NERVE(WoodBoxNrvWait, WoodBox, Wait);
    NEW_NERVE(WoodBoxNrvHit, WoodBox, Hit);
    NEW_NERVE(WoodBoxNrvKilled, WoodBox, Killed);
};  // namespace NrvWoodBox

WoodBox::WoodBox(const char* pName) : LiveActor(pName) {
}

void WoodBox::init(const JMapInfoIter& rIter) {
    MR::initActor(this, rIter, false);
    initNerve(GET_NERVE(WoodBox, WoodBoxNrvWait));

    long arg0_CoinCount = 1;
    long arg1_RemnantsType = -1;
    long arg2_StarPieceCount = 0;
    long arg3_SFXType = 0;
    long arg4_OneUpType = 0;
    long arg7_PowerStarID = 0;

    if (MR::isValidInfo(rIter)) {
        MR::getJMapInfoArg0NoInit(rIter, &arg0_CoinCount);
        MR::getJMapInfoArg1NoInit(rIter, &arg1_RemnantsType);
        MR::getJMapInfoArg2NoInit(rIter, &arg2_StarPieceCount);
        MR::getJMapInfoArg3NoInit(rIter, &arg3_SFXType);
        MR::getJMapInfoArg4NoInit(rIter, &arg4_OneUpType);
        MR::getJMapInfoArg7NoInit(rIter, &arg7_PowerStarID);
    }

    PSMTXCopy(getBaseMtx(), mBaseMtx);
    MR::addTransMtx(mBaseMtx, TVec3f(0.0f, 100.0f, 0.0f));
    mHasPowerStar = false;

    if (arg7_PowerStarID != 0) {
        mHasPowerStar = true;
        MR::declarePowerStar(this);
        mStarDemoModel = MR::createPowerStarDemoModel(this, "パワースターデモモデル", mBaseMtx);
        mStarDemoModel->makeActorDead();
    }

    mCoinCount = arg0_CoinCount;
    mStarPieceCount = arg2_StarPieceCount;
    s32 arg4 = arg4_OneUpType;
    mHitPoint = 1;
    mShowBrokenRemnants = true;

    if (arg1_RemnantsType == 0) {
        mShowBrokenRemnants = false;
    }

    mPlayRiddleSFX = false;

    if (arg3_SFXType == 1) {
        mPlayRiddleSFX = true;
    }

    mBreakModel = MR::createBreakModel(this, nullptr);
    mFloorTouchTimer = 0;
    MR::setClippingFar200m(this);
    MR::validateClipping(this);

    if (mCoinCount != 0) {
        MR::declareCoin(this, mCoinCount);
    }

    if (mStarPieceCount != 0) {
        MR::declareStarPiece(this, mStarPieceCount);
    }

    if (arg4 != 0) {
        mOneUp = MR::createKinokoOneUp();
    } else {
        mOneUp = nullptr;
    }

    makeActorAppeared();
}

void WoodBox::control() {
    if (mFloorTouchTimer != 0) {
        mFloorTouchTimer--;
    }
}

void WoodBox::exeHit() {
    if (MR::isFirstStep(this)) {
        MR::invalidateHitSensor(this, "Body");

        if (mHasPowerStar) {
            mStarDemoModel->makeActorAppeared();
        }
    }

    if (MR::isStep(this, 15)) {
        TVec3f up_20 = TVec3f(0.0f);
        MR::calcUpVec(&up_20, this);

        if (mCoinCount != 0) {
            MR::appearCoinPopToDirection(this, mPosition, up_20, mCoinCount);
        }

        if (mStarPieceCount != 0) {
            MR::appearStarPieceToDirection(this, mPosition, up_20, mStarPieceCount, 10.0f, 40.0f, false);
        }

        if (mOneUp != nullptr) {
            TVec3f up_14;
            MR::calcUpVec(&up_14, this);

            TPos3f spawnMtx;
            PSMTXCopy(getBaseMtx(), spawnMtx);
            MR::addTransMtx(spawnMtx, up_14 * 50.0f);
            MR::appearKinokoOneUpHop(mOneUp, spawnMtx);
        }

        if (MR::isValidSwitchDead(this)) {
            MR::onSwitchDead(this);
        }

        if (mPlayRiddleSFX) {
            MR::startActionSound(this, "SyReadRiddleS");
        }
    }

    if (MR::isDead(mBreakModel)) {
        kill();
    }
}

void WoodBox::appear() {
    mFloorTouchTimer = 0;
    mHitPoint = 1;
    mBreakModel->kill();
    MR::validateCollisionParts(this);
    MR::validateHitSensors(this);
    MR::startBvaAndSetFrameAndStop(this, "Dust", 0.0f);
    setNerve(GET_NERVE(WoodBox, WoodBoxNrvWait));
    LiveActor::appear();
}

void WoodBox::kill() {
    if (!mShowBrokenRemnants) {
        LiveActor::kill();
    } else {
        setNerve(GET_NERVE(WoodBox, WoodBoxNrvKilled));
        MR::invalidateHitSensors(this);
        MR::invalidateCollisionParts(this);
    }

    if (mHasPowerStar) {
        mStarDemoModel->makeActorDead();
        MR::requestAppearPowerStar(this, mPosition);
    }
}

void WoodBox::doHit() {
    // FIXME
    // decomp.me: https://decomp.me/scratch/0XD2p
    // In objdiff, this function is 99.58% matching if the "Function relocation diffs" option is set to "Name or address", and 99.68% matching if it's
    // set to "Data value". Everything is matching except for the data labels for the strings and floats. In decomp.me, this function is 99.68%
    // matching. The wrong numbers are being added to the memory address stored in r31.

    if (mHitPoint == 0) {
        return;
    }

    mHitPoint--;

    if (mHitPoint == 0) {
        MR::invalidateCollisionParts(this);
    }

    if (MR::isInWater(this, TVec3f(0.0f, 0.0f, 0.0f))) {
        MR::startActionSound(this, "OjWoodBoxBreakW");
    } else {
        MR::startActionSound(this, "OjWoodBoxBreak");
    }

    if (!MR::isInWater(this, TVec3f(0.0f, 0.0f, 0.0f))) {
        MR::startActionSound(this, "EmExplodeS");
    }

    mBreakModel->appear();

    if (MR::isInWater(this, TVec3f(0.0f, 0.0f, 0.0f))) {
        MR::emitEffect(mBreakModel, "BreakWater");
    } else {
        MR::emitEffect(mBreakModel, "Break");
    }

    if (mShowBrokenRemnants) {
        MR::startBva(this, "Dust");
    } else {
        MR::hideModel(this);
    }

    setNerve(GET_NERVE(WoodBox, WoodBoxNrvHit));
}

bool WoodBox::receiveMsgPlayerAttack(u32 msg, HitSensor* pSender, HitSensor* pReceiver) {
    if (mHitPoint == 0) {
        return false;
    }

    if (MR::isMsgPlayerUpperPunch(msg)) {
        doHit();
        MR::sendMsgReflectV(pSender, pReceiver);
        return true;
    }

    if (MR::isMsgFireBallAttack(msg)) {
        doHit();
        return false;
    }

    if (MR::isMsgPlayerHitAll(msg)) {
        doHit();
        return true;
    }

    if (MR::isMsgPlayerHipDrop(msg) || MR::isMsgPlayerHipDropFloor(msg)) {
        if (mFloorTouchTimer != 0) {
            doHit();
            return true;
        }

        return true;
    }

    return false;
}

bool WoodBox::receiveMsgEnemyAttack(u32 msg, HitSensor* pSender, HitSensor* pReceiver) {
    if (mHitPoint != 0) {
        doHit();
        return true;
    } else {
        return false;
    }
}

bool WoodBox::receiveOtherMsg(u32 msg, HitSensor* pSender, HitSensor* pReceiver) {
    if (MR::isMsgFloorTouch(msg)) {
        mFloorTouchTimer = 2;
    }

    return false;
}

void WoodBox::forceReappear() {
    if (!isNerve(GET_NERVE(WoodBox, WoodBoxNrvWait))) {
        if (!MR::isDead(mBreakModel)) {
            mBreakModel->kill();
        }

        MR::emitEffect(this, "Appear");
        MR::startActionSound(this, "Appear");
    }

    appear();
}

void WoodBox::registerBreakModelDemoCast() {
    MR::registerDemoSimpleCastAll(mBreakModel);
}

void WoodBox::exeKilled() {
}

void WoodBox::exeWait() {
    MR::attachSupportTicoToTarget(this);
}
