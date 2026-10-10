#include "Game/Ride/TubeSliderCoinCreator.hpp"

#include "Game/Ride/TubeSlider.hpp"
#include "Game/Ride/TubeSliderFunction.hpp"

#include "Game/MapObj/Coin.hpp"

#include "Game/Util/ActorInitUtil.hpp"
#include "Game/Util/JMapUtil.hpp"
#include "Game/Util/LiveActorUtil.hpp"
#include "Game/Util/MathUtil.hpp"
#include "Game/Util/RailUtil.hpp"

namespace {
    // Definitely exists because of the register usage
    ALWAYS_INLINE inline void createCoin(bool isPurple, TubeSlider* pSlider, f32 edgeOffset, TVec3f& vec) {
        Coin* obj =
            isPurple ? MR::createDirectSetPurpleCoin("コイン（チューブスライダー用）") : MR::createDirectSetCoin("コイン（チューブスライダー用）");
        TubeSliderFunction::getUnknown1(&obj->mPosition, pSlider, vec, -edgeOffset);
        obj->setShadowCylinder();
        obj->initWithoutIter();
        MR::setClippingFar300m(obj);
        obj->makeActorAppeared();
        obj->mGravity.x = vec.x;
        obj->mGravity.y = vec.y;
        obj->mGravity.z = vec.z;
    }
}  // namespace

TubeSliderCoinCreator::TubeSliderCoinCreator(TubeSlider* pSlider, bool isPurple) : LiveActor("コイン生成（チューブスライダー）") {
    mIsPurpleCoin = isPurple;
    mSlider = pSlider;
}

void TubeSliderCoinCreator::init(const JMapInfoIter& rIter) {
    MR::initDefaultPos(this, rIter);
    MR::moveCoordToNearestPos(mSlider, mPosition);
    s32 coinNum = 1;
    MR::getJMapInfoArg0NoInit(rIter, &coinNum);
    f32 edgeOffset = 0.0f;
    MR::getJMapInfoArg1NoInit(rIter, &edgeOffset);
    f32 coinSpacing = 500.0f;
    MR::getJMapInfoArg2NoInit(rIter, &coinSpacing);
    f32 startingAngle = -1.0f;
    f32 twistOrSine = 0.0f;
    MR::getJMapInfoArg3NoInit(rIter, &startingAngle);
    MR::getJMapInfoArg4NoInit(rIter, &twistOrSine);
    f32 enableSineWave = 0.0f;
    f32 sinePhaseShift = 0.0f;
    f32 sineCycleDegrees = 360.0f;
    MR::getJMapInfoArg5NoInit(rIter, &enableSineWave);
    MR::getJMapInfoArg6NoInit(rIter, &sinePhaseShift);
    MR::getJMapInfoArg7NoInit(rIter, &sineCycleDegrees);

    for (s32 i = 0; i < coinNum; i++) {
        TubeSliderFunction::updateTubeSliderInfo(mSlider, true);
        TVec3f vec;
        vec.x = 0.0f;
        vec.y = 1.0f;
        vec.z = 0.0f;
        if (startingAngle != -1.0f || twistOrSine != 0.0f) {
            f32 sangle = startingAngle;
            if (sangle == -1.0f)
                sangle = TubeSliderFunction::getFloorAngle(mSlider);
            f32 f3 = 0.0f;
            if (coinNum > 1) {
                f3 = static_cast< f32 >(i) / static_cast< f32 >(coinNum - 1);
            }
            f32 twangle = twistOrSine * f3;
            if (enableSineWave == 1.0f) {
                twangle = twistOrSine * MR::sinDegree(sinePhaseShift + (f3 * sineCycleDegrees));
            }
            TubeSliderFunction::calcTubeVecDegree(sangle + twangle, &vec, mSlider);
        } else {
            f32 a = TubeSliderFunction::getFloorAngle(mSlider);
            TubeSliderFunction::calcTubeVecDegree(a, &vec, mSlider);
        }

        createCoin(mIsPurpleCoin, mSlider, edgeOffset, vec);
        MR::moveCoord(mSlider, coinSpacing);
    }

    makeActorDead();
}
