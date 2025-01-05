#include "LiveActor/Spine.hpp"
#include "LiveActor/ActorStateKeeper.hpp"
#include "LiveActor/Nerve.hpp"

Spine::Spine(void *pExecutor, const Nerve *pNextNerve, s32 numStates) {
    mExecutor = pExecutor;
    mCurrentNerve = nullptr;
    mNextNerve = pNextNerve;
    mCurrentStep = 0;
    mStateKeeper = nullptr;

    if (numStates > 0) {
        mStateKeeper = new ActorStateKeeper(numStates);
    }
}

void Spine::update() {
    changeNerve();
    mCurrentNerve->execute(this);
    mCurrentStep++;
    changeNerve();
}

void Spine::setNerve(const Nerve *pNerve) {
    if (mCurrentStep >= 0 && mCurrentNerve != nullptr) {
        mCurrentNerve->executeOnEnd(this);
    }

    mNextNerve = pNerve;
    mCurrentStep = -1;
}

const Nerve* Spine::getCurrentNerve() const {
    if (mNextNerve != nullptr) {
        return mNextNerve;
    }

    return mCurrentNerve;
}

void Spine::changeNerve() {
    if (mNextNerve != nullptr) {
        if (mStateKeeper != nullptr) {
            mStateKeeper->endState();
            mStateKeeper->startState(mNextNerve);
        }

        mCurrentNerve = mNextNerve;
        mNextNerve = nullptr;
        mCurrentStep = 0;
    }
}
