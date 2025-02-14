#pragma once

#include <revolution.h>

class ActorStateBaseInterface;
class Nerve;

class ActorStateKeeper {
public:
    struct State {
        ActorStateBaseInterface* mInterface;        // 0x00
        const Nerve* mNerve;                        // 0x04
        const char* mStateName;                     // 0x08
    };

    ActorStateKeeper(int);

    void addState(ActorStateBaseInterface *, const Nerve *, const char *);
    bool updateCurrentState();
    void startState(const Nerve *);
    bool isStateDead() const;
    void endState();
    ActorStateKeeper::State* findStateInfo(const Nerve *);

    int mMaxStates;             // 0x00
    int mNumStates;             // 0x04
    State* mStates;             // 0x08
    State* mCurrentState;       // 0x0C
};
