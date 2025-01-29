#pragma once

#include "revolution/mtx/mtx.h"
#include <revolution.h>
#include <JGeometry.hpp>

namespace MR {
    void setMtxTrans(MtxPtr, f32, f32, f32);
    void addTransMtx(MtxPtr, const TVec3f &);
    void addTransMtxLocal(MtxPtr, const TVec3f &);
    void addTransMtxLocalX(MtxPtr, f32);
    void addTransMtxLocalY(MtxPtr, f32);
    void addTransMtxLocalZ(MtxPtr, f32);
    void extractMtxXDir(MtxPtr, TVec3f *);
    void extractMtxYDir(MtxPtr, TVec3f *);
    void extractMtxZDir(MtxPtr, TVec3f *);
    void extractMtxXYZDir(MtxPtr, TVec3f *, TVec3f *, TVec3f *);
    void extractMtxTrans(MtxPtr, TVec3f *);

    template<typename T>
    f32 sqrt(f32);

    bool isSameMtxRot(MtxPtr, MtxPtr);

    MtxPtr tmpMtxScale(f32, f32, f32);
    MtxPtr tmpMtxRotXRad(f32);
    MtxPtr tmpMtxRotYRad(f32);
    MtxPtr tmpMtxRotZRad(f32);
    MtxPtr tmpMtxRotXDeg(f32);
    MtxPtr tmpMtxRotYDeg(f32);
    MtxPtr tmpMtxRotZDeg(f32);
    void orderRotateMtx(s16, const TVec3f &, MtxPtr);
    void inverseConcatMtx(MtxPtr, MtxPtr, TMtx34f *);
};
