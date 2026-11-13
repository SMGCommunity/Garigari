#pragma once

#include <revolution/types.h>

class WorldMapPointPartsHolder;

class WorldMapObjHolder {
public:
    WorldMapObjHolder(s32 worldNo);

    void init();
    void appear();
    void kill();

    /* 0x00 */ s32 mWorldNo;
    /* 0x04 */ u32 _4;   // unknown
    /* 0x08 */ u32 _8;   // unknown
    /* 0x0C */ u32 _C;   // unknown
    /* 0x10 */ u32 _10;  // unknown
    /* 0x14 */ WorldMapPointPartsHolder* mPointPartsHolder;
    /* 0x18 */ u32 _18;  // unknown
    /* 0x1C */ u32 _1C;  // unknown
};
