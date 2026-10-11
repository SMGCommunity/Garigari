#pragma once

#include "Game/System/FileHolder.hpp"
#include "Game/System/OSThreadWrapper.hpp"
#include <JSystem/JKernel/JKRDvdRipper.hpp>

struct RequestFileInfo {
    enum RequestType {
        REQUEST_LOAD = 0,
        REQUEST_MOUNT = 1,
    };

    /* 0x00 */ RequestType mType;
    /* 0x04 */ JKRDvdRipper::EAllocDirection mAllocDirection;
    /* 0x08 */ char mFileName[0x80];
    /* 0x88 */ volatile u32 _88;
    /* 0x8C */ FileHolderFileEntry* mFileEntry;
};

class FileLoaderThread : public OSThreadWrapper {
public:
    FileLoaderThread(int, int, JKRHeap*);

    virtual void* run();

    void loadToMainRAM(RequestFileInfo*);
    void mountArchiveAndStartCreateResource(RequestFileInfo*);
};
