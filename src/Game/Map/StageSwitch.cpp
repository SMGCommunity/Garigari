#include "Game/Map/StageSwitch.hpp"
#include "Game/Scene/SceneObjHolder.hpp"
#include "Game/Util/JMapInfo.hpp"

void DUMMY_StageSwitch() {
    JMapInfoIter iter;
    const char* a;
    s32 b;
    iter.getValue< s32 >(a, &b);
}

namespace {
    StageSwitchContainer* getStageSwitchContainer() {
        return MR::getSceneObj< StageSwitchContainer >(SceneObj_StageSwitchContainer);
    }
};  // namespace

bool BitFlag128::get(int index) const {
    u32 flags = mFlags[index / 32];
    u32 mask = 1 << (index % 32);

    return (flags & static_cast< u32 >(mask)) == mask;
}

void BitFlag128::set(int bitIndex, bool isOn) {
    u32 byteIndex = bitIndex / 32;
    u32& flag = mFlags[byteIndex];

    if (isOn) {
        flag |= (1U << (bitIndex % 32));
    } else {
        flag &= ~(1U << (bitIndex % 32));
    }
}

ZoneSwitch::ZoneSwitch(s32 zoneID) : BitFlag128(), mZoneID(zoneID) {
    for (s32 i = 0; i < 128; i++) {
        set(i, false);
    }
}

SwitchIdInfo::SwitchIdInfo(s32 switchID, const JMapInfoIter& rIter) : mIDInfo(), mIsGlobal(switchID >= 1000) {
    mIDInfo = new JMapIdInfo(switchID, rIter);
}

s32 SwitchIdInfo::getSwitchNo() const {
    if (mIsGlobal) {
        return mIDInfo->mID - 1000;
    }

    return mIDInfo->mID;
}

StageSwitchContainer::StageSwitchContainer() : NameObj("ステージスイッチ"), mZoneSwitches(), mParentZone() {
    mParentZone = new ZoneSwitch(-1);
}

void StageSwitchContainer::createAndAddZone(const SwitchIdInfo& rInfo) {
    if (findZoneSwitchFromTable(rInfo) != nullptr) {
        return;
    }

    ZoneSwitch* zoneSwitch = new ZoneSwitch(rInfo.mIDInfo->mZoneID);
    mZoneSwitches.push_back(zoneSwitch);
}

ZoneSwitch* StageSwitchContainer::getZoneSwitch(const SwitchIdInfo& rInfo) {
    if (rInfo.mIsGlobal) {
        return mParentZone;
    }

    return findZoneSwitchFromTable(rInfo);
}

ZoneSwitch* StageSwitchContainer::findZoneSwitchFromTable(const SwitchIdInfo& rInfo) {
    for (s32 i = 0; i < mZoneSwitches.size(); i++) {
        ZoneSwitch* zoneSwitch = mZoneSwitches[i];

        if (rInfo.getZoneID() == zoneSwitch->mZoneID) {
            return zoneSwitch;
        }
    }

    return nullptr;
}

StageSwitchCtrl::StageSwitchCtrl(const JMapInfoIter& rIter) : mSwitchA(), mSwitchB(), mSwitchAppear(), mSwitchDead(), _10(), mSwitchParam() {
    mSwitchA = StageSwitchFunction::createSwitchIdInfo("SW_A", rIter, true);
    mSwitchB = StageSwitchFunction::createSwitchIdInfo("SW_B", rIter, true);
    mSwitchAppear = StageSwitchFunction::createSwitchIdInfo("SW_APPEAR", rIter, false);
    mSwitchDead = StageSwitchFunction::createSwitchIdInfo("SW_DEAD", rIter, false);
    mSwitchParam = StageSwitchFunction::createSwitchIdInfo("SW_PARAM", rIter, false);
}

void StageSwitchCtrl::onSwitchA() {
    StageSwitchFunction::onSwitchBySwitchIdInfo(*mSwitchA);
}

void StageSwitchCtrl::offSwitchA() {
    StageSwitchFunction::offSwitchBySwitchIdInfo(*mSwitchA);
}

bool StageSwitchCtrl::isOnSwitchA() const {
    return StageSwitchFunction::isOnSwitchBySwitchIdInfo(*mSwitchA);
}

bool StageSwitchCtrl::isValidSwitchA() const {
    return mSwitchA != nullptr;
}

void StageSwitchCtrl::onSwitchB() {
    StageSwitchFunction::onSwitchBySwitchIdInfo(*mSwitchB);
}

void StageSwitchCtrl::offSwitchB() {
    StageSwitchFunction::offSwitchBySwitchIdInfo(*mSwitchB);
}

bool StageSwitchCtrl::isOnSwitchB() const {
    return StageSwitchFunction::isOnSwitchBySwitchIdInfo(*mSwitchB);
}

