#include "Game/System/ScenarioDataParser.hpp"
#include "Game/System/GalaxyStatusAccessor.hpp"
#include "Game/Util/FileUtil.hpp"
#include "Game/Util/JMapInfo.hpp"
#include "Game/Util/SceneUtil.hpp"
#include <cstring>

ScenarioData::ScenarioData(const char* pName) {
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

void ScenarioData::initialize(const char* pFileName) {
    JKRArchive* archive = MR::mountAsyncArchive(pFileName);
    mScenarioData->attach(archive->getResource("/ScenarioData.bcsv"));
    mZoneList->attach(archive->getResource("/ZoneList.bcsv"));
    mGalaxyInfo->attach(archive->getResource("/GalaxyInfo.bcsv"));
}

s32 ScenarioData::getNormalPowerStarNum() const {
    s32 num = 0;

    for (s32 i = 1; i <= mScenarioData->getNumEntries(); i++) {
        if (!isPowerStarTypeHidden(i) && !isPowerStarTypeGreen(i)) {
            num++;
        }
    }

    return num;
}

s32 ScenarioData::getPowerStarNum() const {
    s32 count = 0;
    for (s32 scenarioNo = 1; scenarioNo <= mScenarioData->getNumEntries(); scenarioNo++) {
        s32 powerStarId = 0;
        getValueS32("PowerStarId", scenarioNo, &powerStarId);
        if (powerStarId != 0) {
            count++;
        }
    }

    return count;
}

bool ScenarioData::getValueString(const char* pKey, s32 idx, const char** pOut) const {
    bool str = getScenarioString(pKey, idx, pOut);
    if (str && MR::isEqualString(*pOut, "")) {
        *pOut = nullptr;
    }

    return str;
}

bool ScenarioData::getValueS32(const char* pKey, s32 idx, s32* pOut) const {
    return getScenarioDataIter(idx).getValue< u32 >(pKey, reinterpret_cast< u32* >(pOut));
}

u32 ScenarioData::getScenarioLayers(const char* pKey, s32 idx) const {
    u32 out;
    bool ret = getScenarioDataIter(idx).getValue< u32 >(pKey, &out);

    if (ret) {
        return out << 1;
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
    return mZoneList->getNumEntries();
}

const char* ScenarioData::getZoneName(int idx) const {
    const char* zone = nullptr;
    mZoneList->getValue< const char* >(idx, "ZoneName", &zone);
    return zone;
}

s32 ScenarioData::getZoneId(const char* pZoneName) const {
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
    iter.getValue< u32 >("WorldNo", &worldNo);
    return worldNo;
}

JMapInfoIter ScenarioData::getScenarioDataIter(s32 scenarioNo) const {
    JMapInfoIter iter = mScenarioData->findElement< s32 >("ScenarioNo", scenarioNo, 0);
    return iter;
}

bool ScenarioData::getScenarioString(const char* pName, s32 idx, const char** pOut) const {
    JMapInfoIter iter = getScenarioDataIter(idx);
    return iter.mInfo->getValue< const char* >(iter.mIndex, pName, pOut);
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

ScenarioDataIter::ScenarioDataIter(ScenarioDataParser* pParser) {
    mParser = pParser;
    mCurIdx = 0;
    process(0);
}

void ScenarioDataIter::process(s32 no) {
    for (mCurIdx = no; !isEnd() && !isValidWorldNo(mCurIdx); mCurIdx++)
        ;
}

bool ScenarioDataIter::isValidWorldNo(s32 no) const {
    GalaxyStatusAccessor accessor(mParser->mScenarioData[no]);
    s32 worldNo = accessor.getWorldNo();
    return worldNo > 0;
}

ScenarioDataParser::ScenarioDataParser(const char* pName) : NameObj(pName) {
    mNumScenarioData = 0;
    DVDDir stageDir;
    DVDOpenDir("/StageData", &stageDir);
    DVDDirEntry entry;

    while (DVDReadDir(&stageDir, &entry)) {
        if (entry.isDir) {
            char buf[256];
            MR::makeScenarioArchiveFileName(buf, sizeof(buf), entry.name);
            if (MR::isFileExist(buf, false)) {
                mScenarioData[mNumScenarioData++] = new ScenarioData(buf);
            }
        }
    }

    DVDCloseDir(&stageDir);
}

ScenarioData* ScenarioDataParser::getScenarioData(const char* pName) const {
    for (s32 i = 0; i < mNumScenarioData; i++) {
        ScenarioData* data = mScenarioData[i];
        if (MR::isEqualStringCase(data->_0, pName)) {
            return data;
        }
    }

    return nullptr;
}

GalaxyStatusAccessor ScenarioDataParser::makeAccessor(const char* pName) const {
    return GalaxyStatusAccessor(getScenarioData(pName));
}

namespace ScenarioDataFunction {
    // ScenarioDataFunction::getScenarioDataParser

    bool getCurrentCommonLayers(const char* pName) {
        const char* stageName = MR::getCurrentStageName();
        getScenarioDataParser()->getScenarioData(stageName);
        return true;
    }

    u32 getCurrentScenarioLayers(const char* pName, s32 idx) {
        const char* stageName = MR::getCurrentStageName();
        return getScenarioDataParser()->getScenarioData(stageName)->getScenarioLayers(pName, idx);
    }
};  // namespace ScenarioDataFunction

namespace MR {
    ScenarioDataIter makeBeginScenarioDataIter() {
        return ScenarioDataIter(ScenarioDataFunction::getScenarioDataParser());
    }

};  // namespace MR

ScenarioDataParser::~ScenarioDataParser() {
}
