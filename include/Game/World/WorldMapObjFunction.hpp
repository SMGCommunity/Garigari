#pragma once

class JMapInfo;
class WorldMapObjHolder;

namespace WorldMapObjFunction {
    const JMapInfo* createCsvParser(const WorldMapObjHolder* pObjHolder, const char* pCsvName);
};
