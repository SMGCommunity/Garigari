#pragma once

#include "LiveActor/LiveActor.hpp"

class FixedPosition;

class PartsModel : public LiveActor {
public:
    PartsModel(LiveActor *pHost, const char *pName, const char *pModelName, MtxPtr pMtx, int drawBufferType, bool);

    virtual ~PartsModel();
    virtual void init(const JMapInfoIter &rIter);
    virtual void movement();
    virtual void calcAnim();
    virtual void calcViewAndEntry();
    virtual void makeActorAppeared();
    virtual void makeActorDead();
    virtual void calcAndSetBaseMtx();

    void initFixedPosition(const TVec3f &rOffset, const TVec3f &rRotate, const char *pJointName);
    void initFixedPosition(const char *pJointName);
    void initFixedPosition(MtxPtr pMtx, const TVec3f &rOffset, const TVec3f &rRotate);
    void loadFixedPosition(const char *pJointName, const LiveActor *pActor);
    void offFixedPosNormalizeScale();

    LiveActor* mHost;         // _90
    FixedPosition* mFixedPos; // _94
    MtxPtr mMtx;              // _98
    bool mCalcOwnMatrix;      // _9C
    bool mCheckHiddenHost;    // _9D
    bool mIsDead;             // _9E
};
