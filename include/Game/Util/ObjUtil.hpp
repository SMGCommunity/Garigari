#pragma once

#include "Util/JMapInfo.hpp"

class NameObj;
class LiveActor;
class ResourceHolder;

namespace MR {
    void requestMovementOn(NameObj *);
    void requestMovementOff(NameObj *);

    void connectToScene(NameObj *, int, int, int, int);
    void connectToScene(LiveActor *, int, int, int, int);

    void connectToSceneMapObjMovement(NameObj *);

    ResourceHolder* createAndAddResourceHolder(const char *);

    JMapInfo* createCsvParserFromFile(const char *, const char *, ...);

    void getCsvDataStrOrNULL(const char **, const JMapInfo *, const char *, s32);
    const JMapInfoIter getCsvDataStrByElement(const char **, const JMapInfo *, const char *, const char *, const char *);

    s32 getCsvDataElementNum(const JMapInfo *);

    void getCsvDataVec(Vec *, const JMapInfo *, const char *, s32);

    bool isExistElement(const JMapInfo *, const char *, const char *);
};
