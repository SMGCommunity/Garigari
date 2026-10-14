#pragma once

#include <revolution/types.h>

class ActorStateBaseInterface;
class Nerve;

class ActorStateKeeper {
public:
    struct State {
        /* 0x0 */ ActorStateBaseInterface* mInterface;
        /* 0x4 */ const Nerve* mNerve;
        /* 0x8 */ const char* mName;
    };

    ActorStateKeeper(int);

    void addState(ActorStateBaseInterface*, const Nerve*, const char*);
    bool updateCurrentState();
    void startState(const Nerve*);
    bool isStateDead() const;
    void endState();
    ActorStateKeeper::State* findStateInfo(const Nerve*);

    /* 0x0 */ s32 mStatesCapacity;
    /* 0x4 */ s32 mLength;
    /* 0x8 */ State* mStates;
    /* 0xC */ State* mCurrentState;
};
