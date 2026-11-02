#include "Game/Util/FixedPosition.hpp"
#include "Game/LiveActor/LiveActor.hpp"
#include "Game/Util/JMapInfo.hpp"
#include "Game/Util/JointUtil.hpp"
#include "Game/Util/LiveActorUtil.hpp"
#include "Game/Util/ObjUtil.hpp"

FixedPosition::FixedPosition(const LiveActor* pActor, const char* pJointName, const TVec3f& rLocalTrans, const TVec3f& rLocalRotate) {
    init(MR::getJointMtx(pActor, pJointName), rLocalTrans, rLocalRotate);
}

FixedPosition::FixedPosition(const LiveActor* pActor, const TVec3f& rLocalTrans, const TVec3f& rLocalRotate) {
    init(pActor->getBaseMtx(), rLocalTrans, rLocalRotate);
}

FixedPosition::FixedPosition(MtxPtr pBaseMtx, const TVec3f& rLocalTrans, const TVec3f& rLocalRotate) {
    init(pBaseMtx, rLocalTrans, rLocalRotate);
}

FixedPosition::FixedPosition(const LiveActor* pActor, const char* pResName, const LiveActor* pResActor) {
    if (pResActor == nullptr) {
        pResActor = pActor;
    }

    const char* pJointName = nullptr;
    TVec3f trans(0.0f);
    TVec3f rotate(0.0f);

    ResourceHolder* pResourceHolder = MR::getResourceHolder(pResActor);
    const JMapInfo* pCsvParser = MR::tryCreateCsvParser(pResourceHolder, "%s.bcsv", pResName);

    if (pCsvParser != nullptr) {
        MR::getCsvDataStrOrNULL(&pJointName, pCsvParser, "JointName", 0);
        MR::getCsvDataVec(&trans, pCsvParser, "Trans", 0);
        MR::getCsvDataVec(&rotate, pCsvParser, "Rotate", 0);
    }

    if (pJointName == nullptr) {
        init(pActor->getBaseMtx(), trans, rotate);
    } else {
        init(MR::getJointMtx(pActor, pJointName), trans, rotate);
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
        TPos3f baseMtx;
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
    mLocalTrans.set(rLocalTrans);
}

void FixedPosition::init(MtxPtr pBaseMtx, const TVec3f& rLocalTrans, const TVec3f& rLocalRotate) {
    mBaseMtx = pBaseMtx;
    mLocalTrans.set(rLocalTrans);
    mLocalRotate.set(rLocalRotate);
    mMtx.identity();
    mNormalizeScale = true;
}
