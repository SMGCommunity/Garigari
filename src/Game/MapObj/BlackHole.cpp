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
    : LiveActor(pName), mBlackHoleModel(), _94(gZeroVec), mModelScale(1.0f), mRadius(500.0f), mCubeBox(), mActorCameraInfo() {
    _AC.identity();
    mEffectHostMtx.identity();
}

void BlackHole::init(const JMapInfoIter& rIter) {
    // FIXME
    // decomp.me: https://decomp.me/scratch/boJyM
    // For whatever reason, it matches more in objdiff (99.90%) than in decomp.me (99.76%).
    // For some reason, decomp.me compiles my code differently, resulting in r5 pointing to the wrong stack address before LiveActor::initSound is
    // called. In objdiff, the only issue is that there are discrepancies with the value 500.0f. The target assembly refers to lbl_807DCD94; the
    // current assembly refers to @5851.

    initMapToolInfo(rIter);
    initModel();
    MR::connectToSceneMapObj(this);
    initHitSensor(1);
    MR::addHitSensorEye(this, "Body", 16, mRadius, TVec3f(0.0f, 0.0f, 0.0f));
    initEffectKeeper(0, nullptr, false);
    MR::setEffectHostMtx(this, "BlackHoleSuction", mEffectHostMtx);

    f32 clippingRadius = 500.0f + MR::max(mRadius, 500.0f * mModelScale);
    MR::setClippingTypeSphere(this, clippingRadius);
    MR::setClippingTypeSphere(mBlackHoleModel, clippingRadius);
    MR::setClippingFarMax(this);
    MR::setClippingFarMax(mBlackHoleModel);

    TVec3f a4;
    a4.setAll< f32 >(0.0f);
    initSound(4, "BlackHole", nullptr, a4);

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
    if (!isSwitchAValidAndOn()) {
        LiveActor::makeActorAppeared();
        mBlackHoleModel->makeActorAppeared();
    }
}

void BlackHole::makeActorDead() {
    LiveActor::makeActorDead();
    if (!MR::isDead(mBlackHoleModel)) {
        mBlackHoleModel->makeActorDead();
    }
}

void BlackHole::kill() {
    mBlackHoleModel->kill();
    LiveActor::kill();
}

void BlackHole::calcAndSetBaseMtx() {
    LiveActor::calcAndSetBaseMtx();

    TVec3f dirToCam;
    dirToCam.sub(MR::getCamPos(), mPosition);
    TVec3f camYdir;
    camYdir.set(MR::getCamYdir());

    if (!MR::normalizeOrZero(&dirToCam) && !MR::isSameDirection(dirToCam, camYdir)) {
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

    if (!MR::sendArbitraryMsg(ACTMES_INHALE_BLACK_HOLE, pReceiver, pSender)) {
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
        mRadius = 500.0f * mScale.x;
    } else {
        TVec3f size = mScale;
        size.scale(500.0f);
        mRadius = size.length();
    }

    f32 arg0;
    if (MR::getJMapInfoArg0NoInit(rIter, &arg0)) {
        mModelScale = arg0 / 1000.0f;
    } else if (mCubeBox == nullptr) {
        mModelScale = mScale.x;
    } else {
        mModelScale = 1.0f;
    }
}

void BlackHole::initModel() {
    // FIXME
    // decomp.me: https://decomp.me/scratch/vilNU
    // The target assembly uses r31 to store a pointer to address 8069c5a0 in .data. Then, each time it references a string like "BlackHoleRange", it
    // adds some number to 8069c5a0 and stores the sum in a register. By contrast, the current assembly directly loads the strings into the registers.
    // It never uses r31, so the entire code is screwed up.

    MR::initActor(this, "BlackHoleRange", false);
    mBlackHoleModel = MR::createModelObjMapObj("", "BlackHole", getBaseMtx());
    mBlackHoleModel->makeActorDead();
    updateModelScale(mModelScale, mModelScale);
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
    mScale.setAll< f32 >(num1);
    mBlackHoleModel->mScale.setAll< f32 >(0.5f * num2);
}

void BlackHole::exeWait() {
    // FIXME
    // decomp.me: https://decomp.me/scratch/Wzg3j
    // Every time a string from .data is referenced in the target assembly, the current assembly references some @ thingy.
    // This somehow results in the current code accessing the wrong address in .data before calling MR::startActionSound.

    if (MR::isFirstStep(this)) {
        MR::startAction(this, "BlackHoleRange");
        MR::startBtk(this, "BlackHoleRange");
        MR::startBtk(mBlackHoleModel, "BlackHole");
    }

    MR::startActionSound(this, "OjLvBlackHole");

    if (isSwitchAValidAndOn()) {
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

    f32 easeInValue1 = MR::calcNerveEaseInValue(this, 90, mModelScale, 0.0f);
    f32 easeInValue2 = MR::calcNerveEaseInValue(this, 30, 90, mModelScale, 0.0f);
    mScale.setAll< f32 >(easeInValue1);
    mBlackHoleModel->mScale.setAll< f32 >(0.5f * easeInValue2);

    if (MR::isStep(this, 90)) {
        kill();
    }
}
