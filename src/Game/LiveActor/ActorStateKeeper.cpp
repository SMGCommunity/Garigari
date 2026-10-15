#include "Game/LiveActor/ActorStateKeeper.hpp"
#include "Game/LiveActor/ActorStateBase.hpp"

ActorStateKeeper::ActorStateKeeper(int capacity) : mStatesCapacity(capacity), mLength(), mStates(), mCurrentState() {
    mStates = new State[capacity];
    for (s32 i = 0; i < mStatesCapacity; i++) {
        State& e = mStates[i];
        e.mInterface = nullptr;
        e.mNerve = nullptr;
        e.mName = nullptr;
    }
}

void ActorStateKeeper::addState(ActorStateBaseInterface* pInterface, const Nerve* pNerve, const char* pName) {
    State& e = mStates[mLength];
    e.mInterface = pInterface;
    e.mNerve = pNerve;
    e.mName = pName;
    mLength += 1;
}

bool ActorStateKeeper::updateCurrentState() {
    return (!mCurrentState) ? false : (mCurrentState->mInterface)->update();
}

void ActorStateKeeper::startState(const Nerve* pNerve) {
    mCurrentState = findStateInfo(pNerve);

    if (mCurrentState != nullptr) {
        ActorStateBaseInterface* interface = mCurrentState->mInterface;
        interface->appear();
    }
}

bool ActorStateKeeper::isStateDead() const {
    if (mCurrentState != nullptr) {
        return mCurrentState->mInterface->mIsDead;
    } else {
        return true;
    }
}

void ActorStateKeeper::endState() {
    if (mCurrentState != nullptr) {
        ActorStateBaseInterface* interface = mCurrentState->mInterface;
        if (!interface->mIsDead) {
            interface->kill();
            mCurrentState = nullptr;
        }
    }
}

ActorStateKeeper::State* ActorStateKeeper::findStateInfo(const Nerve* pNerve) {
    for (int i = 0; i < mLength; i++) {
        if (mStates[i].mNerve == pNerve) {
            return &mStates[i];
        }
    }

    return nullptr;
}
