#pragma once

#include "revolution/mtx.h"
#include <JSystem/JGeometry/TVec.hpp>
#include <revolution.h>

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
};
