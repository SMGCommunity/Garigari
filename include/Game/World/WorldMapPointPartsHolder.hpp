#pragma once

#include <revolution/types.h>

class LiveActor;
class WorldMapObjHolder;

class WorldMapPointPart {
public:
    WorldMapPointPart();

    /* 0x00 */ const char* mPartsTypeName;
    /* 0x04 */ s32 mPointIndex;
    /* 0x08 */ s32 mPartsIndex;
    /* 0x0C */ s32 mParam00;
    /* 0x10 */ s32 mParam01;
    /* 0x14 */ s32 mParam02;
    /* 0x18 */ LiveActor* mActor;
};

class WorldMapPointPartsHolder {
public:
    WorldMapPointPartsHolder(WorldMapObjHolder* pObjHolder);

    void init();
    WorldMapPointPart* findPointPart(s32 pointIndex);

    /* 0x0 */ WorldMapObjHolder* mObjHolder;
    /* 0x4 */ WorldMapPointPart* mPointParts;
    /* 0x8 */ s32 mPointPartsNum;
    /* 0xC */ s32 mUnlockedWorldNum;
};
