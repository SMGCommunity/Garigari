#pragma once

#include <revolution.h>
#include "NameObj/NameObj.hpp"
#include "Util/JMapInfo.hpp"
#include "Util/JMapIdInfo.hpp"

#define GLOBAL_SWITCH_ID 1000
#define NUM_SWITCH_FLAGS 4

class BitFlag128 {
public:
    inline BitFlag128() {

    }

    bool get(int) const;
    void set(int, bool);

    s32 mSwitchFlags[NUM_SWITCH_FLAGS];        // 0x00
};

class ZoneSwitch : public BitFlag128 {
public:
    ZoneSwitch(int);

    int getZoneID() const {
        return mZoneID;
    }

    int mZoneID;        // 0x10
};

class SwitchIdInfo {
public:
    SwitchIdInfo(s32, const JMapInfoIter &);

    s32 getSwitchNo() const;

    int getZoneID() const {
        return mIDInfo->getZoneID();
    }

    JMapIdInfo* mIDInfo;    // 0x0
    bool mIsGlobal;         // 0x4
};

class StageSwitchContainer : public NameObj {
public:
    StageSwitchContainer();

    virtual ~StageSwitchContainer();

    void createAndAddZone(const SwitchIdInfo &);
    ZoneSwitch* getZoneSwitch(const SwitchIdInfo &);
    ZoneSwitch* findZoneSwitchFromTable(const SwitchIdInfo &);

    ZoneSwitch* mZoneSwitches[0x10];     // 0x14
    s32 mSwitchCount;                   // 0x54
    ZoneSwitch* mParentZone;            // 0x58
};

class StageSwitchCtrl {
public:
    StageSwitchCtrl(const JMapInfoIter &);

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

    SwitchIdInfo* mSW_A;                // 0x00
    SwitchIdInfo* mSW_B;                // 0x04
    SwitchIdInfo* mSW_Appear;           // 0x08
    SwitchIdInfo* mSW_Dead;             // 0x0C
    bool _10;
    SwitchIdInfo* mSW_Param;            // 0x14
};

namespace StageSwitchFunction {
    SwitchIdInfo* createSwitchIdInfo(const char *, const JMapInfoIter &, bool);
    void onSwitchBySwitchIdInfo(const SwitchIdInfo &);
    void offSwitchBySwitchIdInfo(const SwitchIdInfo &);
    bool isOnSwitchBySwitchIdInfo(const SwitchIdInfo &);
    void onGlobalSwitchById(int);
};

namespace MR {
    StageSwitchCtrl* createStageSwitchCtrl(NameObj *, const JMapInfoIter &);
};
