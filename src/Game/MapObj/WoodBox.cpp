#include "Game/MapObj/WoodBox.hpp"
#include "Game/LiveActor/BreakModel.hpp"
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

    s32 arg0 = 1;
    s32 arg1 = -1;
    s32 arg2 = 0;
    s32 arg3 = 0;
    s32 arg4 = 0;
    s32 arg7 = 0;

    if (MR::isValidInfo(rIter)) {
        MR::getJMapInfoArg0NoInit(rIter, &arg0);
        MR::getJMapInfoArg1NoInit(rIter, &arg1);
        MR::getJMapInfoArg2NoInit(rIter, &arg2);
        MR::getJMapInfoArg3NoInit(rIter, &arg3);
        MR::getJMapInfoArg4NoInit(rIter, &arg4);
        MR::getJMapInfoArg7NoInit(rIter, &arg7);
    }

    PSMTXCopy(getBaseMtx(), mBaseMtx);
    MR::addTransMtx(mBaseMtx, TVec3f(0.0f, 100.0f, 0.0f));
    mHasPowerStar = false;

    if (arg7 != 0) {
        mHasPowerStar = true;
        MR::declarePowerStar(this);
        mPowerStarDemoModel = MR::createPowerStarDemoModel(this, "パワースターデモモデル", mBaseMtx);
        mPowerStarDemoModel->makeActorDead();
    }

    mAppearCoinNum = arg0;
    mAppearStarPieceNum = arg2;
    s32 oneUpType = arg4;
    mHP = 1;
    mIsShowDust = true;

    if (arg1 == 0) {
        mIsShowDust = false;
    }

    mCanPlayRiddleSE = false;

    if (arg3 == 1) {
        mCanPlayRiddleSE = true;
    }

    mBreakModel = MR::createBreakModel(this, nullptr);
    mFloorTouchTimer = 0;
    MR::setClippingFar200m(this);
    MR::validateClipping(this);

    if (mAppearCoinNum != 0) {
        MR::declareCoin(this, mAppearCoinNum);
    }

    if (mAppearStarPieceNum != 0) {
        MR::declareStarPiece(this, mAppearStarPieceNum);
    }

    if (oneUpType != 0) {
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
            mPowerStarDemoModel->makeActorAppeared();
        }
    }

    if (MR::isStep(this, 15)) {
        TVec3f up = TVec3f(0.0f);
        MR::calcUpVec(&up, this);

        if (mAppearCoinNum != 0) {
            MR::appearCoinPopToDirection(this, mPosition, up, mAppearCoinNum);
        }

        if (mAppearStarPieceNum != 0) {
            MR::appearStarPieceToDirection(this, mPosition, up, mAppearStarPieceNum, 10.0f, 40.0f, false);
        }

        if (mOneUp != nullptr) {
            TVec3f up;
            MR::calcUpVec(&up, this);

            TPos3f spawnMtx;
            PSMTXCopy(getBaseMtx(), spawnMtx);
            MR::addTransMtx(spawnMtx, up * 50.0f);
            MR::appearKinokoOneUpHop(mOneUp, spawnMtx);
        }

        if (MR::isValidSwitchDead(this)) {
            MR::onSwitchDead(this);
        }

        if (mCanPlayRiddleSE) {
            MR::startActionSound(this, "SyReadRiddleS");
        }
    }

    if (MR::isDead(mBreakModel)) {
        kill();
    }
}

void WoodBox::appear() {
    mFloorTouchTimer = 0;
    mHP = 1;
    mBreakModel->kill();
    MR::validateCollisionParts(this);
    MR::validateHitSensors(this);
    MR::startBvaAndSetFrameAndStop(this, "Dust", 0.0f);
    setNerve(GET_NERVE(WoodBox, WoodBoxNrvWait));
    LiveActor::appear();
}

void WoodBox::kill() {
    if (!mIsShowDust) {
        LiveActor::kill();
    } else {
        setNerve(GET_NERVE(WoodBox, WoodBoxNrvKilled));
        MR::invalidateHitSensors(this);
        MR::invalidateCollisionParts(this);
    }

    if (mHasPowerStar) {
        mPowerStarDemoModel->makeActorDead();
        MR::requestAppearPowerStar(this, mPosition);
    }
}

void WoodBox::doHit() {
    if (mHP == 0) {
        return;
    }

    mHP--;

    if (mHP == 0) {
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

    if (mIsShowDust) {
        MR::startBva(this, "Dust");
    } else {
        MR::hideModel(this);
    }

    setNerve(GET_NERVE(WoodBox, WoodBoxNrvHit));
}

bool WoodBox::receiveMsgPlayerAttack(u32 msg, HitSensor* pSender, HitSensor* pReceiver) {
    if (mHP == 0) {
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
    if (mHP != 0) {
        doHit();
        return true;
    }
    
    return false;
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
