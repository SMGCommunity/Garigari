#pragma once

#include <revolution.h>

// Galaxy 2 pointer offsets are recovered; unresolved types remain opaque.
class ModelManager {
public:
    ModelManager(const f32 (*)[4]);
    void init(const char*, const char*, bool);
    void startBck(const char*, const char*);
    void update();
    void calcAnim();
    void calcView();
    void entry();
    void updateDL(bool);
    void newDifferedDLBuffer();
    void* _0;
    void* _4;
    void* _8;
    void* _C;
    void* _10;
    void* _14;
    void* _18;
    void* _1C;
    const f32 (*_20)[4];
    void* _24;
    void* _28;
};
