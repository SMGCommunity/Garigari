#pragma once

#include "JSystem/JGeometry/TMatrix.hpp"
#include <revolution/types.h>
#include <revolution/mtx.h>
#include <JSystem/JGeometry/TVec.hpp>

class LiveActor;

class FixedPosition {
public:
    FixedPosition(const LiveActor*, const char*, const TVec3f&, const TVec3f&);
    FixedPosition(const LiveActor*, const TVec3f&, const TVec3f&);
    FixedPosition(MtxPtr, const TVec3f&, const TVec3f&);
    FixedPosition(const LiveActor*, const char*, const LiveActor*);

    void calc();
    void setBaseMtx(MtxPtr);
    void setLocalTrans(const TVec3f&);
    void init(MtxPtr, const TVec3f&, const TVec3f&);

    /* 0x00 */ MtxPtr mBaseMtx;
    /* 0x04 */ TVec3f mLocalTrans;
    /* 0x10 */ TVec3f mLocalRotate;
    /* 0x1C */ TPos3f mMtx;
    /* 0x4C */ bool mNormalizeScale;
};
