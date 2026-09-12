#pragma once

#include <revolution.h>
#include <JGeometry.hpp>

class LiveActor;
class TubeSlider;
class JMapInfoIter;

namespace TubeSliderFunction {
	void initChildObjs(TubeSlider* pSlider, const JMapInfoIter& rIter);
	void initDefaultPosOnTube(LiveActor* pActor, const JMapInfoIter& rIter, f32*, f32*, TVec3f*, f32, TubeSlider* pSlider);
	f32 interpolateBetweenPoints(const TubeSlider* pSlider, f32 A, f32 B);
	void updateTubeSliderInfo(TubeSlider* pSlider, bool);
	void getRailUpVec(TVec3f* pDest, const TubeSlider* pSlider);
	void calcTubeVecDegree(f32 degree, TVec3f* pDest, const TubeSlider* pSlider);
	NO_INLINE void getUnknown1(TVec3f* pOut, const TubeSlider* pSlider, const TVec3f& vec, f32 a);
	f32 getRadiusAtRailCoord(f32 coord, TubeSlider* pSlider);
	f32 getRadius(const TubeSlider* pSlider);
	f32 getFloorAngle(const TubeSlider* pSlider);
	bool isUnknown1(f32, f32, f32);
	bool isUnknown2(const TubeSlider* pSlider);
	bool isUnknown3(f32*, bool, f32, f32, f32);
	bool isHitWall(const TubeSlider*, f32*, bool);
	bool isHitLeftWall(const TubeSlider*, f32*);
	bool isHitRightWall(const TubeSlider*, f32*);
	NO_INLINE bool isSameGroundType(s32, s32);
	bool isGroundType(TubeSlider* pSlider, s32 groundType);
	bool isGroundWood(TubeSlider* pSlider);   // 6
	bool isGroundNormal(TubeSlider* pSlider); // 0
	bool isGroundDamage(TubeSlider* pSlider); // 3
	bool isGroundSlow(TubeSlider* pSlider);   // 2
	bool isGroundNormal2(TubeSlider* pSlider);// 4
	bool isGroundIce(TubeSlider* pSlider);    // 1
	void unknown(LiveActor* pActor, TVec3f* vec, TubeSlider* pSlider, f32 railcoord, f32 rotate, f32 u);
}