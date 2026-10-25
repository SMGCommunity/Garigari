#pragma once

#include "revolution/types.h"
#include <JSystem/JGeometry/TVec.hpp>
#include <revolution.h>
#include <revolution/mtx.h>

class ResourceHolder;
class LiveActor;
class Binder;
class XanimePlayer;
class MultiEmitter;
class Triangle;

class EffectKeeper {
public:
    EffectKeeper(const char*, ResourceHolder*, int, const char*);

    void init(LiveActor*);
    void initAfterPlacementForAttributeEffect(MtxPtr);
    void setBinder(const Binder*);
    void addEffect(const char*, LiveActor*);
    void registerEffect(const char*, TVec3f*, const TVec3f*, const TVec3f*, const char*);
    void registerEffect(const char*, MtxPtr, const char*, const char*);
    void registerEffect(const char*, MtxPtr, const TVec3f*, const char*, const char*);
    void registerEffectWithoutSRT(const char*, const char*);
    void registerSyncBckEffect(XanimePlayer*, const char*, const char*, long, float, float, bool);
    void createEmitter(const char*);
    void deleteEmitter(const char*);
    void forceDeleteEmitter(const char*);
    void deleteEmitterAll();
    void forceDeleteEmitterAll();
    void fn_80233A20();
    void fn_80233A30();
    void getEmitter(long) const;
    void getEmitter(const char*) const;
    void changeEffectName(const char*, const char*);
    void update();
    void updateSyncBckEffect();
    void syncEffectBck(MultiEmitter*);
    void updateAttributeEffect();
    void stopEmitterOnClipped();
    void playEmitterOffClipped();
    void clear();
    void changeBck();
    void fn_80234050();
    void onDraw();
    void offDraw();
    void onCalcEmitter();
    void offCalcEmitter();
    void enableSort();
    void finalizeSort();
    bool isRegisteredEmitter(const char*) const;
    void checkExistenceAttributeEffect();
    void registerMultiEmitter(MultiEmitter*, const char*, const char*);
    void updateFloorCode();
    void updateFloorCode(Triangle*);
    bool isTypeAttributeEffect(const char*) const;

    /* 0x00 */ const char* _0;
    /* 0x04 */ const char* _4;
    /* 0x08 */ ResourceHolder* mResourceHolder;
    /* 0x0C */ u32* _C;
    /* 0x10 */ int mSize_C;
    /* 0x14 */ u32 _14;
    /* 0x18 */ u32 _18;
    /* 0x1C */ u32 _1C;
    /* 0x20 */ u32 _20;
    /* 0x24 */ u32 _24;
    /* 0x28 */ u32 _28;
    /* 0x2C */ u32 _2C;
    /* 0x30 */ bool _30;
};
