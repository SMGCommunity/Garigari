#include "Game/MapObj/WanwanGoal.hpp"
#include "Game/LiveActor/Nerve.hpp"
#include "Game/Util/ActorInitUtil.hpp"
#include "Game/Util/ActorMovementUtil.hpp"
#include "Game/Util/ActorSensorUtil.hpp"
#include "Game/Util/LiveActorUtil.hpp"

namespace NrvWanwanGoal {
    NEW_NERVE(WanwanGoalNrvWait, WanwanGoal, Wait);
};  // namespace NrvWanwanGoal

WanwanGoal::WanwanGoal(const char* pName) : LiveActor(pName), mIsActive() {
}

void WanwanGoal::init(const JMapInfoIter& rIter) {
    MR::initActor(this, rIter, false);
    initNerve(GET_NERVE(WanwanGoal, WanwanGoalNrvWait));
    MR::calcGravity(this);
    makeActorAppeared();
}

void WanwanGoal::attackSensor(HitSensor* pSender, HitSensor* pReceiver) {
    if (mIsActive) {
        return;
    }

    f32 senderRadius = MR::getSensorRadius(pSender);

    if (!(MR::calcDistance(pSender, pReceiver, nullptr) <= senderRadius)) {
        return;
    }

    if (MR::sendArbitraryMsg(ACTMES_WANWAN_GOAL, pReceiver, pSender)) {
        mIsActive = true;
    }
}

void WanwanGoal::exeWait() {
}
