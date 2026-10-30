#include "Game/MapObj/BlackHole.hpp"

#include "Game/LiveActor/LiveActor.hpp"
#include "Game/LiveActor/Nerve.hpp"
#include "Game/Util/ActionSoundUtil.hpp"
#include "Game/Util/ActorAnimUtil.hpp"
#include "Game/Util/ActorCameraUtil.hpp"
#include "Game/Util/ActorInitUtil.hpp"
#include "Game/Util/ActorSensorUtil.hpp"
#include "Game/Util/ActorSwitchUtil.hpp"
#include "Game/Util/CameraUtil.hpp"
#include "Game/Util/DemoUtil.hpp"
#include "Game/Util/EffectUtil.hpp"
#include "Game/Util/JMapUtil.hpp"
#include "Game/Util/LiveActorUtil.hpp"
#include "Game/Util/MathUtil.hpp"
#include "Game/Util/MtxUtil.hpp"
#include "Game/Util/ObjUtil.hpp"
#include "JSystem/JGeometry/TBox.hpp"
#include "JSystem/JGeometry/TVec.hpp"
#include "revolution/types.h"
#include <JSystem/JGeometry/TMatrix.hpp>
#include <math_types.hpp>

namespace NrvBlackHole {
    NEW_NERVE(BlackHoleNrvWait, BlackHole, Wait);
    NEW_NERVE(BlackHoleNrvDemo, BlackHole, Demo);
    NEW_NERVE(BlackHoleNrvDisappear, BlackHole, Disappear);
};  // namespace NrvBlackHole

BlackHole::BlackHole(const char* pName)
    : LiveActor(pName), _90(), _94(gZeroVec), _A0(1.0f), mHitSensorEyeRadius(500.0f), mCubeBox(), mActorCameraInfo() {
    _AC.identity();
    mEffectHostMtx.identity();
}

void BlackHole::init(const JMapInfoIter& rIter) {
    // FIXME
    // decomp.me: https://decomp.me/scratch/A5dvE
    // There seems to be issues with the TVec3f constructor. In particular, when it's first called, it's inlined, even though it shouldn't be.
    // Also, there are discrepancies with the value 500.0f. The target assembly refers to lbl_807DCD94; the current assembly refers to @5155.

    initMapToolInfo(rIter);
    initModel();
    MR::connectToSceneMapObj(this);
    initHitSensor(1);
    MR::addHitSensorEye(this, "Body", 4, mHitSensorEyeRadius, TVec3f(0.0f, 0.0f, 0.0f));
    initEffectKeeper(0, nullptr, false);
    MR::setEffectHostMtx(this, "BlackHoleSuction", mEffectHostMtx);

    f32 clippingRadius = 500.f + MR::max(mHitSensorEyeRadius, 500.f * _A0);
    MR::setClippingTypeSphere(this, clippingRadius);
    MR::setClippingTypeSphere(_90, clippingRadius);
    MR::setClippingFarMax(this);
    MR::setClippingFarMax(_90);
    initSound(4, "BlackHole");

    if (MR::tryRegisterDemoCast(this, rIter)) {
        MR::registerDemoActionNerve(this, GET_NERVE(BlackHole, BlackHoleNrvDisappear), nullptr);
    }

    if (MR::createActorCameraInfoIfExist(rIter, &mActorCameraInfo)) {
        MR::initActorCamera(this, rIter, &mActorCameraInfo);
    }

    initNerve(GET_NERVE(BlackHole, BlackHoleNrvWait));
    MR::useStageSwitchSyncAppear(this, rIter);
    MR::useStageSwitchAwake(this, rIter);
}

void BlackHole::makeActorAppeared() {
    bool switchAValidAndOn = MR::isValidSwitchA(this) && MR::isOnSwitchA(this);

    if (!switchAValidAndOn) {
        LiveActor::makeActorAppeared();
        _90->makeActorAppeared();
    }
}

void BlackHole::makeActorDead() {
    LiveActor::makeActorDead();
    if (!MR::isDead(_90)) {
        _90->makeActorDead();
    }
}

void BlackHole::kill() {
    _90->kill();
    LiveActor::kill();
}

void BlackHole::calcAndSetBaseMtx() {
    // FIXME
    // decomp.me: https://decomp.me/scratch/nH8k8
    // TVec3f.set() is inlined, even though it shouldn't be.
    // Also, there is a discrepancy with the value 0.01f. The target assembly refers to lbl_807DCD98; the current assembly refers to @5309.

    LiveActor::calcAndSetBaseMtx();

    TVec3f dirToCam;
    dirToCam.sub(MR::getCamPos(), mPosition);
    TVec3f camYdir;
    camYdir.set(MR::getCamYdir());

    if (!MR::normalizeOrZero(&dirToCam) && !MR::isSameDirection(dirToCam, camYdir, 0.01f)) {
        MR::makeMtxFrontUpPos(&mEffectHostMtx, dirToCam, camYdir, mPosition);
        mEffectHostMtx.scaleInline(mScale.x);
    }
}

