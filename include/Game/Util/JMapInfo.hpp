#pragma once

#include <revolution.h>

struct JMapItem {
    u32 mHash;       // _0
    u32 mMask;       // _4
    u16 mOffsetData; // _8
    u8 mShift;       // _A
    u8 mType;        // _B
};

struct JMapData {
    s32 _0;
    s32 mNumData;      // _4
    s32 mDataOffset;   // _8
    u32 _C;
    JMapItem* mItems;  // _10
};

class JMapInfoIter;

class JMapInfo {
public:
    const JMapData* mData;      // 0x00
    const char* mName;          // 0x04
};

class JMapInfoIter {
public:
    inline JMapInfoIter() { }
    inline JMapInfoIter(const JMapInfo *pInfo, s32 index) : mInfo(pInfo), mIndex(index) {}

    const JMapInfo* mInfo;      // 0x00
    s32 mIndex;                 // 0x04
};