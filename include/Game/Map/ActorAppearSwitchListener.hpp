#pragma once

class LiveActor;

class ActorAppearSwitchListener {
public:
    ActorAppearSwitchListener(LiveActor*, bool, bool);

    virtual void listenSwitchOnEvent();
    virtual void listenSwitchOffEvent();

    /* 0x04 */ LiveActor* mLiveActor;
    /* 0x08 */ bool mAppearIfDead;
    /* 0x09 */ bool mKillIfAlive;
};
