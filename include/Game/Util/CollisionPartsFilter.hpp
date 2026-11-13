#pragma once

#include <revolution/types.h>

class LiveActor;
class CollisionParts;

class CollisionPartsFilterBase {
public:
    CollisionPartsFilterBase() {
    }

    virtual bool isInvalidParts(const CollisionParts*) const = 0;
};

class CollisionPartsFilterSensorType : public CollisionPartsFilterBase {
public:
    CollisionPartsFilterSensorType(u32 pSensorType) : mSensorType(pSensorType) {
    }

    virtual bool isInvalidParts(const CollisionParts* pParts) const;

    /* 0x04 */ u32 mSensorType;
};

class CollisionPartsFilterActor : public CollisionPartsFilterBase {
public:
    CollisionPartsFilterActor(const LiveActor* pActor) : mActor(pActor) {
    }

    virtual bool isInvalidParts(const CollisionParts* pParts) const;

    /* 0x04 */ const LiveActor* mActor;
};
