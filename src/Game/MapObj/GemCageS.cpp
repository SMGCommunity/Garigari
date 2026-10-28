#include "Game/MapObj/GemCageS.hpp"
#include "Game/LiveActor/Nerve.hpp"
#include "Game/LiveActor/BreakModel.hpp"
#include "Game/Util/ActorInitUtil.hpp"
#include "Game/Util/JMapUtil.hpp"
#include "Game/Util/LiveActorUtil.hpp"
#include "Game/Util/ObjUtil.hpp"
#include "Game/Util/ActorSensorUtil.hpp"
#include "Game/Util/ActorAnimUtil.hpp"
#include "Game/Util/ActorMovementUtil.hpp"
#include "Game/Util/ActionSoundUtil.hpp"
#include "Game/Util/ActorSwitchUtil.hpp"

namespace NrvGemCageS {
    NEW_NERVE(GemCageSNrvWait, GemCageS, Wait);
    NEW_NERVE(GemCageSNrvBreak, GemCageS, Break);
};  // namespace NrvGemCageS

GemCageS::GemCageS(const char* pName) : LiveActor(pName), mBreakModel(), mItemType(-1), mIsRockCage() {

}

void GemCageS::init(const JMapInfoIter& rIter) {
    MR::initActor(this, rIter, false);
    mIsRockCage = MR::isObjectName(rIter, "RockCageS");

    initNerve(GET_NERVE(GemCageS, GemCageSNrvWait));

    mBreakModel = MR::createBreakModel(this, nullptr);

    MR::getJMapInfoArg0NoInit(rIter, &mItemType);

    switch(mItemType) {
    case ITEM_TYPE_STAR_PIECE:
        MR::declareStarPiece(this, 5);
        break;
    case ITEM_TYPE_COIN:
        MR::declareCoin(this, 1);
        break;
    }

    makeActorAppeared();
}

bool GemCageS::receiveMsgPlayerAttack(u32 msg, HitSensor* pSender, HitSensor* pReceiver) {
    if (!isNerve(GET_NERVE(GemCageS, GemCageSNrvWait))) {
        return false;
    }

    if (MR::isMsgRockAttack(msg)) {
        if (MR::isEqualSensor(pReceiver, this, "Collision")) {
            setNerve(GET_NERVE(GemCageS, GemCageSNrvBreak));
            return true;
        }

        return false;
    }
    
    if (!mIsRockCage && MR::isMsgPlayerHitAll(msg)) {
        setNerve(GET_NERVE(GemCageS, GemCageSNrvBreak));
        return true;
    }

    return false;
}

void GemCageS::attackSensor(HitSensor* pSender, HitSensor* pReceiver) {
    if (!MR::isSensorRide(pReceiver)) {
        MR::sendMsgPush(pReceiver, pSender);
    }
}

bool GemCageS::appearItem() {
    if (mItemType == ITEM_TYPE_STAR_PIECE) {
        MR::appearStarPiece(this, mPosition, 5, 10.0f, 40.0f, false);
        return true;
    }
    else if (mItemType == ITEM_TYPE_COIN) {
        MR::appearCoinPop(this, mPosition, 1);
        return true;
    }
    else {
        return false;
    }
}

void GemCageS::exeWait() {
    if (MR::isFirstStep(this)) {
        const char* pAnimName = mIsRockCage ? "RockCageS" : "GemCageS";
        MR::startBvaAndSetFrameAndStop(this, pAnimName, 0.0f);
    }

    TVec3f unused;
    MR::calcUpVec(&unused, this);
}

void GemCageS::exeBreak() {
    if (MR::isFirstStep(this)) {
        const char* pAnimName = mIsRockCage ? "RockCageS" : "GemCageS";
        MR::startBvaAndSetFrameAndStop(this, pAnimName, 1.0f);

        MR::startActionSound(this, "Break");

        MR::invalidateCollisionParts(this);
        MR::invalidateHitSensors(this);

        mBreakModel->appear();

        if (MR::isValidSwitchDead(this)) {
            MR::onSwitchDead(this);
        }

        appearItem();
    }
}
