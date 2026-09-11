#include "Map/SwitchWatcher.hpp"
#include "Map/StageSwitch.hpp"
#include "Scene/SceneObjHolder.hpp"
#include "Util/ObjUtil.hpp"

#define Listener_A      1
#define Listener_B      2    
#define Listener_Appear 4

SwitchWatcher::SwitchWatcher(const StageSwitchCtrl* pSwitchCtrl) : NameObj("スイッチ監視") {
    mCheck = 0;
    mSwitchCtrl = pSwitchCtrl;
    mListener_A = nullptr;
    mListener_B = nullptr;
    mListener_Appear = nullptr;
}

void SwitchWatcher::movement() {
    if (mListener_A != nullptr) {
        checkSwitch(mListener_A, Listener_A, mSwitchCtrl->isOnSwitchA());
    }

    if (mListener_B != nullptr) {
        checkSwitch(mListener_B, Listener_B, mSwitchCtrl->isOnSwitchB());
    }

    if (mListener_Appear != nullptr) {
        checkSwitch(mListener_Appear, Listener_Appear, mSwitchCtrl->isOnSwitchAppear());
    }
}

void SwitchWatcher::checkSwitch(SwitchEventListener *pListener, u32 check, bool isOnEvent) {
    if (isOnEvent) {
        if ((mCheck & check) == 0) {
            pListener->listenSwitchOnEvent();
        }

        mCheck |= check;
    }
    else {
        if ((mCheck & check) != 0) {
            pListener->listenSwitchOffEvent();
        }

        mCheck &= ~check;
    }
}

bool SwitchWatcher::isSameSwitch(const StageSwitchCtrl *pCtrl) const {
    return mSwitchCtrl == pCtrl;
}

void SwitchWatcher::addSwitchListener(SwitchEventListener *pListener, u32 type) {
    switch (type) {
        case Listener_A:
            mListener_A = pListener;
            break;
        case Listener_B:
            mListener_B = pListener;
            break;
        case Listener_Appear:
            mListener_Appear = pListener;
            break;
    }
}

SwitchWatcher::~SwitchWatcher() {
    
}

