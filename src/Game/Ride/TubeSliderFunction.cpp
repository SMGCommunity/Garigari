#include "Ride/TubeSliderFunction.hpp"
#include "Ride/TubeSlider.hpp"
#include "Ride/TubeSliderCoinCreator.hpp"
#include "Util/ActorInitUtil.hpp"
#include "Util/JMapUtil.hpp"
#include "Util/MathUtil.hpp"
#include "Util/RailUtil.hpp"
#include "Util/SceneUtil.hpp"
#include "Util/StringUtil.hpp"

namespace TubeSliderFunction {
	// TODO: Needs class definitions
	void initChildObjs(TubeSlider* pSlider, const JMapInfoIter& rIter) {
		s32 childNum = MR::getChildObjNum(rIter);
		for (s32 i = 0; i < childNum; i++) {
			const char* pName = nullptr;
			MR::getChildObjName(&pName, rIter, i);

			if (MR::isEqualString(pName, "TubeSliderCoinCreator")) {
				MR::initChildObj(new TubeSliderCoinCreator(pSlider, false), rIter, i);
				continue;
			}
			else if (MR::isEqualString(pName, "TubeSliderCoinCreatorPurple")) {
				MR::initChildObj(new TubeSliderCoinCreator(pSlider, true), rIter, i);
				continue;
			}
			else if (MR::isEqualString(pName, "TubeSliderDamageObj")) {
				continue;
			}
			else if (MR::isEqualString(pName, "TubeSliderEnemy")) {
				continue;
			}
			else if (MR::isEqualString(pName, "TubeSliderHana")) {
				continue;
			}
			else {
				// TubeSliderObjCreator
			}
		}
	}
	void initDefaultPosOnTube(LiveActor* pActor, const JMapInfoIter& rIter, f32* railcoord, f32* floorangle, TVec3f* vec, f32 flt, TubeSlider* pSlider) {
		MR::initDefaultPos(pActor, rIter);
		MR::moveCoordToNearestPos(pSlider, pActor->mPosition);
		updateTubeSliderInfo(pSlider, true);
		*railcoord = MR::getRailCoord(pSlider);
		MR::getJMapInfoArg5NoInit(rIter, floorangle);
		if (*floorangle == -1.0f) {
			*floorangle = getFloorAngle(pSlider);
		}
		*floorangle = MR::repeat(*floorangle, 0.0f, 360.0f);
		unknown(pActor, vec, pSlider, *railcoord, *floorangle, flt);
	}
	f32 interpolateBetweenPoints(const TubeSlider* pSlider, f32 A, f32 B) {
		f32 nextPointDist;
		f32 currentPointDist;
		currentPointDist = 0.0f;
		nextPointDist = 0.0f;
		MR::calcDistanceToCurrentAndNextRailPoint(pSlider, &currentPointDist, &nextPointDist);

		f32 f0 = nextPointDist;
		f32 f3 = 1.0f;
		if (currentPointDist + nextPointDist < 1.0f) {
			f0 = 0.0f;
		}
		else {
			f3 = currentPointDist / (currentPointDist + nextPointDist);
			f0 = nextPointDist / (currentPointDist + nextPointDist);
		}
		return (A * f0) + (B * f3);
	}
	void updateTubeSliderInfo(TubeSlider* pSlider, bool doFullUpdate) {
		f32 nextArg0, currentArg0;
		currentArg0 = pSlider->mRadiusDefault;
		nextArg0 = pSlider->mRadiusDefault;
		MR::getCurrentRailPointArg0NoInit(pSlider, &currentArg0);
		MR::getNextRailPointArg0NoInit(pSlider, &nextArg0);
		pSlider->mInfo.mRadius = interpolateBetweenPoints(pSlider, currentArg0, nextArg0);

		if (doFullUpdate) {
			s32 currentArg1 = pSlider->mFloorCodeDefault;
			MR::getCurrentRailPointArg1NoInit(pSlider, &currentArg1);
			pSlider->mInfo.mPrimaryFloorType = currentArg1;

			f32 nextArg2;
			f32 currentArg2 = 0.0f;
			MR::getCurrentRailPointArg2NoInit(pSlider, &currentArg2);
			bool interpolate = false;
			MR::getCurrentRailPointArg4NoInit(pSlider, &interpolate);
			f32 primaryangle;
			if (!interpolate) {
				primaryangle = currentArg2;
			}
			else {
				nextArg2 = currentArg2;
				MR::getNextRailPointArg2NoInit(pSlider, &nextArg2);
				primaryangle = interpolateBetweenPoints(pSlider, currentArg2, nextArg2);
			}
			pSlider->mInfo.mPrimaryFloorAngle = primaryangle;

			f32 nextArg3;
			f32 currentArg3 = 0.0f;
			MR::getCurrentRailPointArg3NoInit(pSlider, &currentArg3);
			bool interpolate2 = false;
			MR::getCurrentRailPointArg4NoInit(pSlider, &interpolate2);
			f32 primarywidth;
			if (!interpolate2) {
				primarywidth = currentArg3;
			}
			else {
				nextArg3 = currentArg3;
				MR::getNextRailPointArg3NoInit(pSlider, &nextArg3);
				primarywidth = interpolateBetweenPoints(pSlider, currentArg3, nextArg3);
			}
			pSlider->mInfo.mPrimaryFloorWidth = primarywidth;

			s32 currentArg5 = -1;
			MR::getCurrentRailPointArg5NoInit(pSlider, &currentArg5);
			pSlider->mInfo.mSecondaryFloorType = currentArg5;

			f32 nextArg6;
			f32 currentArg6 = 0.0f;
			MR::getCurrentRailPointArg6NoInit(pSlider, &currentArg6);
			bool interpolate3 = false;
			MR::getCurrentRailPointArg4NoInit(pSlider, &interpolate3);
			f32 secondaryangle;
			if (!interpolate3) {
				secondaryangle = currentArg6;
			}
			else {
				nextArg6 = currentArg6;
				MR::getNextRailPointArg6NoInit(pSlider, &nextArg6);
				secondaryangle = interpolateBetweenPoints(pSlider, currentArg6, nextArg6);
			}
			pSlider->mInfo.mSecondaryFloorAngle = secondaryangle;

			f32 nextArg7;
			f32 currentArg7 = 0.0f;
			MR::getCurrentRailPointArg7NoInit(pSlider, &currentArg7);
			bool interpolate4 = false;
			MR::getCurrentRailPointArg4NoInit(pSlider, &interpolate4);
			f32 secondarywidth;
			if (!interpolate4) {
				secondarywidth = currentArg7;
			}
			else {
				nextArg7 = currentArg7;
				MR::getNextRailPointArg7NoInit(pSlider, &nextArg7);
				secondarywidth = interpolateBetweenPoints(pSlider, currentArg7, nextArg7);
			}
			pSlider->mInfo.mSecondaryFloorWidth = secondarywidth;
		}
	}
	void getRailUpVec(TVec3f* pDest, const TubeSlider* pSlider) {
		TVec3f min(0.0f, -1.0f, 0.0f);
		
		TVec3f out;
		TVec3f neg = -min;
		const TVec3f& raildir = MR::getRailDirection(pSlider);
		PSVECCrossProduct(raildir, neg, &out);
		MR::normalize(&out);
		PSVECCrossProduct(out, MR::getRailDirection(pSlider), pDest);
		MR::normalize(pDest);
	}
	void calcTubeVecDegree(f32 degree, TVec3f* pDest, const TubeSlider* pSlider) {
		getRailUpVec(pDest, pSlider);
		MR::rotateVecDegree(pDest, -MR::getRailDirection(pSlider), degree);
	}
	void getUnknown1(TVec3f* pOut, const TubeSlider* pSlider, const TVec3f& vec, f32 a) {
		pOut->set(vec);
		pOut->scale(a + pSlider->mInfo.getRadius());
		pOut->add(MR::getRailPos(pSlider));
	}
	f32 getRadiusAtRailCoord(f32 coord, TubeSlider* pSlider) {
		f32 railCoord = MR::getRailCoord(pSlider);
		MR::setRailCoord(pSlider, coord);
		updateTubeSliderInfo(pSlider, true);
		f32 radius = pSlider->mInfo.getRadius();
		MR::setRailCoord(pSlider, railCoord);
		updateTubeSliderInfo(pSlider, true);
		return radius;
	}
	f32 getRadius(const TubeSlider* pSlider) {
		return pSlider->mInfo.getRadius();
	}
	f32 getFloorAngle(const TubeSlider* pSlider) {
		if (pSlider->mInfo.mPrimaryFloorWidth <= 0 && pSlider->mInfo.mSecondaryFloorWidth > 0)
			return pSlider->mInfo.mSecondaryFloorAngle;
		f32 angle = pSlider->mInfo.mPrimaryFloorAngle;
		return MR::repeat(180.0f + angle, 0.0f, 360.0f);
	}
	bool isUnknown1(f32 a, f32 b, f32 c) {
		if (c <= 0.0f)
			return false;

		f32 vA = b - (c / 2);
		f32 vB = b + (c / 2);

		if (vA <= a && a <= vB)
			return true;

		if (vA <= a - 360.0f && a - 360.0f <= vB)
			return true;

		if (vA <= 360.0f + a && 360.0f + a <= vB)
			return true;

		return false;
	}
	bool isUnknown2(const TubeSlider* pSlider) {
		const f32 range = 5.0f;
		if (!((isUnknown1(pSlider->getPlayerTheta(), pSlider->mInfo.mPrimaryFloorAngle, pSlider->mInfo.mPrimaryFloorWidth))
			&& (isUnknown1(pSlider->getPlayerTheta() - range, pSlider->mInfo.mPrimaryFloorAngle, pSlider->mInfo.mPrimaryFloorWidth))
			&& (isUnknown1(pSlider->getPlayerTheta() + range, pSlider->mInfo.mPrimaryFloorAngle, pSlider->mInfo.mPrimaryFloorWidth))))
			return false;
		return true;
	}
	bool isUnknown3(f32* f, bool side, f32 a, f32 b, f32 c) {
		if (b <= a && a <= c) {
			f32 L = __fabsf(b - a);
			f32 R = __fabsf(c - a);
			if (15.0f < L && 15.0f < R)
				return false;
			bool asdsad = L > R;
			if (side && asdsad) {
				*f = c;
				return true;
			}
			if (!side && !asdsad) {
				*f = b;
				return true;
			}
		}
		return false;
	}
	bool isHitWall(const TubeSlider* pSlider, f32* f, bool checkLeft) {
		const TubeSliderInfo& pInfo = pSlider->mInfo;
		if (pInfo.mPrimaryFloorWidth <= 0.0f || !pInfo.hasWall(checkLeft)) {
			return false;
		}
		f32 f31 = pInfo.mPrimaryFloorAngle - (pInfo.mPrimaryFloorWidth / 2);
		f32 f30 = pInfo.mPrimaryFloorAngle + (pInfo.mPrimaryFloorWidth / 2);
		if (isUnknown3(f, checkLeft, *f, f31, f30) || isUnknown3(f, checkLeft, *f - 360.0f, f31, f30) || isUnknown3(f, checkLeft, *f + 360.0f, f31, f30))
			return true;
		return false;
	}
	bool isHitLeftWall(const TubeSlider* pSlider, f32* f) {
		return isHitWall(pSlider, f, true);
	}
	bool isHitRightWall(const TubeSlider* pSlider, f32* f) {
		return isHitWall(pSlider, f, false);
	}
	bool isSameGroundType(s32 A, s32 B) {
		return A == B;
	}
	bool isGroundType(TubeSlider* pSlider, s32 type) {
		if (!isSameGroundType(pSlider->mInfo.mPrimaryFloorType, type) && !isSameGroundType(pSlider->mInfo.mSecondaryFloorType, type))
			return false;

		bool b = TubeSliderFunction::isUnknown1(pSlider->mPlayerTheta, pSlider->mInfo.mSecondaryFloorAngle, pSlider->mInfo.mSecondaryFloorWidth);
		if ((b && isSameGroundType(pSlider->mInfo.mSecondaryFloorType, type)) || (!b && isSameGroundType(pSlider->mInfo.mPrimaryFloorType, type)))
			return true;
		return false;
	}
	bool isGroundWood(TubeSlider* pSlider) {
		return isGroundType(pSlider, 6);
	}
	bool isGroundNormal(TubeSlider* pSlider) {
		return isGroundType(pSlider, 0);
	}
	bool isGroundDamage(TubeSlider* pSlider) {
		return isGroundType(pSlider, 3);
	}
	bool isGroundSlow(TubeSlider* pSlider) {
		return isGroundType(pSlider, 2);
	}
	bool isGroundNormal2(TubeSlider* pSlider) {
		return isGroundType(pSlider, 4);
	}
	bool isGroundIce(TubeSlider* pSlider) {
		return isGroundType(pSlider, 1);
	}
	void unknown(LiveActor* pActor, TVec3f* vec, TubeSlider* pSlider, f32 railcoord, f32 rotate, f32 u) {
		f32 OriginalRailCoord = MR::getRailCoord(pSlider);
		MR::setRailCoord(pSlider, railcoord);
		updateTubeSliderInfo(pSlider, true);
		TVec3f railUpVec(0.0f, 1.0f, 0.0f);
		getRailUpVec(&railUpVec, pSlider);
		MR::rotateVecDegree(&railUpVec, -MR::getRailDirection(pSlider), rotate);
		getUnknown1(&pActor->mPosition, pSlider, railUpVec, u);
		pActor->mGravity.set(railUpVec);
		vec->set(MR::getRailDirection(pSlider));
		MR::setRailCoord(pSlider, OriginalRailCoord);
		updateTubeSliderInfo(pSlider, true);
	}
}