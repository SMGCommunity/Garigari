#pragma once

#include "Game/LiveActor/LiveActor.hpp"
#include <JSystem/JGeometry/TMatrix.hpp>

class CollectTico;
class PartsModel;

/// @brief Silver Star
class StrayTico : public LiveActor {
public:
    StrayTico(const char*, CollectTico*);

    virtual void init(const JMapInfoIter&);
    virtual void appear();
    virtual void control();
    virtual void calcAndSetBaseMtx();
    virtual void attackSensor(HitSensor*, HitSensor*);
    virtual bool receiveMsgPush(HitSensor*, HitSensor*);
    virtual bool receiveMsgPlayerAttack(u32, HitSensor*, HitSensor*);
    virtual bool receiveOtherMsg(u32, HitSensor*, HitSensor*);

    void initSensor();
    void setShadowDrop(const char*);
    void initShadow() NO_INLINE;
    void startGlad();
    void launch(const TPos3f&);
    void updateWarp();
    void updateChase();
    bool tryStartBindMove();
    bool tryEndBindMove();
    bool tryNigeroDrop();
    bool requestCompleteDemo(const TVec3f&, const TVec3f&, f32);

    bool isNigeroTakeable() const NO_INLINE;
    bool isEnableSpin() const;
    bool isRescued() const;
    bool isCompleteDemoEnd() const;
    void noticeEnd();

    void exeWait();
    void exeGlad();
    void exeChase();
    void exeLauncherCamera();
    void exeCompleteDemo();
    void exeBindMove();
    void exeBindEnd();

    /* 0x90 */ CollectTico* mHost;
    /* 0x94 */ PartsModel* mItemBubbleModel;
    /* 0x98 */ TQuat4f mRotateQuat;
    /* 0xA8 */ TVec3f mFrontVec;
    /* 0xB4 */ TVec3f _B0;
    /* 0xC0 */ TVec3f _BC;
    /* 0xCC */ TVec3f _C8;
    /* 0xD8 */ TVec3f _D4;
    /* 0xE4 */ TVec3f _E0;
    /* 0xF0 */ f32 _EC;
    /* 0xF4 */ f32 _F0;
};
