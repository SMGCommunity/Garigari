#pragma once

#include "Game/LiveActor/LiveActor.hpp"

class ActorLayout;
class WorldMapObjHolder;

class MiniStarWorldPoint : public LiveActor {
public:
    MiniStarWorldPoint(WorldMapObjHolder* pObjHolder, s32 pointIndex, s32 param00);

    virtual void init(const JMapInfoIter& rIter);
    virtual void makeActorAppeared();
    virtual void control();

    void initStateLayout();

    /* 0x90 */ WorldMapObjHolder* mObjHolder;
    /* 0x94 */ s32 mPointIndex;
    /* 0x98 */ s32 mWorldNo;
    /* 0x9C */ ActorLayout* mStateLayout;
};
