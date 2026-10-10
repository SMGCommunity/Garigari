#include "Game/Ride/TubeSliderDamageObjCreator.hpp"
#include "Game/Ride/TubeSlider.hpp"
#include "Game/Ride/TubeSliderFunction.hpp"

#include "Game/LiveActor/Nerve.hpp"
#include "Game/Util/ActionSoundUtil.hpp"
#include "Game/Util/ActorAnimUtil.hpp"
#include "Game/Util/ActorInitUtil.hpp"
#include "Game/Util/ActorMovementUtil.hpp"
#include "Game/Util/ActorSensorUtil.hpp"
#include "Game/Util/EffectUtil.hpp"
#include "Game/Util/JMapUtil.hpp"
#include "Game/Util/LiveActorUtil.hpp"
#include "Game/Util/MathUtil.hpp"
#include "Game/Util/RailUtil.hpp"
#include "Game/Util/SupportPlayUtil.hpp"

namespace {
    ALWAYS_INLINE inline TubeSliderDamageObj* createDamageObj(TubeSlider* pSlider, s32 type, f32 edgeOffset, TVec3f& vec) {
        TubeSliderDamageObj* obj = new TubeSliderDamageObj(type, -MR::getRailDirection(pSlider));  // Negate operator needs to be inlined, but isn't
        if (type == 1)
            edgeOffset += 50.0f;
        TubeSliderFunction::getUnknown1(&obj->mPosition, pSlider, vec, -edgeOffset);
        obj->mGravity.x = vec.x;
        obj->mGravity.y = vec.y;
        obj->mGravity.z = vec.z;
        return obj;
    }
}  // namespace

namespace NrvTubeSliderDamageObj {
    NEW_NERVE(TubeSliderDamageObjNrvWait, TubeSliderDamageObj, Wait);
    NEW_NERVE(TubeSliderDamageObjNrvShake, TubeSliderDamageObj, Shake);
    NEW_NERVE(TubeSliderDamageObjNrvSupportFreeze, TubeSliderDamageObj, SupportFreeze);
}  // namespace NrvTubeSliderDamageObj

TubeSliderDamageObj::TubeSliderDamageObj(s32 t, const TVec3f& vec) : LiveActor("ダメージオブジェ（チューブスライダー用）"), mType(t), _94(vec) {
    _A0 = false;
    _A4 = 0.0f;
}

void TubeSliderDamageObj::init(const JMapInfoIter& rIter) {
    if (mType == 0) {
        MR::initActor(this, rIter, "TubeSliderDamageObj", false);
    } else {
        MR::initActor(this, rIter, "TubeSliderFire", false);
    }
    initNerve(GET_NERVE(TubeSliderDamageObj, TubeSliderDamageObjNrvWait));
    MR::addEffect(this, "PointerTouch");
    makeActorAppeared();
}

void TubeSliderDamageObj::exeWait() {
    if (MR::isFirstStep(this)) {
        MR::validateClipping(this);
        MR::startAction(this, "Wait");
    }
    if (MR::attachSupportTicoToTarget(this)) {
        MR::invalidateClipping(this);
        setNerve(GET_NERVE(TubeSliderDamageObj, TubeSliderDamageObjNrvSupportFreeze));
    }
}

void TubeSliderDamageObj::exeShake() {
    if (MR::isFirstStep(this)) {
        MR::startAction(this, "Shake");
    }
    if (MR::isActionEnd(this)) {
        setNerve(GET_NERVE(TubeSliderDamageObj, TubeSliderDamageObjNrvWait));
        return;
    }
    if (MR::isGreaterStep(this, 30) && MR::attachSupportTicoToTarget(this)) {
        MR::invalidateClipping(this);
        setNerve(GET_NERVE(TubeSliderDamageObj, TubeSliderDamageObjNrvSupportFreeze));
    }
}

void TubeSliderDamageObj::exeSupportFreeze() {
    if (MR::isFirstStep(this)) {
        MR::startAction(this, "SupportFreeze");
        MR::emitEffect(this, "PointerTouch");
    }
    if (!MR::attachSupportTicoToTarget(this)) {
        MR::deleteEffect(this, "PointerTouch");
        setNerve(GET_NERVE(TubeSliderDamageObj, TubeSliderDamageObjNrvShake));
    }
}

