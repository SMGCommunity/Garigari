#pragma once

#include "LiveActor/PartsModel.hpp"

class LodCtrl;

struct DummyDisplayModelInfo {
    const char* mModelName; // _0
    const char* mInitName;  // _4
    Vec mOffset;            // _8
    s32 _14;
    const char* mAnimName;  // _18
    bool mHasColorChange;   // _1C
};

class DummyDisplayModel : public PartsModel {
public:
    DummyDisplayModel(LiveActor *pHost, const DummyDisplayModelInfo *pInfo, int, s32, s32);

    virtual ~DummyDisplayModel();
    virtual void init(const JMapInfoIter &rIter);
    virtual void makeActorAppeared();
    virtual void makeActorDead();
    virtual void control();
    virtual void calcAndSetBaseMtx();

    DummyDisplayModelInfo* mModelInfo; // _A0
    s32 mModelId;                      // _A4
    s32 mColorFrame;                   // _A8
    LodCtrl* mLodCtrl;                 // _AC
    bool mIsCrystalItem;               // _B0
};

namespace MR {
    DummyDisplayModel* tryCreateDummyModel(LiveActor *pHost, const JMapInfoIter &rIter, s32, int);
    DummyDisplayModel* createDummyDisplayModel(LiveActor *pHost, const JMapInfoIter &rIter, s32, const TVec3f &, const TVec3f &);
    DummyDisplayModel* createDummyDisplayModel(LiveActor *pHost, const JMapInfoIter &rIter, const char *, s32);
    DummyDisplayModel* createDummyDisplayModel(LiveActor *pHost, const JMapInfoIter &rIter, MtxPtr, s32, const TVec3f &, const TVec3f &);
    DummyDisplayModel* createDummyDisplayModelCrystalItem(LiveActor *pHost, const JMapInfoIter &rIter, const TVec3f &, const TVec3f &);
    DummyDisplayModel* createDummyDisplayModelCrystalItem(LiveActor *pHost, s32, const TVec3f &, const TVec3f &);
    s32 getDummyDisplayModelId(const JMapInfoIter &, s32);
    s32 getDummyDisplayModelId(const LiveActor *);
}
