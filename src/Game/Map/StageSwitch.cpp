#include "Map/StageSwitch.hpp"


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

StageSwitchContainer::~StageSwitchContainer() {
    
}
