#pragma once

#include "Game/LiveActor/LiveActor.hpp"
#include "Game/Util/Array.hpp"
#include <JSystem/JGeometry/TMatrix.hpp>

class ActorCameraInfo;
class StrayTico;

class CollectTico : public LiveActor {
public:
    CollectTico(const char*);

    virtual void init(const JMapInfoIter&);

    void exeWait();
    void exeCompleteDemo();
    void exeFlash();
    void exeAppearPowerStar();
    inline void exeTryStartDemo();
    s32 calcNoRescuedCount() const;
    void launch(const TPos3f&);
    void startAppearPowerStar();

    /* 0x90 */ ActorCameraInfo* mCameraInfo;
    /* 0x94 */ StrayTico** mStrayTicos;
    /* 0x94 */ s32 mTicoNum;
    /* 0x98 */ TVec3f _98;
    /* 0xA8 */ u8 _A8;
    /* 0xA9 */ bool mHasCamera;
    /* 0xAA */ bool mCompleteHere;     // ObjArg0 if set, the silver stars will do the completion animation at the position this object is placed
};
