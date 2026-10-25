#pragma once

#include "Game/LiveActor/LiveActor.hpp"

class WorldMapObjHolder;

class MiniWorldWarpPoint : public LiveActor {
public:
    MiniWorldWarpPoint(WorldMapObjHolder* pObjHolder, s32 pointIndex, bool isWorldNext);

    virtual void init(const JMapInfoIter& rIter);
    virtual void makeActorAppeared();
    virtual void makeActorDead();

    bool tryStartSound(s32 distance);
    void setAllEffectDrawOrder(s32 drawOrder);

    /* 0x90 */ WorldMapObjHolder* mObjHolder;
    /* 0x94 */ s32 mPointIndex;
    /* 0x98 */ bool mIsWorldNext;
};