void TubeSliderDamageObj::calcAndSetBaseMtx() {
    MR::calcAndSetBaseTRMtxFromGravityAndZAxis(this, _94);
}

void TubeSliderDamageObj::attackSensor(HitSensor* pSender, HitSensor* pReceiver) {
    if (MR::isSensorRide(pReceiver) && !isNerve(GET_NERVE(TubeSliderDamageObj, TubeSliderDamageObjNrvSupportFreeze))) {
        MR::sendMsgEnemyAttack(pReceiver, pSender);
        if (isNerve(GET_NERVE(TubeSliderDamageObj, TubeSliderDamageObjNrvWait)))
            setNerve(GET_NERVE(TubeSliderDamageObj, TubeSliderDamageObjNrvShake));
    }
}

bool TubeSliderDamageObj::receiveMsgPlayerAttack(u32 msg, HitSensor* pSender, HitSensor* pReceiver) {
    if (MR::isMsgStarPieceReflect(msg) && !isNerve(GET_NERVE(TubeSliderDamageObj, TubeSliderDamageObjNrvSupportFreeze))) {
        setNerve(GET_NERVE(TubeSliderDamageObj, TubeSliderDamageObjNrvShake));
        return true;
    }
    return false;
}

void TubeSliderDamageObj::control() {
    // TODO: All of this :(

    // MR::getMicDistance???
    MR::startActionSound(this, "MarioPassLv", -1, -1, -1);  // incorrect statement. only here to make the string spawn in
}

TubeSliderDamageObjCreator::TubeSliderDamageObjCreator(TubeSlider* pSlider) : LiveActor("ダメージオブジェ生成（チューブスライダー用）") {
    mSlider = pSlider;
}

void TubeSliderDamageObjCreator::init(const JMapInfoIter& rIter) {
    MR::initDefaultPos(this, rIter);
    MR::moveCoordToNearestPos(mSlider, mPosition);

    s32 type = 0;
    MR::getJMapInfoArg0NoInit(rIter, &type);
    if (type < 0 || type >= 2)
        type = 0;

    s32 width = 1;
    s32 length = 1;
    MR::getJMapInfoArg1NoInit(rIter, &width);
    MR::getJMapInfoArg2NoInit(rIter, &length);

    f32 edgeOffset = 0.0f;
    MR::getJMapInfoArg3NoInit(rIter, &edgeOffset);

    f32 rowDistance = 500.0f;
    MR::getJMapInfoArg4NoInit(rIter, &rowDistance);

    f32 startingAngle = -1.0f;
    f32 validDegrees = 0.0f;
    f32 twistDegrees = 0.0f;
    MR::getJMapInfoArg5NoInit(rIter, &startingAngle);
    MR::getJMapInfoArg6NoInit(rIter, &validDegrees);
    MR::getJMapInfoArg7NoInit(rIter, &twistDegrees);

    TVec3f vec;
    for (s32 i = 0; i < length; i++) {
        TubeSliderFunction::updateTubeSliderInfo(mSlider, true);
        vec.x = 0.0f;
        vec.y = 1.0f;
        vec.z = 0.0f;
        f32 f26 = 0.0f;
        if (length > 1) {
            f26 = static_cast< f32 >(i) / static_cast< f32 >(length - 1);
        }
        for (s32 j = 0; j < width; j++) {
            if (startingAngle != -1.0f || validDegrees != 0 || twistDegrees != 0) {
                if (startingAngle == -1.0f)
                    startingAngle = TubeSliderFunction::getFloorAngle(mSlider);
                f32 f0 = 0.0f;
                if (width > 1) {
                    f0 = static_cast< f32 >(j) / static_cast< f32 >(width - 1);
                }
                f32 f3 = f0 - 0.5f;
                TubeSliderFunction::calcTubeVecDegree(startingAngle + (validDegrees * f3) + (twistDegrees * f26), &vec, mSlider);
            } else {
                f32 a = TubeSliderFunction::getFloorAngle(mSlider);
                TubeSliderFunction::calcTubeVecDegree(a, &vec, mSlider);
            }

            TubeSliderDamageObj* current = createDamageObj(mSlider, type, edgeOffset, vec);
            MR::setClippingFar300m(current);
            MR::setScale(current, mScale);
            current->initWithoutIter();
        }
        MR::moveCoord(mSlider, rowDistance);
    }
    makeActorDead();
}
