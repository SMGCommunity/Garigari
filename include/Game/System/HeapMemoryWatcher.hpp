#pragma once

#include <revolution/types.h>

class JKRExpHeap;
class JKRHeap;
class JKRSolidHeap;

class HeapMemoryWatcher {
public:
    HeapMemoryWatcher();

    JKRHeap* getHeapNapa(const JKRHeap*);
    JKRHeap* getHeapGDDR3(const JKRHeap*);
    void createWorldMapHeap();
    void createFileCacheHeapOnGameHeap(u32);
    void createSceneHeapOnGameHeap();
    void adjustStationedHeapNapa();
    void adjustStationedHeapGDDR3();
    void setCurrentHeapToStationedHeap();
    void setCurrentHeapToSystemHeap();
    void setCurrentHeapToSceneHeap();
    void resetGameHeapNapaAndGDDR3();
    void resetGameHeapNapa();
    void resetGameHeapGDDR3() NO_INLINE;
    void destroyWorldMapHeap();
    void destroyFileCache();
    void fn_804BCD50();
    void destroySceneHeap();
    static void createRootHeap();
    void createHeaps();
    void createGameHeap();
    static void memoryErrorCallback(void*, u32, int);
    void checkRestMemory();

    /* 0x00 */ JKRExpHeap* mStationedHeapNapa;
    /* 0x04 */ JKRExpHeap* mStationedHeapGDDR;
    /* 0x08 */ JKRExpHeap* mGameHeapNapa;
    /* 0x0C */ JKRExpHeap* mGameHeapGDDR;
    /* 0x10 */ JKRSolidHeap* mWorldMapHeap;
    /* 0x14 */ JKRSolidHeap* mFileCacheHeap;
    /* 0x18 */ JKRHeap* _18;
    /* 0x1C */ JKRSolidHeap* mSceneHeapNapa;
    /* 0x20 */ JKRSolidHeap* mSceneHeapGDDR;
    /* 0x24 */ JKRExpHeap* mWPadHeap;
    /* 0x28 */ JKRExpHeap* mHomeButtonLayoutHeap;
    /* 0x2C */ JKRSolidHeap* mAudSystemHeap;
    static JKRExpHeap* sRootHeapGDDR3;
};
