#include "Map/StageSwitch.hpp"
#include "Scene/SceneObjHolder.hpp"
#include "Util/JMapInfo.hpp"

bool BitFlag128::get(int idx) const {
    u32 flags = mSwitchFlags[idx / 32];
    u32 mask = (1 << (idx % 32));
    return mask == (flags & (u32)mask);
}

void BitFlag128::set(int bit_index, bool setTrue) {
    u32 valIdx = bit_index / 32;
    s32& flag = mSwitchFlags[valIdx];

    if (setTrue) {
        flag |= (1 << (bit_index % 32));
    }
    else {
        flag &= ~(1 << (bit_index % 32));
    }
}

ZoneSwitch::ZoneSwitch(int zoneId) : BitFlag128() {
    s32 *sw = mSwitchFlags;

    do {
        *sw = 0;
        sw = sw + 1;
    } while (sw < &mSwitchFlags[NUM_SWITCH_FLAGS]);

    mZoneID = zoneId;
    s32 idx = 0;

    while (idx < 0x80) {
        set(idx, false);
        idx++;
    }
}

SwitchIdInfo::SwitchIdInfo(s32 switchID, const JMapInfoIter &rIter) {
    mIDInfo = nullptr;
    mIsGlobal = switchID >= GLOBAL_SWITCH_ID;
    mIDInfo = new JMapIdInfo(switchID, rIter);
}

s32 SwitchIdInfo::getSwitchNo() const {
    if (mIsGlobal) {
        return mIDInfo->_0 - GLOBAL_SWITCH_ID;
    }

    return mIDInfo->_0;
}

StageSwitchContainer::StageSwitchContainer() : NameObj("ステージスイッチ") {
    mSwitchCount = 0;
    mParentZone = nullptr;
    mParentZone = new ZoneSwitch(-1);
}

void StageSwitchContainer::createAndAddZone(const SwitchIdInfo &rInfo) {
    if (findZoneSwitchFromTable(rInfo) == nullptr) {
        ZoneSwitch* sw = new ZoneSwitch(rInfo.mIDInfo->mZoneID);
        s32 numSwitchCount = mSwitchCount;
        mSwitchCount++;
        mZoneSwitches[numSwitchCount] = sw;
    }
}

ZoneSwitch* StageSwitchContainer::getZoneSwitch(const SwitchIdInfo &rInfo) {
    if (rInfo.mIsGlobal) {
        return mParentZone;
    }

    return findZoneSwitchFromTable(rInfo);
}

ZoneSwitch* StageSwitchContainer::findZoneSwitchFromTable(const SwitchIdInfo &rInfo) {
    for (s32 i = 0; i < mSwitchCount; i++) {
        if (rInfo.getZoneID() == mZoneSwitches[i]->mZoneID) {
            return mZoneSwitches[i];
        }
    }

    return nullptr;
}

// https://decomp.me/scratch/x3aBu
StageSwitchCtrl::StageSwitchCtrl(const JMapInfoIter &rIter) {
    mSW_A = nullptr;
    mSW_B = nullptr;
    mSW_Appear = nullptr;
    mSW_Dead = nullptr;
    _10 = false;
    mSW_Param = nullptr;
    mSW_A = StageSwitchFunction::createSwitchIdInfo("SW_A", rIter, true);
    mSW_B = StageSwitchFunction::createSwitchIdInfo("SW_B", rIter, true);
    mSW_Appear = StageSwitchFunction::createSwitchIdInfo("SW_APPEAR", rIter, false);
    mSW_Dead = StageSwitchFunction::createSwitchIdInfo("SW_DEAD", rIter, false);
    mSW_Param = StageSwitchFunction::createSwitchIdInfo("SW_PARAM", rIter, false);
}

void StageSwitchCtrl::onSwitchA() {
    StageSwitchFunction::onSwitchBySwitchIdInfo(*mSW_A);
}

void StageSwitchCtrl::offSwitchA() {
    StageSwitchFunction::offSwitchBySwitchIdInfo(*mSW_A);
}

bool StageSwitchCtrl::isOnSwitchA() const {
    return StageSwitchFunction::isOnSwitchBySwitchIdInfo(*mSW_A);
}

bool StageSwitchCtrl::isValidSwitchA() const {
    return mSW_A != nullptr;
}

void StageSwitchCtrl::onSwitchB() {
    StageSwitchFunction::onSwitchBySwitchIdInfo(*mSW_B);
}

void StageSwitchCtrl::offSwitchB() {
    StageSwitchFunction::offSwitchBySwitchIdInfo(*mSW_B);
}

bool StageSwitchCtrl::isOnSwitchB() const {
    return StageSwitchFunction::isOnSwitchBySwitchIdInfo(*mSW_B);
}

