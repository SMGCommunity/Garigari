#pragma once

#include "Game/LiveActor/ActorStateBase.hpp"

class ActorCameraInfo;
class JMapInfoIter;
class LiveActor;

class ActorStateDemoAppearance : public ActorStateBase< LiveActor > {
public:
    ActorStateDemoAppearance(LiveActor* pActor, const JMapInfoIter& rIter, const char* pActionName);

    virtual void appear();

    void exeAppear();
    void exeWait();

    bool isDemoEnd() const;

    /* 0x10 */ ActorCameraInfo* mCameraInfo;
    /* 0x14 */ const char* mActionName;
    /* 0x18 */ s32 mCameraTime;
    /* 0x1C */ s32 _1C;
    /* 0x20 */ bool mIsInitCamera;
    /* 0x21 */ bool _21;
};
