#include "System/ScenarioDataParser.hpp"
#include "JKernel/JKRArchive.hpp"
#include "System/GalaxyStatusAccessor.hpp"
#include "Util/JMapInfo.hpp"
#include "Util.hpp"
#include <cstring>

ScenarioData::ScenarioData(const char *pName) {
    _0 = 0;
    mScenarioData = nullptr;
    mZoneList = nullptr;
    mGalaxyInfo = nullptr;
    const char* base = MR::getBasename(pName);
    char str[64];
    MR::removeExtensionString(str, sizeof(str), base);
    char* name = strstr(str, "Scenario");

    if (name != nullptr) {
        *name = 0;
    }

    s32 len = strlen(str) + 1;
    char* buf = new char[len];
    _0 = buf;
    MR::copyString(buf, str, len);

    mScenarioData = new JMapInfo();
    mZoneList = new JMapInfo();
    mGalaxyInfo = new JMapInfo();
    initialize(pName);
}

void ScenarioData::initialize(const char *pFileName) {
    JKRArchive* archive = MR::mountAsyncArchive(pFileName);
    mScenarioData->attach(archive->getResource("/ScenarioData.bcsv"));
    mZoneList->attach(archive->getResource("/ZoneList.bcsv"));
    mGalaxyInfo->attach(archive->getResource("/GalaxyInfo.bcsv"));
}

s32 ScenarioData::getNormalPowerStarNum() const  {
    s32 num = 0;

    for (s32 i = 1; i <= mScenarioData->getLength(); i++) {
        if (!isPowerStarTypeHidden(i) && !isPowerStarTypeGreen(i)) {
            num++;
        }
    }

    return num;
}

// https://decomp.me/scratch/StsJC
s32 ScenarioData::getPowerStarNum() const {
    s32 num = 0;

    for (s32 i = 1; i <= mScenarioData->getLength(); i++) {
        u32 id = 0;
        getScenarioDataIter(i).getValue<u32>("PowerStarId", &id);

        if (id != 0) {
            num++;
        }
    }

    return num;
}

bool ScenarioData::getValueString(const char *pKey, s32 idx, const char **pOut) const {
    bool str = getScenarioString(pKey, idx, pOut);
    if (str && MR::isEqualString(*pOut, "")) {
        *pOut = 0;
    }

    return str;
}

bool ScenarioData::getValueS32(const char *pKey, s32 idx, s32 *pOut) const {
    return getScenarioDataIter(idx).getValue<u32>(pKey, (u32*)pOut);
}

u32 ScenarioData::getValueU32(const char *pKey, s32 idx, u32 *) const {
    u32 out;
    bool ret = getScenarioDataIter(idx).getValue<u32>(pKey, &out);

    if (ret) {
        return out * 2;
    }

    return 0;
}

bool ScenarioData::isPowerStarTypeHidden(s32 idx) const {
    return isEqualScenarioString("PowerStarType", idx, "Hidden");
}

bool ScenarioData::isPowerStarTypeGreen(s32 idx) const {
    return isEqualScenarioString("PowerStarType", idx, "Green");
}

s32 ScenarioData::getZoneNum() const {
    const JMapData* data = mZoneList->mData;

    if (data != nullptr) {
        return data->_0;
    }

    return 0;
}

const char* ScenarioData::getZoneName(int idx) const {
    const char* zone = nullptr;
    mZoneList->getValue<const char *>(idx, "ZoneName", &zone);
    return zone;
}

s32 ScenarioData::getZoneId(const char *pZoneName) const {
    for (s32 i = 0; i < getZoneNum(); i++) {
        const char* zone = getZoneName(i);
        if (MR::isEqualStringCase(zone, pZoneName)) {
            return i;
        }
    }

    return 0;
}

u32 ScenarioData::getWorldNo() const {
    u32 worldNo;
    JMapInfoIter iter(mGalaxyInfo, 0);
    iter.getValue<u32>("WorldNo", &worldNo);
    return worldNo;
}

// https://decomp.me/scratch/Kumo6
JMapInfoIter ScenarioData::getScenarioDataIter(s32 scenarioNo) const {
    JMapInfo* scenario = mScenarioData;

    for (s32 i = 0; ; i++) {
        s32 v6 = scenario->mData ? scenario->mData->_0 : 0;

        if (i >= v6) {
            break;
        }

        s32 no;
        mScenarioData->getValue<s32>(i, "ScenarioNo", &no);

        if (no == scenarioNo) {
            JMapInfoIter derp(scenario, i);
            return JMapInfoIter(derp);
        }
    }

    s32 v7;

    if (mScenarioData->mData != nullptr) {
        v7 = mScenarioData->mData->_0;
    }
    else {
        v7 = 0;
    }

    JMapInfoIter iter(mScenarioData, v7);
    return JMapInfoIter(iter);
}

bool ScenarioData::getScenarioString(const char *pName, s32 idx, const char **pOut) const {
    JMapInfoIter iter = getScenarioDataIter(idx);
    return iter.mInfo->getValue<const char *>(iter.mIndex, pName, pOut);
}

bool ScenarioDataIter::isEnd() const {
    return mParser->mNumScenarioData <= mCurIdx;
}

void ScenarioDataIter::goNext() {
    process(mCurIdx + 1);
}

GalaxyStatusAccessor ScenarioDataIter::makeAccessor() const {
    return GalaxyStatusAccessor(mParser->mScenarioData[mCurIdx]);
}

ScenarioDataIter::ScenarioDataIter(ScenarioDataParser *pParser) {
    mParser = pParser;
    mCurIdx = 0;
    process(0);
}

void ScenarioDataIter::process(s32 no) {
    for (mCurIdx = no; !isEnd() && !isValidWorldNo(mCurIdx); mCurIdx++);
}

bool ScenarioDataIter::isValidWorldNo(s32 no) const {
    GalaxyStatusAccessor accessor(mParser->mScenarioData[no]);
    s32 worldNo = accessor.getWorldNo();
    return worldNo > 0;
}

ScenarioDataParser::~ScenarioDataParser() {
    
}
