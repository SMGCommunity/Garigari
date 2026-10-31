#include "Game/Util/FixedPosition.hpp"
#include "Game/LiveActor/LiveActor.hpp"
#include "Game/Util/JMapInfo.hpp"
#include "Game/Util/JointUtil.hpp"
#include "Game/Util/LiveActorUtil.hpp"
#include "Game/Util/MtxUtil.hpp"
#include "Game/Util/ObjUtil.hpp"
#include "math_types.hpp"
#include <JSystem/JGeometry/TVec.hpp>
#include <revolution/types.h>

FixedPosition::FixedPosition(const LiveActor* pActor, const char* pStr, const TVec3f& rVec1, const TVec3f& rVec2) {
    init(MR::getJointMtx(pActor, pStr), rVec1, rVec2);
}

FixedPosition::FixedPosition(const LiveActor* pActor, const TVec3f& rVec1, const TVec3f& rVec2) {
    init(pActor->getBaseMtx(), rVec1, rVec2);
}

FixedPosition::FixedPosition(MtxPtr pMtx, const TVec3f& rVec1, const TVec3f& rVec2) {
    init(pMtx, rVec1, rVec2);
}

FixedPosition::FixedPosition(const LiveActor* pActor1, const char* pStr, const LiveActor* pActor2) {
    if (pActor2 == nullptr) {
        pActor2 = pActor1;
    }

    const char* jointName = nullptr;
    TVec3f trans(0.0f);
    TVec3f rotate(0.0f);

    ResourceHolder* resourceHolder = MR::getResourceHolder(pActor2);
    const JMapInfo* csvParser = MR::tryCreateCsvParser(resourceHolder, "%s.bcsv", pStr);

    if (csvParser != nullptr) {
        MR::getCsvDataStrOrNULL(&jointName, csvParser, "JointName", 0);
        MR::getCsvDataVec(&trans, csvParser, "Trans", 0);
        MR::getCsvDataVec(&rotate, csvParser, "Rotate", 0);
    }

    if (jointName == nullptr) {
        init(pActor1->getBaseMtx(), trans, rotate);
    } else {
        init(MR::getJointMtx(pActor1, jointName), trans, rotate);
    }
}

void FixedPosition::calc() {
    // FIXME
    // decomp.me: https://decomp.me/scratch/u8ALi
    // This function calls MR::makeMtxWithoutScale, which should be in MtxUtil.hpp but isn't!
    // Until MtxUtil gets a PR to include that function in the header, this function cannot be decompiled!

    mMtx.identity();
    mMtx.setRotate(mLocalRotate * PI_180);
    mMtx.setTrans(mLocalTrans);

    if (mBaseMtx != nullptr) {
        TMtx34f baseMtx;
        baseMtx.set(mBaseMtx);
        mMtx.concat(baseMtx, mMtx);
    }

    if (mNormalizeScale) {
        // MR::makeMtxWithoutScale(&mMtx, mMtx);
    }
}

void FixedPosition::setBaseMtx(MtxPtr pBaseMtx) {
    mBaseMtx = pBaseMtx;
}

void FixedPosition::setLocalTrans(const TVec3f& rLocalTrans) {
    // FIXME
    // decomp.me: https://decomp.me/scratch/SOjN5
    // TVec3f::set is being inlined even though it shouldn't be.

    mLocalTrans.set(rLocalTrans);
}

void FixedPosition::init(MtxPtr pBaseMtx, const TVec3f& rLocalTrans, const TVec3f& rLocalRotate) {
    mBaseMtx = pBaseMtx;
    mLocalTrans.set(rLocalTrans);
    mLocalRotate.set(rLocalRotate);
    mMtx.identity();
    mNormalizeScale = true;
}
