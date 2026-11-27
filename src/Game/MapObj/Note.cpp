#include "Game/MapObj/Note.hpp"
#include "Game/LiveActor/FlashingCtrl.hpp"
#include "Game/LiveActor/Nerve.hpp"
#include "Game/MapObj/NoteFairy.hpp"
#include "Game/Scene/SceneObjHolder.hpp"
#include "Game/Screen/NoteCounter.hpp"
#include "Game/Util/ActionSoundUtil.hpp"
#include "Game/Util/ActorAnimUtil.hpp"
#include "Game/Util/ActorInitUtil.hpp"
#include "Game/Util/ActorSensorUtil.hpp"
#include "Game/Util/ActorShadowUtil.hpp"
#include "Game/Util/EffectUtil.hpp"
#include "Game/Util/GravityUtil.hpp"
#include "Game/Util/LiveActorUtil.hpp"
#include "Game/Util/MathUtil.hpp"
#include "Game/Util/ModelUtil.hpp"
#include "Game/Util/MtxUtil.hpp"
#include "Game/Util/ObjUtil.hpp"

namespace {
    static const f32 sBodySensorRadius = 80.0f;
    static const f32 sFlyUpSpeed = 30.0f;
    static const f32 sRotateSpeed = 8.0f;
    static const f32 sShadowRadius = 30.0f;
    static const s32 sStepFlyUp = 10;
};  // namespace

namespace NrvNote {
    NEW_NERVE(NoteNrvWait, Note, Wait);
    NEW_NERVE(NoteNrvCountDown, Note, CountDown);
    NEW_NERVE(NoteNrvFlyUp, Note, FlyUp);
};  // namespace NrvNote

Note::Note(const char* pName, const TVec3f& rRailDirection, NoteFairy* pNoteFairy)
    : LiveActor(pName), mNoteFairy(pNoteFairy), _94(0.0f, 0.0f, 0.0f), mRailDirection(rRailDirection), mCounter(), _B0(), mIsCountdown(),
      mFlashCtrl() {
}

void Note::init(const JMapInfoIter& rIter) {
    MR::createSceneObj(SceneObj_NoteGroup);
    _94.set(mPosition);
    MR::initActor(this, "Note", false);
    MR::connectToSceneNoSilhouettedMapObjStrongLight(this);
    initHitSensor(1);
    MR::addHitSensorMapObj(this, "Body", 8, ::sBodySensorRadius, TVec3f(0.0f, 0.0f, 0.0f));
    initEffectKeeper(0, nullptr, false);
    initSound(4, "Note");
    initNerve(GET_NERVE(Note, NoteNrvWait));
    mFlashCtrl = new FlashingCtrl(this, true);
    MR::calcGravityAndDropShadowVector(this, &mGravity, nullptr, 0);

    if (MR::isNearZero(mGravity)) {
        mGravity.set(0.0f, -1.0f, 0.0f);
    }

    MR::initShadowVolumeSphere(this, ::sShadowRadius);
    MR::turnVecToPlane(&mRailDirection, mRailDirection, mGravity);
    MR::invalidateClipping(this);
    makeActorDead();
}

void Note::startCountDown() {
    mIsCountdown = true;
}

void Note::exeWait() {
    if (MR::isFirstStep(this)) {
        MR::startBrk(this, "Note");
        f32 frameMax = MR::getBrkFrameMax(this, "Note");
        MR::setBrkFrame(this, MR::repeat(_B0, 0.0f, frameMax));
    }

    if (mIsCountdown) {
        setNerve(GET_NERVE(Note, NoteNrvCountDown));
    }
}

void Note::exeCountDown() {
    if (MR::isFirstStep(this)) {
        mFlashCtrl->start(mCounter);
    }

    if (MR::isStep(this, mCounter)) {
        MR::emitEffect(this, "Vanish");
        MR::startActionSound(this, "OjMusicalNoteBreak");
        MR::failureNoteCollection();
        kill();
    }
}

void Note::exeFlyUp() {
    if (MR::isFirstStep(this)) {
        mVelocity.set(mGravity);
        mVelocity.scale(-::sFlyUpSpeed);
        MR::invalidateHitSensors(this);
        mFlashCtrl->end();
    }

    if (MR::isStep(this, ::sStepFlyUp)) {
        kill();
    }
}

void Note::appear() {
    MR::calcGravityAndDropShadowVector(this, &mGravity, nullptr, 0);

    if (MR::isNearZero(mGravity)) {
        mGravity.set(0.0f, -1.0f, 0.0f);
    }

    LiveActor::appear();
}

void Note::control() {
    mRotation.y = MR::getSceneObj< NoteGroup >(SceneObj_NoteGroup)->mRotation;
}

void Note::calcAndSetBaseMtx() {
    TPos3f mtxUpFront;
    MR::makeMtxUpFront(&mtxUpFront, -mGravity, mRailDirection);
    Mtx mtxRotateY;
    f32 groupRotation = MR::getSceneObj< NoteGroup >(SceneObj_NoteGroup)->mRotation;
    MR::makeMtxRotateY(mtxRotateY, groupRotation);
    MR::multMtx(mtxUpFront, mtxRotateY, mtxUpFront);
    mtxUpFront.setTrans(mPosition);
    MR::setBaseTRMtx(this, mtxUpFront);
}

void Note::attackSensor(HitSensor* pSender, HitSensor* pReceiver) {
    if (MR::isSensorPlayerOrRide(pReceiver) && !MR::isSensorGhost(pReceiver) && !isNerve(GET_NERVE(Note, NoteNrvFlyUp))) {
        MR::emitEffect(this, "Get");
        MR::addNoteToCounter();
        mNoteFairy->setLastGotNote(this);
        setNerve(GET_NERVE(Note, NoteNrvFlyUp));
    }
}

NoteGroup::NoteGroup() : LiveActorGroup("音符グループ", 256), mRotation() {
}

void NoteGroup::init(const JMapInfoIter& rIter) {
    MR::connectToSceneMapObjMovement(this);
}

void NoteGroup::movement() {
    mRotation += ::sRotateSpeed;
    mRotation = MR::repeat(mRotation, 0.0f, 360.0f);
}
