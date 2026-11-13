#include "Game/World/WorldMapObjFunction.hpp"
#include "Game/Util/ObjUtil.hpp"
#include "Game/World/WorldMapObjHolder.hpp"
#include <cstdio>

const JMapInfo* WorldMapObjFunction::createCsvParser(const WorldMapObjHolder* pObjHolder, const char* pCsvName) {
    char fileName[0x40];
    snprintf(fileName, sizeof(fileName), "WorldMap%02d.arc", pObjHolder->mWorldNo);
    return MR::createCsvParserFromFile(fileName, pCsvName);
}
