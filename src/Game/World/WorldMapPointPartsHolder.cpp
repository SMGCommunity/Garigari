#include "Game/World/WorldMapPointPartsHolder.hpp"
#include "Game/Util/JMapInfo.hpp"
#include "Game/Util/LiveActorUtil.hpp"
#include "Game/Util/ObjUtil.hpp"
#include "Game/Util/StringUtil.hpp"
#include "Game/World/MiniEarthenPipe.hpp"
#include "Game/World/MiniWorldWarpPoint.hpp"
#include <decomp.h>

EXTERN_UNKNOWN_FUNC_NO_ARGS(u32, 804E82A0)
EXTERN_UNKNOWN_FUNC(JMapInfo*, 804F24E0, WorldMapObjHolder*, const char*)
EXTERN_UNKNOWN_FUNC(TVec3f&, 804F2550, WorldMapObjHolder*, s32)
EXTERN_UNKNOWN_FUNC(s32, 804F2B60, WorldMapObjHolder*)

namespace {
    static TVec3f sWorldWarpPointOffset(0.0f, 300.0f, 300.0f);

    bool isWorldWarpPoint(const char* pName) NO_INLINE {
        return MR::isEqualString(pName, "WorldWarpPoint");
    }

    bool isStarRoadWarpPoint(const char* pName) NO_INLINE {
        return MR::isEqualString(pName, "StarRoadWarpPoint");
    }

    bool isStarCheckPoint(const char* pName) NO_INLINE {
        return MR::isEqualString(pName, "StarCheckPoint");
    }

    bool isStarPieceMine(const char* pName) NO_INLINE {
        return MR::isEqualString(pName, "StarPieceMine");
    }

    bool isEarthenPipe(const char* pName) NO_INLINE {
        return MR::isEqualString(pName, "EarthenPipe");
    }

    bool isTicoRouteCreator(const char* pName) NO_INLINE {
        return MR::isEqualString(pName, "TicoRouteCreator");
    }
};  // namespace WorldMapPointPartsFunction

WorldMapPointPart::WorldMapPointPart() : mPartsTypeName(), mPointIndex(), mPartsIndex(), mParam00(-1), mParam01(-1), mParam02(-1), mActor() {
}

WorldMapPointPartsHolder::WorldMapPointPartsHolder(WorldMapObjHolder* pObjHolder)
    : mObjHolder(pObjHolder), mPointParts(), mPointPartsNum(), mUnlockedWorldNum() {
}

void WorldMapPointPartsHolder::init() {
    JMapInfo* info = fn_804F24E0(mObjHolder, "PointParts");
    if (info == nullptr) {
        return;
    }

    mUnlockedWorldNum = fn_804E82A0();
    s32 worldNo = fn_804F2B60(mObjHolder);

    mPointPartsNum = MR::getCsvDataElementNum(info);
    mPointParts = new WorldMapPointPart[mPointPartsNum];

    for (s32 i = 0; i < mPointPartsNum; i++) {
        WorldMapPointPart* part = &mPointParts[i];
        MR::getCsvDataStr(&part->mPartsTypeName, info, "PartsTypeName", i);
        MR::getCsvDataS32(&part->mPointIndex, info, "PointIndex", i);
        MR::getCsvDataS32(&part->mPartsIndex, info, "PartsIndex", i);
        MR::getCsvDataS32(&part->mParam00, info, "Param00", i);
        MR::getCsvDataS32(&part->mParam01, info, "Param01", i);

        if (MR::hasCsvItem(info, "Param02")) {
            MR::getCsvDataS32(&part->mParam02, info, "Param02", i);
        }

        if (::isWorldWarpPoint(part->mPartsTypeName)) {
            part->mActor = new MiniWorldWarpPoint(mObjHolder, part->mPointIndex, part->mParam00 > worldNo);
            MR::setPosition(part->mActor, fn_804F2550(mObjHolder, part->mPointIndex));
            part->mActor->mPosition += sWorldWarpPointOffset;
            part->mActor->initWithoutIter();
        } else if (::isStarRoadWarpPoint(part->mPartsTypeName)) {
            // TODO
            MR::setPosition(part->mActor, fn_804F2550(mObjHolder, part->mPointIndex));
            part->mActor->initWithoutIter();
        } else if (::isStarCheckPoint(part->mPartsTypeName)) {
            // TODO
            MR::setPosition(part->mActor, fn_804F2550(mObjHolder, part->mPointIndex));
            part->mActor->initWithoutIter();
        } else if (::isStarPieceMine(part->mPartsTypeName)) {
            // TODO
            MR::setPosition(part->mActor, fn_804F2550(mObjHolder, part->mPointIndex));
            part->mActor->initWithoutIter();
        } else if (::isEarthenPipe(part->mPartsTypeName)) {
            part->mActor = new MiniEarthenPipe();
            MR::setPosition(part->mActor, fn_804F2550(mObjHolder, part->mPointIndex));
            part->mActor->initWithoutIter();
        } else if (::isTicoRouteCreator(part->mPartsTypeName)) {
            // TODO
            MR::setPosition(part->mActor, fn_804F2550(mObjHolder, part->mPointIndex));
            part->mActor->initWithoutIter();
        } else {
            // TODO
            MR::setPosition(part->mActor, fn_804F2550(mObjHolder, part->mPointIndex));
            part->mActor->initWithoutIter();
        }

        MR::setClippingFarMax(part->mActor);
        part->mActor->makeActorDead();

        if (!::isStarRoadWarpPoint(part->mPartsTypeName)) {
            MR::invalidateClipping(part->mActor);
        }
    }
}

WorldMapPointPart* WorldMapPointPartsHolder::findPointPart(s32 pointIndex) {
    for (s32 i = 0; i < mPointPartsNum; i++) {
        WorldMapPointPart* part = &mPointParts[i];

        if (part->mPointIndex == pointIndex) {
            return part;
        }
    }

    return nullptr;
}
