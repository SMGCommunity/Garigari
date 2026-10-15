#include "Game/LiveActor/Spine.hpp"
#include "Game/LiveActor/ActorStateKeeper.hpp"
#include "Game/LiveActor/Nerve.hpp"

Spine::Spine(void* pExecutor, const Nerve* pNerve, s32 numStates) : mExecutor(pExecutor), mCurrNerve(), mNextNerve(pNerve), mStep(), mStateKeeper() {
    if (numStates > 0) {
        mStateKeeper = new ActorStateKeeper(numStates);
    }
}

void Spine::update() {
    changeNerve();
    mCurrNerve->execute(this);
    mStep++;
    changeNerve();
}

void Spine::setNerve(const Nerve* pNerve) {
    if (mStep >= 0 && mCurrNerve != nullptr) {
        mCurrNerve->executeOnEnd(this);
    }

    mNextNerve = pNerve;
    mStep = -1;
}

const Nerve* Spine::getCurrentNerve() const {
    if (mNextNerve != nullptr) {
        return mNextNerve;
    }

    return mCurrNerve;
}

void Spine::changeNerve() {
    if (mNextNerve != nullptr) {
        if (mStateKeeper != nullptr) {
            mStateKeeper->endState();
            mStateKeeper->startState(mNextNerve);
        }

        mCurrNerve = mNextNerve;
        mNextNerve = nullptr;
        mStep = 0;
    }
}
