#pragma once

#include "LiveActor/LiveActor.hpp"

// The separately placed destructor must not emit a second vtable.
#ifdef MODELOBJ_NO_VTABLE
class __declspec(novtable) ModelObj : public LiveActor {
#else
class ModelObj : public LiveActor {
#endif
public:
    ModelObj(const char *, const char *, MtxPtr, int, int, int, bool);

    virtual ~ModelObj();
    virtual void init(const JMapInfoIter &);
    virtual void calcAndSetBaseMtx();

    MtxPtr mBaseMtx;            // 0x90
};
