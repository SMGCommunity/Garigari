#include "LiveActor/ActorStateKeeper.hpp"
#include "LiveActor/ActorStateBase.hpp"

ActorStateKeeper::ActorStateKeeper(int capacity)
	: mMaxStates(capacity), mNumStates(0), mStates(nullptr), mCurrentState(nullptr) {
	mStates = new State [capacity];
	for(s32 i = 0; i < mMaxStates; i++) {
		State& e = mStates[i];
		e.mInterface = nullptr;
		e.mNerve = nullptr;
		e.mStateName = nullptr;
	}
}

void ActorStateKeeper::addState(ActorStateBaseInterface* pInterface, const Nerve* pNerve, const char* pName) {
	State& e = mStates[mNumStates];
	e.mInterface = pInterface;
	e.mNerve = pNerve;
	e.mStateName = pName;
	mNumStates += 1;
}

bool ActorStateKeeper::updateCurrentState() {
    return (!mCurrentState) ? false : (mCurrentState->mInterface)->update();
}

void ActorStateKeeper::startState(const Nerve *pNerve) {
    mCurrentState = findStateInfo(pNerve);

    if (mCurrentState != nullptr) {
        ActorStateBaseInterface* interface = mCurrentState->mInterface;
        interface->appear();
    }
}

bool ActorStateKeeper::isStateDead() const {
    if (mCurrentState != nullptr) {
        return mCurrentState->mInterface->mIsDead;
    }
    else {
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

ActorStateKeeper::State* ActorStateKeeper::findStateInfo(const Nerve *pNerve) {
	for(int i = 0; i < mNumStates; i++) {
		if(mStates[i].mNerve == pNerve) return &mStates[i];
	}
	return NULL;
}
