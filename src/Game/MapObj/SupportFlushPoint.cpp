#include "Game/MapObj/SupportFlushPoint.hpp"
#include "Game/LiveActor/LiveActor.hpp"
#include "Game/LiveActor/Nerve.hpp"
#include "Game/Util/ActorAnimUtil.hpp"
#include "Game/Util/ActorInitUtil.hpp"
#include "Game/Util/ActorSensorUtil.hpp"
#include "Game/Util/JMapUtil.hpp"
#include "Game/Util/LiveActorUtil.hpp"
#include "Game/Util/ObjUtil.hpp"
#include "Game/Util/SupportPlayUtil.hpp"

namespace NrvSupportFlushPoint {
    NEW_NERVE(SupportFlushPointNrvAppear, SupportFlushPoint, Appear);
    NEW_NERVE(SupportFlushPointNrvHide, SupportFlushPoint, Hide);
    NEW_NERVE(SupportFlushPointNrvWait, SupportFlushPoint, Wait);
    NEW_NERVE(SupportFlushPointNrvGenerateItem, SupportFlushPoint, GenerateItem);
    NEW_NERVE(SupportFlushPointNrvDisappear, SupportFlushPoint, Disappear);
};  // namespace NrvSupportFlushPoint

SupportFlushPoint::SupportFlushPoint(const char* pName) : LiveActor(pName), mItemType(ITEM_TYPE_STAR_PIECE) {
    MR::joinSupportPlayGroup(this);
}

void SupportFlushPoint::init(const JMapInfoIter& rIter) {
    MR::initActor(this, rIter, false);

    initNerve(GET_NERVE(SupportFlushPoint, SupportFlushPointNrvWait));

    MR::getJMapInfoArg0WithInit(rIter, &mItemType);

    switch (mItemType) {
    case ITEM_TYPE_STAR_PIECE:
        MR::declareStarPiece(this, 3);
        break;
    case ITEM_TYPE_COIN:
        MR::declareCoin(this, 1);
        break;
    }

    makeActorDead();
}

void SupportFlushPoint::control() {
}

bool SupportFlushPoint::receiveMsgPlayerAttack(u32 msg, HitSensor* pSender, HitSensor* pReceiver) {
    if (MR::isMsgSupportTicoSpin(msg) && isNerve(GET_NERVE(SupportFlushPoint, SupportFlushPointNrvWait))) {
        setNerve(GET_NERVE(SupportFlushPoint, SupportFlushPointNrvGenerateItem));

        return true;
    }

    return false;
}

bool SupportFlushPoint::receiveOtherMsg(u32 msg, HitSensor* pSender, HitSensor* pReceiver) {
    if (MR::isMsgSupportPlayGroupStart(msg) && !isNerve(GET_NERVE(SupportFlushPoint, SupportFlushPointNrvDisappear))) {
        setNerve(GET_NERVE(SupportFlushPoint, SupportFlushPointNrvAppear));
        appear();
        return true;
    }

    if (MR::isMsgSupportPlayGroupStop(msg) && !isNerve(GET_NERVE(SupportFlushPoint, SupportFlushPointNrvDisappear))) {
        setNerve(GET_NERVE(SupportFlushPoint, SupportFlushPointNrvHide));
        return true;
    }

    return false;
}

void SupportFlushPoint::exeAppear() {
    if (MR::isFirstStep(this)) {
        MR::startAction(this, "Appear");
    }

    if (MR::isActionEnd(this)) {
        setNerve(GET_NERVE(SupportFlushPoint, SupportFlushPointNrvWait));
    }
}

void SupportFlushPoint::exeHide() {
    if (MR::isFirstStep(this)) {
        MR::startAction(this, "Hide");
    }

    if (MR::isActionEnd(this)) {
        kill();
    }
}

void SupportFlushPoint::exeWait() {
    if (MR::isFirstStep(this)) {
        MR::startAction(this, "Wait");
    }

    MR::attachSupportTicoToTarget(this);
}

void SupportFlushPoint::exeGenerateItem() {
    if (MR::isFirstStep(this)) {
        MR::startAction(this, "GenerateItem");

        switch (mItemType) {
        case ITEM_TYPE_STAR_PIECE:
            MR::appearStarPiece(this, mPosition, 3, 10.0f, 40.0f, false);
            break;
        case ITEM_TYPE_COIN:
            MR::appearCoinPop(this, mPosition, 1);
            break;
        default:
            break;
        }
    }

    if (MR::isActionEnd(this)) {
        setNerve(GET_NERVE(SupportFlushPoint, SupportFlushPointNrvDisappear));
        kill();
    }
}

void SupportFlushPoint::exeDisappear() {
}
