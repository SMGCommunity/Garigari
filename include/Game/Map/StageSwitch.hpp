#pragma once

#include "Game/NameObj/NameObj.hpp"
#include "Game/Util/Array.hpp"
#include "Game/Util/JMapIdInfo.hpp"
#include "Game/Util/JMapInfo.hpp"
#include <revolution.h>

class BitFlag128 {
public:
    BitFlag128() {
        u32* pFlag = mFlags;

        do {
            *pFlag++ = 0;
        } while (pFlag < &mFlags[4]);
    }

    bool get(int idx) const;
    void set(int bitIndex, bool setTrue);

    /* 0x0 */ u32 mFlags[4];
};

class ZoneSwitch : public BitFlag128 {
public:
    ZoneSwitch(s32 zoneID);

    int getZoneID() const {
        return mZoneID;
    }

    /* 0x10 */ s32 mZoneID;
};

class SwitchIdInfo {
public:
    SwitchIdInfo(s32, const JMapInfoIter&);

    s32 getSwitchNo() const;

    s32 getZoneID() const {
        return mIDInfo->mZoneID;
    }

    /* 0x0 */ JMapIdInfo* mIDInfo;
    /* 0x4 */ bool mIsGlobal;
};

class StageSwitchContainer : public NameObj {
public:
    StageSwitchContainer();

    virtual ~StageSwitchContainer();

    void createAndAddZone(const SwitchIdInfo&);
    ZoneSwitch* getZoneSwitch(const SwitchIdInfo&);
    ZoneSwitch* findZoneSwitchFromTable(const SwitchIdInfo&);

    /* 0x14 */ MR::Vector< MR::FixedArray< ZoneSwitch*, 0x10 > > mZoneSwitches;
    /* 0x58 */ ZoneSwitch* mParentZone;
};

class StageSwitchCtrl {
public:
    StageSwitchCtrl(const JMapInfoIter&);

    void onSwitchA();
    void offSwitchA();
    bool isOnSwitchA() const;
    bool isValidSwitchA() const;
    void onSwitchB();
    void offSwitchB();
    bool isOnSwitchB() const;
    bool isValidSwitchB() const;
    bool isOnSwitchAppear() const;
    bool isValidSwitchAppear() const;
    void onSwitchDead();
    void offSwitchDead();
    bool isValidSwitchDead() const;
    bool isOnAllSwitchAfterB(int) const;
    bool isOnAnyOneSwitchAfterB(int) const;
    bool isOnSwitchParam() const;
    bool isValidSwitchParam() const;

    /* 0x00 */ SwitchIdInfo* mSwitchA;
    /* 0x04 */ SwitchIdInfo* mSwitchB;
    /* 0x08 */ SwitchIdInfo* mSwitchAppear;
    /* 0x0C */ SwitchIdInfo* mSwitchDead;
    /* 0x10 */ bool _10;
    /* 0x14 */ SwitchIdInfo* mSwitchParam;
};

namespace StageSwitchFunction {
    SwitchIdInfo* createSwitchIdInfo(const char*, const JMapInfoIter&, bool);
    void onSwitchBySwitchIdInfo(const SwitchIdInfo&);
    void offSwitchBySwitchIdInfo(const SwitchIdInfo&);
    bool isOnSwitchBySwitchIdInfo(const SwitchIdInfo&);
    void onGlobalSwitchById(int);
};  // namespace StageSwitchFunction

namespace MR {
    StageSwitchCtrl* createStageSwitchCtrl(NameObj*, const JMapInfoIter&);
};
