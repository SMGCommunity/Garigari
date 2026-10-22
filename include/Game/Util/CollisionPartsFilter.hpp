#pragma once

#include "Game/LiveActor/LiveActor.hpp"
#include "Game/Map/CollisionParts.hpp"

class CollisionPartsFilterBase {
public:
    inline CollisionPartsFilterBase() {
    }

    virtual bool isInvalidParts(const CollisionParts*) const = 0;
};

class CollisionPartsFilterSensorType : public CollisionPartsFilterBase {
public:
    inline CollisionPartsFilterSensorType(u32 pSensorType) {
        mSensorType = pSensorType;
    }

    virtual bool isInvalidParts(const CollisionParts* pParts) const;

    /* 0x04 */ u32 mSensorType;
};

class CollisionPartsFilterActor : public CollisionPartsFilterBase {
public:
    inline CollisionPartsFilterActor(const LiveActor* pActor) : mActor(pActor) {
    }

    virtual bool isInvalidParts(const CollisionParts* pParts) const;

    /* 0x04 */ const LiveActor* mActor;
};
