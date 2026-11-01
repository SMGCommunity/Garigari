#pragma once

class LiveActor;

class ActorAppearSwitchListener {
public:
    ActorAppearSwitchListener(LiveActor*, bool, bool);

    virtual void listenSwitchOnEvent();
    virtual void listenSwitchOffEvent();

    /* 0x04 */ LiveActor* mActor;
    /* 0x08 */ bool mUsesOn;
    /* 0x09 */ bool mUsesOff;
};
