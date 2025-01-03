#pragma once

#include "System/GalaxyStatusAccessor.hpp"
#include "NameObj/NameObj.hpp"
#include "Util/JMapInfo.hpp"
#include "Util/StringUtil.hpp"
#include <revolution.h>

class ScenarioData {
public:
    ScenarioData(const char *);

    void initialize(const char *);
    s32 getNormalPowerStarNum() const;
    s32 getPowerStarNum() const;
    bool getValueString(const char *, s32, const char **) const;
    bool getValueS32(const char *, s32, s32 *) const;
    u32 getValueU32(const char *, s32, u32 *) const;
    bool isPowerStarTypeHidden(s32) const;
    bool isPowerStarTypeGreen(s32) const;
    s32 getZoneNum() const;
    const char* getZoneName(int) const;
    s32 getZoneId(const char *) const;
    u32 getWorldNo() const;
    JMapInfoIter getScenarioDataIter(s32) const;
    bool getScenarioString(const char *, s32, const char **) const;

    inline bool isEqualScenarioString(const char *pKey, s32 idx, const char *pOther) const {
        const char* val = nullptr;
        getScenarioString(pKey, idx, &val);
        return MR::isEqualString(val, pOther);
    }

    const char* _0;
    JMapInfo* mScenarioData;    // 0x4
    JMapInfo* mZoneList;        // 0x8
    JMapInfo* mGalaxyInfo;      // 0xC
};

class ScenarioDataParser : public NameObj {
public:

    virtual ~ScenarioDataParser();

    ScenarioData* mScenarioData[0x60];        // 0x14
    s32 mNumScenarioData;                           // 0x194
};

class ScenarioDataIter {
public:
    ScenarioDataIter(ScenarioDataParser *);

    virtual bool isValidWorldNo(s32) const;

    void process(s32);
    bool isEnd() const NO_INLINE;
    void goNext();
    GalaxyStatusAccessor makeAccessor() const;

    ScenarioDataParser* mParser;        // 0x4
    s32 mCurIdx;                        // 0x8
};
