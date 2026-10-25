#pragma once

#include "Game/LiveActor/LiveActor.hpp"

class DemoObj : public LiveActor {
public:
    DemoObj(const char* pName, MtxPtr pMtx);

    virtual ~DemoObj();
    virtual void init(const JMapInfoIter& rIter);
    virtual void calcAndSetBaseMtx();

    /* 0x90 */ MtxPtr mBaseMtx;
};

class ModelObj : public LiveActor {
public:
    ModelObj(const char*, const char*, MtxPtr, int, int, int, bool);

    virtual ~ModelObj();
    virtual void init(const JMapInfoIter&);
    virtual void calcAndSetBaseMtx();

    /* 0x90 */ MtxPtr mBaseMtx;
};
