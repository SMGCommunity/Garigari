#pragma once

#include "Game/NameObj/NameObj.hpp"
#include "Game/Util/Array.hpp"
#include "Game/Util/StringUtil.hpp"

class GalaxyStatusAccessor;
class JMapInfo;

class ScenarioData {
public:
    ScenarioData(const char*);

    void initialize(const char*);
    s32 getNormalPowerStarNum() const;
    s32 getPowerStarNum() const;
    bool getValueString(const char*, s32, const char**) const;
    bool getValueU32(const char*, s32, u32*) const;
    u32 getScenarioLayers(const char*, s32) const;
    bool isPowerStarTypeHidden(s32) const;
    bool isPowerStarTypeGreen(s32) const;
    s32 getZoneNum() const;
    const char* getZoneName(int) const;
    s32 getZoneId(const char*) const;
    u32 getWorldNo() const;
    JMapInfoIter getScenarioDataIter(s32) const;
    bool getScenarioString(const char*, s32, const char**) const;

    inline bool isEqualScenarioString(const char* pKey, s32 idx, const char* pOther) const {
        const char* val = nullptr;
        getScenarioString(pKey, idx, &val);
        return MR::isEqualString(val, pOther);
    }

    /* 0x0 */ char* mGalaxyName;
    /* 0x4 */ JMapInfo* mScenarioData;
    /* 0x8 */ JMapInfo* mZoneList;
    /* 0xC */ JMapInfo* mGalaxyInfo;
};

class ScenarioDataParser : public NameObj {
public:
    ScenarioDataParser(const char*);

    ScenarioData* getScenarioData(const char*) const;
    GalaxyStatusAccessor makeAccessor(const char*) const;

    /* 0x014 */ MR::Vector< MR::FixedArray< ScenarioData*, 0x60 > > mScenarioData;
};

class ScenarioDataIter {
public:
    ScenarioDataIter(ScenarioDataParser*);

    virtual bool isValidWorldNo(s32) const;

    void process(s32);
    bool isEnd() const NO_INLINE;
    void goNext();
    GalaxyStatusAccessor makeAccessor() const;

    /* 0x4 */ ScenarioDataParser* mParser;
    /* 0x8 */ s32 mCur;
};

namespace ScenarioDataFunction {
    ScenarioDataParser* getScenarioDataParser();
    bool getCurrentCommonLayers(const char*);
    u32 getCurrentScenarioLayers(const char*, s32);
};  // namespace ScenarioDataFunction

namespace MR {
    ScenarioDataIter makeBeginScenarioDataIter();
};
