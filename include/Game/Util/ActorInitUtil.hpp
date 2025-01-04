#pragma once

#include "Util/JMapInfo.hpp"
#include <JGeometry.hpp>

class LiveActor;

namespace MR {
    struct ObjConnection {
        const char* mObjType;       // 0x00
        int _4;
        int _8;
        int _C;
        int _10;
    };

    struct ObjLight {
        const char *mJpnName;       // 0x00
        const char* mTypeStr;       // 0x04
        int mID;                    // 0x08
    };

    bool isDataEnable(JMapInfo *, const char *);
    bool getInitSwitchType(const char **, const JMapInfo *, const char *);

    JMapInfo* makeInitActorCsvParser(const char *, const char *);
    bool isValidInitActorCsvParser(const char *, const char *);

    bool fn_8000C340(LiveActor *, const JMapInfoIter &, const char *, const char *, const char *, bool);


};
