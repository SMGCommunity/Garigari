#pragma once

#include <JSystem/JGeometry/TMatrix.hpp>
#include <JSystem/JGeometry/TVec.hpp>
#include <revolution.h>
#include <revolution/mtx/mtx.h>

namespace MR {
    void makeMtxRotate(MtxPtr, f32, f32, f32);
    void makeMtxRotate(MtxPtr, const TVec3f&);
    void preScaleMtx(MtxPtr, const TVec3f&);
    void makeMtxTRS(MtxPtr, const TVec3f&, const TVec3f&, const TVec3f&);
    void makeMtxTR(MtxPtr, f32, f32, f32, f32, f32, f32);
    void makeMtxTR(MtxPtr, const TVec3f&, const TVec3f&);
    void makeMtxSideUp(TPos3f*, const TVec3f&, const TVec3f&);
    void makeMtxSideUpPos(TPos3f*, const TVec3f&, const TVec3f&, const TVec3f&);
    void makeMtxSideFront(TPos3f*, const TVec3f&, const TVec3f&);
    void makeMtxUpSide(TPos3f*, const TVec3f&, const TVec3f&);
    void makeMtxUpSidePos(TPos3f*, const TVec3f&, const TVec3f&, const TVec3f&);
    void makeMtxUpFront(TPos3f*, const TVec3f&, const TVec3f&);
    void makeMtxUpFrontPos(TPos3f*, const TVec3f&, const TVec3f&, const TVec3f&) NO_INLINE;
    void makeMtxFrontSidePos(TPos3f*, const TVec3f&, const TVec3f&, const TVec3f&);
    void makeMtxFrontUp(TPos3f*, const TVec3f&, const TVec3f&);
    void makeMtxFrontUpPos(TPos3f*, const TVec3f&, const TVec3f&, const TVec3f&) NO_INLINE;
    void makeMtxUpNoSupport(TPos3f*, const TVec3f&);
    void makeMtxUpNoSupportPos(TPos3f*, const TVec3f&, const TVec3f&);
    void makeMtxFrontNoSupport(TPos3f*, const TVec3f&);
    void makeMtxFrontNoSupportPos(TPos3f*, const TVec3f&, const TVec3f&);
    void setMtxTrans(MtxPtr, f32, f32, f32);
    void addTransMtx(MtxPtr, const TVec3f&);
    void addTransMtxLocal(MtxPtr, const TVec3f&);
    void addTransMtxLocalX(MtxPtr, f32);
    void addTransMtxLocalY(MtxPtr, f32);
    void addTransMtxLocalZ(MtxPtr, f32);
    void extractMtxXDir(MtxPtr, TVec3f*);
    void extractMtxYDir(MtxPtr, TVec3f*);
    void extractMtxZDir(MtxPtr, TVec3f*);
    void extractMtxXYZDir(MtxPtr, TVec3f*, TVec3f*, TVec3f*);
    void extractMtxTrans(MtxPtr, TVec3f*);
    void preScaleMtx(MtxPtr, const TVec3f&);

    template < typename T >
    f32 sqrt(f32);

    bool isSameMtxRot(MtxPtr, MtxPtr);

    MtxPtr tmpMtxScale(f32, f32, f32);
    MtxPtr tmpMtxRotXRad(f32);
    MtxPtr tmpMtxRotYRad(f32);
    MtxPtr tmpMtxRotZRad(f32);
    MtxPtr tmpMtxRotXDeg(f32);
    MtxPtr tmpMtxRotYDeg(f32);
    MtxPtr tmpMtxRotZDeg(f32);
    void orderRotateMtx(s16, const TVec3f&, MtxPtr);
    void inverseConcatMtx(MtxPtr, MtxPtr, TMtx34f*);
    void turnMtxToXDirRate(TPos3f*, const TVec3f&, f32);
};  // namespace MR
