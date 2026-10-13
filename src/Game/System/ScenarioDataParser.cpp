#include "Game/System/ScenarioDataParser.hpp"
#include "Game/System/GalaxyStatusAccessor.hpp"
#include "Game/Util/FileUtil.hpp"
#include "Game/Util/JMapInfo.hpp"
#include "Game/Util/SceneUtil.hpp"
#include <cstring>

void ScenarioDataParser_DUMMY() {
    s32 a;
    JMapInfoIter iter(nullptr, 0);
    iter.getValue< s32 >(nullptr, &a);
}

ScenarioData::ScenarioData(const char* pFilePath) : mGalaxyName(), mScenarioData(), mZoneList(), mGalaxyInfo() {
    char fileName[64];
    MR::removeExtensionString(fileName, sizeof(fileName), MR::getBasename(pFilePath));

    const char* pSuffix = "Scenario";
    char* galaxyName = strstr(fileName, pSuffix);

    if (galaxyName != nullptr) {
        galaxyName[0] = '\0';
    }

    s32 galaxyNameSize = strlen(fileName) + 1;
    mGalaxyName = new char[galaxyNameSize];
    MR::copyString(mGalaxyName, fileName, galaxyNameSize);

    mScenarioData = new JMapInfo();
    mZoneList = new JMapInfo();
    mGalaxyInfo = new JMapInfo();
    initialize(pFilePath);
}

void ScenarioData::initialize(const char* pFileName) {
    JKRArchive* archive = MR::receiveArchive(pFileName);
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
        u32 powerStarId = 0;
        getValueU32("PowerStarId", scenarioNo, &powerStarId);
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

bool ScenarioData::getValueU32(const char* pKey, s32 idx, u32* pOut) const {
    return getScenarioDataIter(idx).getValue< u32 >(pKey, pOut);
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
    return iter.getValue< const char* >(pName, pOut);
}

bool ScenarioDataIter::isEnd() const {
    return mParser->mScenarioData.size() <= mCur;
}

void ScenarioDataIter::goNext() {
    process(mCur + 1);
}

GalaxyStatusAccessor ScenarioDataIter::makeAccessor() const {
    return GalaxyStatusAccessor(mParser->mScenarioData[mCur]);
}

ScenarioDataIter::ScenarioDataIter(ScenarioDataParser* pParser) {
    mParser = pParser;
    mCur = 0;
    process(0);
}

void ScenarioDataIter::process(s32 no) {
    for (mCur = no; !isEnd() && !isValidWorldNo(mCur); mCur++)
        ;
}

bool ScenarioDataIter::isValidWorldNo(s32 no) const {
    GalaxyStatusAccessor accessor(mParser->mScenarioData[no]);
    s32 worldNo = accessor.getWorldNo();
    return worldNo > 0;
}

#pragma push
#pragma opt_propagation off
ScenarioDataParser::ScenarioDataParser(const char* pName) : NameObj(pName), mScenarioData() {
    DVDDir dir;
    DVDDirEntry dirent;
    DVDOpenDir("/StageData", &dir);

    while (DVDReadDir(&dir, &dirent)) {
        if (!dirent.isDir) {
            continue;
        }

        char fileName[256];
        MR::makeScenarioArchiveFileName(fileName, sizeof(fileName), dirent.name);

        if (!MR::isFileExist(fileName, false)) {
            continue;
        }

        ScenarioData* pData = new ScenarioData(fileName);

        u32 index = mScenarioData.mCount;
        u32 nextCount = index;
        nextCount++;

        mScenarioData.mArray[index] = pData;
        mScenarioData.mCount = nextCount;
    }

    DVDCloseDir(&dir);
}
#pragma pop

ScenarioData* ScenarioDataParser::getScenarioData(const char* pName) const {
    for (s32 i = 0; i < mScenarioData.size(); i++) {
        ScenarioData* data = mScenarioData[i];
        if (MR::isEqualStringCase(data->mGalaxyName, pName)) {
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
