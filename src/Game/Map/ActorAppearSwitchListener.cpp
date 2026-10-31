#include "Game/Map/ActorAppearSwitchListener.hpp"
#include "Game/LiveActor/LiveActor.hpp"
#include "Game/Util/LiveActorUtil.hpp"

ActorAppearSwitchListener::ActorAppearSwitchListener(LiveActor* pActor, bool appearIfDead, bool killIfAlive)
    : mLiveActor(pActor), mAppearIfDead(appearIfDead), mKillIfAlive(killIfAlive) {
}

void ActorAppearSwitchListener::listenSwitchOnEvent() {
    if (MR::isDead(mLiveActor) && mAppearIfDead) {
        mLiveActor->appear();
    }
}

void ActorAppearSwitchListener::listenSwitchOffEvent() {
    if (!MR::isDead(mLiveActor) && mKillIfAlive) {
        mLiveActor->kill();
    }
}
