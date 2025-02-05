#pragma once

#include "LiveActor/LiveActor.hpp"

class ModelObj : public LiveActor {
public:
    ModelObj(const char *, const char *, MtxPtr, int, int, int, bool);

    virtual ~ModelObj();
    virtual void init(const JMapInfoIter &);
    virtual void calcAndSetBaseMtx();

    MtxPtr mBaseMtx;            // 0x90
};
