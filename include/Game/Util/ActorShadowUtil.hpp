#pragma once

#include <revolution.h>
#include <JGeometry.hpp>

class Color8;
class HitSensor;
class LiveActor;

namespace MR {
    void initShadowFromCSVWithInitShadowVolumeSphere(LiveActor* pActor, const char* pShadowName);
    void initShadowFromCSVWithoutInitShadowVolumeSphere(LiveActor* pActor, const char* pShadowName);
    void initShadowControllerList(LiveActor* pActor, u32 shadowCount);

    void addShadowVolumeOval(LiveActor* pActor, const char* pShadowName, const TVec3f& rSize, MtxPtr pDropPosMtx);
    void addShadowVolumeCylinder(LiveActor* pActor, const char* pShadowName, f32 radius);
    void addShadowVolumeBox(LiveActor* pActor, const char* pShadowName, const TVec3f& rSize);
    void addShadowVolumeBox(LiveActor* pActor, const char* pShadowName, const TVec3f& rSize, MtxPtr pDropPosMtx);
    void addShadowVolumeLine(LiveActor* pActor, const char* pShadowName, LiveActor* pStartActor, const char* pStartShadowName, f32 fromWidth, LiveActor* pEndActor, const char* pEndShadowName, f32 toWidth);
    void addShadowVolumeFlatModel(LiveActor* pActor, const char* pShadowName, const char* pShadowModelName, MtxPtr pDropPosMtx);

    void initShadowSurfaceCircle(LiveActor* pActor, f32 radius);
    void initShadowVolumeSphere(LiveActor* pActor, f32 radius);
    void initShadowVolumeOval(LiveActor* pActor, const TVec3f& rSize);
    void initShadowVolumeCylinder(LiveActor* pActor, f32 radius);
    void initShadowVolumeFlatModel(LiveActor* pActor, const char* pShadowModelName, MtxPtr pDropPosMtx);

    void setShadowDropPositionPtr(LiveActor* pActor, const char* pShadowName, const TVec3f* pDropPos);
    void setShadowDropPositionMtxPtr(LiveActor* pActor, const char* pShadowName, MtxPtr pDropPosMtx, const TVec3f& rOffset);
    void setShadowDropPositionAtJoint(LiveActor* pActor, const char* pShadowName, const char* pJointName, const TVec3f& rOffset);
    void setShadowDropDirectionPtr(LiveActor* pActor, const char* pShadowName, const TVec3f* pDropDir);
    void setShadowDropDirectionPtrAll(LiveActor* pActor, const TVec3f* pDropDir);
    void setShadowProjectionPtr(LiveActor* pActor, const char* pShadowName, const TVec3f* pProjPos, const TVec3f* pProjNormal);
    void setShadowDropPosition(LiveActor* pActor, const char* pShadowName, const TVec3f& rDropPos);
    void setShadowDropDirection(LiveActor* pActor, const char* pShadowName, const TVec3f& rDropDir);
    void setShadowDropLength(LiveActor* pActor, const char* pShadowName, f32 length);
    void setShadowProjection(LiveActor* pActor, const char* pShadowName, const TVec3f& rProjPos, const TVec3f& rProjNormal, bool fix);
    void setShadowSurfaceOvalColor(LiveActor* pActor, const char* pShadowName, Color8 color);
    void setShadowSurfaceOvalAlpha(LiveActor* pActor, const char* pShadowName, u8 alpha);
    void setShadowVolumeSphereRadius(LiveActor* pActor, const char* pShadowName, f32 radius);
    void setShadowVolumeCylinderRadius(LiveActor* pActor, const char* pShadowName, f32 radius);
    void setShadowVolumeBoxSize(LiveActor* pActor, const char* pShadowName, const TVec3f& rSize);
    void setShadowVolumeStartDropOffset(LiveActor* pActor, const char* pShadowName, f32 startDropOffset);
    void setShadowVolumeEndDropOffset(LiveActor* pActor, const char* pShadowName, f32 endDropOffset);

    void onShadowVolumeCutDropLength(LiveActor* pActor, const char* pShadowName);
    void onCalcShadow(LiveActor* pActor, const char* pShadowName);
    void offCalcShadow(LiveActor* pActor, const char* pShadowName);
    void onCalcShadowOneTime(LiveActor* pActor, const char* pShadowName);
    void onCalcShadowAll(LiveActor* pActor);
    void offCalcShadowAll(LiveActor* pActor);
    void onCalcShadowOneTimeAll(LiveActor* pActor);
    void onCalcShadowDropGravity(LiveActor* pActor, const char* pShadowName);
    void onCalcShadowDropGravityOneTime(LiveActor* pActor, const char* pShadowName);
    void onCalcShadowDropPrivateGravity(LiveActor* pActor, const char* pShadowName);
    void onCalcShadowDropPrivateGravityOneTime(LiveActor* pActor, const char* pShadowName);
    void offCalcShadowDropPrivateGravity(LiveActor* pActor, const char* pShadowName);

    void excludeCalcShadowToMyCollision(LiveActor* pActor, const char* pShadowName);
    void excludeCalcShadowToSensorAll(LiveActor* pActor, const HitSensor* pExcludeSensor);
    void excludeCalcShadowToActorAll(LiveActor* pActor, const LiveActor* pExcludeActor);

    bool isExistShadow(const LiveActor* pActor, const char* pShadowName);
    bool isExistShadows(const LiveActor* pActor);

    void invalidateShadow(LiveActor* pActor, const char* pShadowName);
    void validateShadow(LiveActor* pActor, const char* pShadowName);
    void validateShadowGroup(LiveActor* pActor, const char* pShadowName);
    void invalidateShadowAll(LiveActor* pActor);
    void validateShadowAll(LiveActor* pActor);

    void offShadowVisibleSyncHost(LiveActor* pActor, const char* pShadowName);
    void onShadowVisibleSyncHostAll(LiveActor* pActor);
    void offShadowVisibleSyncHostAll(LiveActor* pActor);
    void onShadowFollowHostScale(LiveActor* pActor, const char* pShadowName);
    void onShadowFollowHostScaleAll(LiveActor* pActor);

    void calcClippingRangeIncludeShadow(TVec3f* pClippingPos, f32* pClippingRadius, const LiveActor* pActor, f32 minRadius);
    void setClippingRangeIncludeShadow(LiveActor* pActor, TVec3f* pClippingPos, f32 clippingRadius);

    bool isShadowProjected(const LiveActor* pActor, const char* pShadowName);
    void getShadowProjectionPos(const LiveActor* pActor, const char* pShadowName, TVec3f* pDest);
    void getShadowProjectionNormal(const LiveActor* pActor, const char* pShadowName, TVec3f* pDest);
    f32 getShadowProjectionLength(const LiveActor* pActor, const char* pShadowName);
    HitSensor* getShadowProjectedSensor(const LiveActor* pActor, const char* pShadowName);
    bool isShadowProjectedAny(const LiveActor* pActor);
    f32 getShadowNearProjectionLength(const LiveActor* pActor);
};
