#include "Map/SwitchSynchronizer.hpp"
#include "Map/StageSwitch.hpp"
#include "Util.hpp"

SwitchSynchronizer::SwitchSynchronizer(const char *pName) : NameObj(pName) {
    mSwitchCtrl = nullptr;
    _18 = true;
}

void SwitchSynchronizer::init(const JMapInfoIter &rIter) {
    MR::connectToSceneMapObjMovement(this);
    MR::registerDemoSimpleCastAll(this);
    mSwitchCtrl = MR::createStageSwitchCtrl(this, rIter);
}

void SwitchSynchronizer::movement() {
    if (_18) {
        if (mSwitchCtrl->isOnSwitchA() && mSwitchCtrl->isOnSwitchB()) {
            mSwitchCtrl->offSwitchA();
            return;
        }

        if (!mSwitchCtrl->isOnSwitchA() && !mSwitchCtrl->isOnSwitchB()) {
            mSwitchCtrl->onSwitchA();
            return;
        }
    }
    else {
        if (mSwitchCtrl->isOnSwitchA() && !mSwitchCtrl->isOnSwitchB()) {
            mSwitchCtrl->offSwitchA();
            return;
        }
        
        if (!mSwitchCtrl->isOnSwitchA() && mSwitchCtrl->isOnSwitchB()) {
            mSwitchCtrl->onSwitchA();
        }
    }
}

SwitchSynchronizer::~SwitchSynchronizer() {
    
}