bool StageSwitchCtrl::isValidSwitchB() const {
    return mSwitchB != nullptr;
}

bool StageSwitchCtrl::isOnSwitchAppear() const {
    return StageSwitchFunction::isOnSwitchBySwitchIdInfo(*mSwitchAppear);
}

bool StageSwitchCtrl::isValidSwitchAppear() const {
    return mSwitchAppear != nullptr;
}

void StageSwitchCtrl::onSwitchDead() {
    StageSwitchFunction::onSwitchBySwitchIdInfo(*mSwitchDead);
}

void StageSwitchCtrl::offSwitchDead() {
    StageSwitchFunction::offSwitchBySwitchIdInfo(*mSwitchDead);
}

bool StageSwitchCtrl::isValidSwitchDead() const {
    return mSwitchDead != nullptr;
}

bool StageSwitchCtrl::isOnAllSwitchAfterB(int idx) const {
    SwitchIdInfo* info;
    s32 switchNo;

    for (int i = 0; i < idx; i++) {
        switchNo = i + mSwitchB->getSwitchNo();
        info = mSwitchB;
        StageSwitchContainer* container = MR::getSceneObj< StageSwitchContainer >(SceneObj_StageSwitchContainer);

        if (!container->getZoneSwitch(*info)->get(switchNo)) {
            return false;
        }
    }

    return true;
}

bool StageSwitchCtrl::isOnAnyOneSwitchAfterB(int idx) const {
    SwitchIdInfo* info;
    s32 switchNo;

    for (int i = 0; i < idx; i++) {
        switchNo = i + mSwitchB->getSwitchNo();
        info = mSwitchB;
        StageSwitchContainer* container = MR::getSceneObj< StageSwitchContainer >(SceneObj_StageSwitchContainer);

        if (container->getZoneSwitch(*info)->get(switchNo)) {
            return true;
        }
    }

    return false;
}

SwitchIdInfo* StageSwitchFunction::createSwitchIdInfo(const char* pSwitchName, const JMapInfoIter& rIter, bool /* unused */) {
    s32 switchNo;
    bool hasSwitch = rIter.getValue< s32 >(pSwitchName, &switchNo);

    if (!hasSwitch) {
        return nullptr;
    }

    if (switchNo < 0) {
        return nullptr;
    }

    SwitchIdInfo* idInfo = new SwitchIdInfo(switchNo, rIter);

    if (switchNo < 1000) {
        ::getStageSwitchContainer()->createAndAddZone(*idInfo);
    }

    return idInfo;
}

void StageSwitchFunction::onSwitchBySwitchIdInfo(const SwitchIdInfo& rInfo) {
    s32 switchNo = rInfo.getSwitchNo();
    StageSwitchContainer* container = MR::getSceneObj< StageSwitchContainer >(SceneObj_StageSwitchContainer);
    ZoneSwitch* zoneSwitch = container->getZoneSwitch(rInfo);
    if (!zoneSwitch->get(switchNo)) {
        zoneSwitch->set(switchNo, true);
    }
}

void StageSwitchFunction::offSwitchBySwitchIdInfo(const SwitchIdInfo& rInfo) {
    s32 switchNo = rInfo.getSwitchNo();
    StageSwitchContainer* container = MR::getSceneObj< StageSwitchContainer >(SceneObj_StageSwitchContainer);
    ZoneSwitch* zoneSwitch = container->getZoneSwitch(rInfo);
    if (zoneSwitch->get(switchNo)) {
        zoneSwitch->set(switchNo, false);
    }
}

bool StageSwitchFunction::isOnSwitchBySwitchIdInfo(const SwitchIdInfo& rInfo) {
    s32 switchNo = rInfo.getSwitchNo();
    StageSwitchContainer* container = MR::getSceneObj< StageSwitchContainer >(SceneObj_StageSwitchContainer);
    ZoneSwitch* zoneSwitch = container->getZoneSwitch(rInfo);
    return zoneSwitch->get(switchNo);
}

void StageSwitchFunction::onGlobalSwitchById(int switchNo) {
    StageSwitchContainer* container = MR::getSceneObj< StageSwitchContainer >(SceneObj_StageSwitchContainer);
    ZoneSwitch* parentZone = container->mParentZone;

    if (!parentZone->get(switchNo)) {
        parentZone->set(switchNo, true);
    }
}

StageSwitchCtrl* MR::createStageSwitchCtrl(NameObj* /* unused */, const JMapInfoIter& rInfo) {
    return new StageSwitchCtrl(rInfo);
}

bool StageSwitchCtrl::isOnSwitchParam() const {
    return StageSwitchFunction::isOnSwitchBySwitchIdInfo(*mSwitchParam);
}

bool StageSwitchCtrl::isValidSwitchParam() const {
    return mSwitchParam != nullptr;
}

StageSwitchContainer::~StageSwitchContainer() {
}
