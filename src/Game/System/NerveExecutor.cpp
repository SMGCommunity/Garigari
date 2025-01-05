#include "System/NerveExecutor.hpp"
#include "LiveActor/Spine.hpp"

NerveExecutor::NerveExecutor(const char *) {
    mSpine = nullptr;
}

NerveExecutor::~NerveExecutor() {
    delete mSpine;
}

void NerveExecutor::initNerve(const Nerve *pNerve, s32 numStates) {
    mSpine = new Spine(this, pNerve, numStates);
}

void NerveExecutor::updateNerve() {
    if (mSpine != nullptr) {
        mSpine->update();
    }
}

void NerveExecutor::setNerve(const Nerve *pNerve) {
    mSpine->setNerve(pNerve);
}

bool NerveExecutor::isNerve(const Nerve *pNerve) const {
    return mSpine->getCurrentNerve() == pNerve;
}

s32 NerveExecutor::getNerveStep() const {
    return mSpine->mCurrentStep;
}
