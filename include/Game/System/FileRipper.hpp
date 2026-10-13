#pragma once

#include <revolution.h>

class JKRHeap;

class FileRipper {
public:
    enum AllocDirection {
        ALLOC_DIRECTION_FORWARD = 0,
        ALLOC_DIRECTION_BACKWARD = 1,
    };

    static void setup(u32, JKRHeap*);
    static s32 checkCompressed(const u8*);
    static void* loadToMainRAM(const char*, u8*, bool, JKRHeap*, AllocDirection);
    static bool decompressFromDVD(DVDFileInfo*, void*, u32, u32, const u8*, u32);
    static bool decompressSzsSub(u8*, u8*);
    static u8* readSrcDataFirst();
    static u8* readSrcDataNext(u8*);
};