void BlackHole::attackSensor(HitSensor* pSender, HitSensor* pReceiver) {
    if (!isNerve(GET_NERVE(BlackHole, BlackHoleNrvWait))) {
        return;
    }

    if (mCubeBox != nullptr) {
        if (!isInCubeBox(*MR::getSensorPos(pReceiver))) {
            return;
        }
    }

    if (!MR::sendArbitraryMsg(0x81, pReceiver, pSender)) {
        return;
    }

    if (!MR::isSensorPlayer(pReceiver)) {
        return;
    }

    setNerve(GET_NERVE(BlackHole, BlackHoleNrvDemo));
}

bool BlackHole::tryStartDemoCamera() {
    if (mActorCameraInfo != nullptr) {
        MR::startActorCameraTargetSelf(this, mActorCameraInfo, -1);
        return true;
    }
    return false;
}

void BlackHole::initMapToolInfo(const JMapInfoIter& rIter) {
    MR::initDefaultPos(this, rIter);
    MR::initUseStageSwitchReadA(this, rIter);

    if (MR::isEqualObjectName(rIter, "BlackHoleCube")) {
        initCubeBox();
    }

    if (mCubeBox == nullptr) {
        mHitSensorEyeRadius = 500.0f * mScale.x;
    } else {
        TVec3f size(mScale);
        size.scale(500.0f);
        mHitSensorEyeRadius = size.length();
    }

    f32 arg0;
    if (MR::getJMapInfoArg0NoInit(rIter, &arg0)) {
        _A0 = arg0 / 1000.0f;
    } else if (mCubeBox == nullptr) {
        _A0 = mScale.x;
    } else {
        _A0 = 1.0f;
    }
}

void BlackHole::initModel() {
    // FIXME
    // decomp.me: https://decomp.me/scratch/qJWcy
    // Every time a string from .data is referenced in the target assembly, the current assembly references some @ thingy.
    // As a result, nothing from .data ever gets loaded into r31, so r31 is used for this instead.
    // r30 never gets used, which screws up a bunch of stuff at the beginning and end of the function involving the stack.

    MR::initActor(this, "BlackHoleRange", false);
    _90 = MR::createModelObjMapObj("", "BlackHole", getBaseMtx());
    _90->makeActorDead();
    updateModelScale(_A0, _A0);
}

void BlackHole::initCubeBox() {
    MR::makeMtxRotate(_AC, mRotation.x, mRotation.y, mRotation.z);
    _AC.setTrans(mPosition);

    mCubeBox = new TBox3f();
    TVec3f vecStart(0.5f * (1000.0f * -mScale.x), 0.5f * (1000.0f * -mScale.y), 0.5f * (1000.0f * -mScale.z));
    TVec3f vecEnd(0.5f * (1000.0f * mScale.x), 0.5f * (1000.0f * mScale.y), 0.5f * (1000.0f * mScale.z));
    mCubeBox->set(vecStart, vecEnd);
}

bool BlackHole::isInCubeBox(const TVec3f& rVec) const {
    TVec3f pos;
    _AC.multTranspose(rVec, pos);
    return mCubeBox->intersectsPoint(pos);
}

void BlackHole::updateModelScale(f32 num1, f32 num2) {
    mScale.setAll< float >(num1);
    _90->mScale.setAll< float >(0.5f * num2);
}

void BlackHole::exeWait() {
    // FIXME
    // decomp.me: https://decomp.me/scratch/Wzg3j
    // Every time a string from .data is referenced in the target assembly, the current assembly references some @ thingy.
    // This somehow results in the current code accessing the wrong address in .data before calling MR::startActionSound.

    if (MR::isFirstStep(this)) {
        MR::startAction(this, "BlackHoleRange");
        MR::startBtk(this, "BlackHoleRange");
        MR::startBtk(_90, "BlackHole");
    }

    MR::startActionSound(this, "OjLvBlackHole");

    bool shouldKill = MR::isValidSwitchA(this) && MR::isOnSwitchA(this);

    if (shouldKill) {
        kill();
    }
}

void BlackHole::exeDemo() {
    MR::startActionSound(this, "OjLvBlackHole");
}

void BlackHole::exeDisappear() {
    if (MR::isFirstStep(this)) {
        MR::startActionSound(this, "OjLvBlackHoleDisappear");
    }

    f32 easeInValue1 = MR::calcNerveEaseInValue(this, 0x5a, _A0, 0.0f);
    f32 easeInValue2 = MR::calcNerveEaseInValue(this, 0x1e, 0x5a, _A0, 0.0f);
    mScale.setAll< float >(easeInValue1);
    _90->mScale.setAll< float >(0.5f * easeInValue2);

    if (MR::isStep(this, 0x5a)) {
        kill();
    }
}