bool StageSwitchCtrl::isValidSwitchB() const {
    return mSW_B != nullptr;
}

bool StageSwitchCtrl::isOnSwitchAppear() const {
    return StageSwitchFunction::isOnSwitchBySwitchIdInfo(*mSW_Appear);
}

bool StageSwitchCtrl::isValidSwitchAppear() const {
    return mSW_Appear != nullptr;
}

void StageSwitchCtrl::onSwitchDead() {
    StageSwitchFunction::onSwitchBySwitchIdInfo(*mSW_Dead);
}

void StageSwitchCtrl::offSwitchDead() {
    StageSwitchFunction::offSwitchBySwitchIdInfo(*mSW_Dead);
}

bool StageSwitchCtrl::isValidSwitchDead() const {
    return mSW_Dead != nullptr;
}

bool StageSwitchCtrl::isOnAllSwitchAfterB(int idx) const {
    SwitchIdInfo* info;
    s32 v7;
    for (int i = 0; i < idx; i++) {
        v7 = i + mSW_B->getSwitchNo();
        info = mSW_B;
        StageSwitchContainer* container = MR::getSceneObj<StageSwitchContainer*>(SceneObj_StageSwitchContainer);

        if (!container->getZoneSwitch(*info)->get(v7)) {
            return false;
        }
    }

    return true;
}

bool StageSwitchCtrl::isOnAnyOneSwitchAfterB(int idx) const {
    SwitchIdInfo* info;
    s32 v7;
    for (int i = 0; i < idx; i++) {
        v7 = i + mSW_B->getSwitchNo();
        info = mSW_B;
        StageSwitchContainer* container = MR::getSceneObj<StageSwitchContainer*>(SceneObj_StageSwitchContainer);

        if (container->getZoneSwitch(*info)->get(v7)) {
            return true;
        }
    }

    return false;
}

namespace StageSwitchFunction {
    SwitchIdInfo* createSwitchIdInfo(const char *pName, const JMapInfoIter &rIter, bool /* unused*/) {
        s32 switchVal;
        if (!rIter.getValue<s32>(pName, &switchVal)) {
            return nullptr;
        }

        if (switchVal < 0) {
            return nullptr;
        }

        SwitchIdInfo* info = new SwitchIdInfo(switchVal, rIter);

        if (switchVal < 1000) {
            MR::getSceneObj<StageSwitchContainer*>(SceneObj_StageSwitchContainer)->createAndAddZone(*info);
        }

        return info;
    }

    void onSwitchBySwitchIdInfo(const SwitchIdInfo &rInfo) {
        s32 switchNo = rInfo.getSwitchNo();
        StageSwitchContainer* container = MR::getSceneObj<StageSwitchContainer*>(SceneObj_StageSwitchContainer);
        ZoneSwitch* zs = container->getZoneSwitch(rInfo);
        if (!zs->get(switchNo)) {
            zs->set(switchNo, true);
        }
    }

    void offSwitchBySwitchIdInfo(const SwitchIdInfo &rInfo) {
        s32 switchNo = rInfo.getSwitchNo();
        StageSwitchContainer* container = MR::getSceneObj<StageSwitchContainer*>(SceneObj_StageSwitchContainer);
        ZoneSwitch* zs = container->getZoneSwitch(rInfo);
        if (zs->get(switchNo)) {
            zs->set(switchNo, false);
        }
    }

    bool isOnSwitchBySwitchIdInfo(const SwitchIdInfo &rInfo) {
        s32 switchNo = rInfo.getSwitchNo();
        StageSwitchContainer* container = MR::getSceneObj<StageSwitchContainer*>(SceneObj_StageSwitchContainer);
        ZoneSwitch* zs = container->getZoneSwitch(rInfo);
        return zs->get(switchNo);
    }

    void onGlobalSwitchById(int switchNo) {
        StageSwitchContainer* container = MR::getSceneObj<StageSwitchContainer*>(SceneObj_StageSwitchContainer);
        ZoneSwitch* parentZone = container->mParentZone;

        if (!parentZone->get(switchNo)) {
            parentZone->set(switchNo, true);
        }
    }
};

namespace MR {
    StageSwitchCtrl* createStageSwitchCtrl(NameObj */* unused */, const JMapInfoIter &rInfo) {
        return new StageSwitchCtrl(rInfo);
    }
};

bool StageSwitchCtrl::isOnSwitchParam() const {
    return StageSwitchFunction::isOnSwitchBySwitchIdInfo(*mSW_Param);
}

bool StageSwitchCtrl::isValidSwitchParam() const {
    return mSW_Param != nullptr;
}

StageSwitchContainer::~StageSwitchContainer() {
    
}
