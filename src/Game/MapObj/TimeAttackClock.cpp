#include "Game/MapObj/TimeAttackClock.hpp"
#include "Game/LiveActor/LiveActor.hpp"
#include "Game/LiveActor/Nerve.hpp"
#include "Game/MapObj/CoinRotater.hpp"
#include "Game/NPC/EventDirector.hpp"
#include "Game/Screen/PopUpAddTimeAttackTime.hpp"
#include "Game/Util/ActionSoundUtil.hpp"
#include "Game/Util/ActorAnimUtil.hpp"
#include "Game/Util/ActorInitUtil.hpp"
#include "Game/Util/ActorMovementUtil.hpp"
#include "Game/Util/ActorSensorUtil.hpp"
#include "Game/Util/ActorShadowUtil.hpp"
#include "Game/Util/ActorSwitchUtil.hpp"
#include "Game/Util/EffectUtil.hpp"
#include "Game/Util/Functor.hpp"
#include "Game/Util/JMapInfo.hpp"
#include "Game/Util/JMapUtil.hpp"
#include "Game/Util/LiveActorUtil.hpp"
#include "Game/Util/MessageUtil.hpp"

namespace NrvTimeAttackClock {
    NEW_NERVE(TimeAttackClockNrvWait, TimeAttackClock, Wait);
    NEW_NERVE(TimeAttackClockNrvCollect, TimeAttackClock, Collect);
}  // namespace NrvTimeAttackClock

TimeAttackClock::TimeAttackClock(const char* pName) : LiveActor(pName), mTimePopup(nullptr), mTimeToAdd(600) {
    _90.identity();
    _C0.identity();
    MR::createCoinRotater();
}

void TimeAttackClock::init(const JMapInfoIter& rIter) {
    MR::initActor(this, rIter, "TimeAttackClock", false);
    MR::makeMtxTR(_90, this);
    initNerve(GET_NERVE(TimeAttackClock, TimeAttackClockNrvWait));
    MR::setAllEffectHostMtx(this, _C0);

    s32 arg1 = -1;
    if (MR::getJMapInfoArg1NoInit(rIter, &arg1)) {
        MR::onCalcShadowAll(this);
    }

    mTimePopup = new PopUpAddTimeAttackTime("タイムアタック時間加算ポップアップ", 0.0f);
    mTimePopup->initWithoutIter();

    if (MR::isValidSwitchAppear(this)) {
        MR::listenStageSwitchOnAppear(this, MR::Functor(this, &TimeAttackClock::appear));
        makeActorDead();
    } else {
        makeActorAppeared();
    }
}

void TimeAttackClock::appear() {
    LiveActor::appear();
}

void TimeAttackClock::calcAndSetBaseMtx() {
    if (isNerve(GET_NERVE(TimeAttackClock, TimeAttackClockNrvWait))) {
        _C0.concat(_90, MR::getCoinInWaterRotateYMatrix());
    }

    MR::setBaseTRMtx(this, _C0);
}

void TimeAttackClock::exeWait() {
    if (MR::isFirstStep(this)) {
        MR::startAction(this, "Wait");
    }
}

void TimeAttackClock::exeCollect() {
    if (MR::isFirstStep(this)) {
        MR::startAction(this, "Get");
    }

    if (MR::isStep(this, 1)) {
        kill();
    }
}

void TimeAttackClock::addTimer() {
    char messageID[0x20];
    MR::getLayoutMessageID(messageID, "CollectCounter", "AddTimer");
    mTimePopup->show(MR::getGameMessageDirect(messageID));
    mTimePopup->setTextBoxArgNumber(mTimeToAdd / 60);
    MR::startActionSound(this, "Caught");
    MR::addCometTimer(mTimeToAdd);
    setNerve(GET_NERVE(TimeAttackClock, TimeAttackClockNrvCollect));
}

void TimeAttackClock::attackSensor(HitSensor* pSender, HitSensor* pReceiver) {
    if (!isNerve(GET_NERVE(TimeAttackClock, TimeAttackClockNrvWait))) {
        return;
    }

    if (MR::isSensorYoshi(pReceiver)) {
        MR::sendMsgPush(pReceiver, pSender);
        return;
    }

    if (MR::isSensorPlayer(pReceiver)) {
        addTimer();
    }
}

bool TimeAttackClock::receiveMsgPlayerAttack(u32 msg, HitSensor* pSender, HitSensor* pReceiver) {
    return MR::isMsgStarPieceReflect(msg);
}
