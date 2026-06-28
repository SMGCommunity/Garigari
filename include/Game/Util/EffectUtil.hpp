#pragma once

#include <revolution.h>
#include <JGeometry.hpp>

class HitSensor;
class LayoutActor;
class LiveActor;
class MultiEmitterCallBackBase;
class MultiEmitterParticleCallBack;
class Triangle;

/* FINISHED */

namespace MR {
	bool isExistEffect(const LiveActor* pActor, const char* pEffectName);

	void requestEffectStopSceneStartAndDelete();
	void requestEffectStopSceneStart();
	void requestEffectStopSceneEnd();

	void addEffect(LiveActor* pActor, const char* pEffectName);
	void getEffect(const LiveActor* pActor, const char* pEffectName);
	void* getEffect(const LayoutActor* pLayout, const char* pEffectName);
	bool isExistEffectKeeper(const LiveActor* pActor);
	bool isExistEffectKeeper(const LayoutActor* pLayout);

	void emitEffect(LiveActor* pActor, const char* pEffectName);
	void emitEffectWithScale(LiveActor* pActor, const char* pEffectName, f32 scale, s32 emitterIndex);
	void emitEffectWithEmitterCallBack(LiveActor* pActor, const char* pEffectName, MultiEmitterCallBackBase* mEmitterCallBack);
	void emitEffectWithParticleCallBack(LiveActor* pActor, const char* pEffectName, MultiEmitterParticleCallBack* mParticleCallBack);
	bool tryEmitEffect(LiveActor* pActor, const char* pEffectName);

	bool tryDeleteEffect(LiveActor* pActor, const char* pEffectName);
	bool tryForceDeleteEffect(LiveActor* pActor, const char* pEffectName);
	bool tryDeleteEffectAll(LiveActor* pActor);
	bool tryForceDeleteEffectAll(LiveActor* pActor);
	void deleteEffect(LiveActor* pActor, const char* pEffectName);
	void forceDeleteEffect(LiveActor* pActor, const char* pEffectName);
	void deleteEffectAll(LiveActor* pActor);
	void forceDeleteEffectAll(LiveActor* pActor);

	bool isRegisteredEffect(const LiveActor* pActor, const char* pEffectName);
	bool isEffectValid(const LiveActor* pActor, const char* pEffectName);

	void onDrawEffect(LiveActor* pActor);
	void offDrawEffect(LiveActor* pActor);
	void onCalcEmitter(LiveActor* pActor);
	void offCalcEmitter(LiveActor* pActor);
	void pauseOffEffectAll(LiveActor* pActor);

	void setAllEffectDrawOrder(LiveActor* pActor, s32 drawOrder);

	void onEmitEffectSyncClipping(LiveActor* pActor, const char* pEffectName);
	void onForceDeleteEffectSyncClipping(LiveActor* pActor, const char* pEffectName);

	void setEffectName(LiveActor* pActor, const char* pOldEffectName, const char* pNewEffectName);
	void setEffectHostSRT(LiveActor* pActor, const char* pEffectName, const TVec3f* pTranslation, const TVec3f* pRotation, const TVec3f* pScale);
	void setEffectHostMtx(LiveActor* pActor, const char* pEffectName, MtxPtr pMtx);
	void setAllEffectHostMtx(LiveActor* pActor, MtxPtr pMtx);
	void setEffectBaseScale(LiveActor* pActor, const char* pEffectName, f32 baseScale);
	void setEffectColor(LiveActor* pActor, const char* pEffectName, u8 prmR, u8 prmG, u8 prmB, u8 envR, u8 envG, u8 envB);
	void setEffectPrmColor(LiveActor* pActor, const char* pEffectName, u8 r, u8 g, u8 b);
	void setEffectEnvColor(LiveActor* pActor, const char* pEffectName, u8 r, u8 g, u8 b);
	void setEffectLocalScale(LiveActor* pActor, const char* pEffectName, const TVec3f& rLocalScale);
	void addEffectHitNormal(LiveActor* pActor, const char* pEffectName);

	void emitEffectHit(LiveActor* pActor, const TVec3f& rPosition, const char* pEffectName);
	void emitEffectHit(LiveActor* pActor, const TVec3f& rPosition, const TVec3f& rUpVec, const char* pEffectName);
	void emitEffectHit(LiveActor* pActor, MtxPtr, const char* pEffectName);
	void emitEffectHitBetweenSensors(LiveActor* pActor, const HitSensor* pSensorA, const HitSensor* pSensorB, f32 offset, const char* pEffectName);

	void initEffectAfterPlacement(LiveActor* pActor, MtxPtr pMtx);
	void updateEffectFloorCode(LiveActor* pActor, const Triangle* pTriangle);
	void updateEffectFloorCodeLineToMap(LiveActor* pActor, const TVec3f& pStart, const TVec3f& pEnd);
	void updateEffectFloorCodeLineToMap(LiveActor* pActor, f32 pStart, f32 pEnd);
};
