#include "Game/Enemy/FireBallSpreadLava.hpp"
#include "Game/LiveActor/Nerve.hpp"
#include "Game/Util/ActionSoundUtil.hpp"
#include "Game/Util/ActorInitUtil.hpp"
#include "Game/Util/ActorSensorUtil.hpp"
#include "Game/Util/Color.hpp"
#include "Game/Util/EffectUtil.hpp"
#include "Game/Util/LiveActorUtil.hpp"
#include "Game/Util/ObjUtil.hpp"
#include "Game/Util/PlayerUtil.hpp"

extern "C" void fn_8003DEF0(f32*, f32*, const TVec3f*, const TVec3f*, const TVec3f*);

namespace {
    const GXColor cColor = {255, 192, 0, 255};
};

namespace NrvFireBallSpreadLava {
    NEW_NERVE(FireBallSpreadLavaNrvHidden, FireBallSpreadLava, Hidden);
    NEW_NERVE(FireBallSpreadLavaNrvAppear, FireBallSpreadLava, Appear);
    NEW_NERVE(FireBallSpreadLavaNrvWait, FireBallSpreadLava, Wait);
    NEW_NERVE(FireBallSpreadLavaNrvShrink, FireBallSpreadLava, Shrink);
};  // namespace NrvFireBallSpreadLava

FireBallSpreadLava::FireBallSpreadLava(FireBallSpread* pFireBallSpread, const char* pName)
    : LiveActor(pName), mHost(pFireBallSpread), mClipAreaDrop(), _98() {
}

void FireBallSpreadLava::init(const JMapInfoIter& rIter) {
    MR::initActor(this, rIter, "FireBallSpreadLava", false);
    initNerve(GET_NERVE(FireBallSpreadLava, FireBallSpreadLavaNrvHidden));

    // mClipAreaDrop = new ClipAreaDrop("クリップエリアのしずく", "VolumeSphere");
    // mClipAreaDrop->initWithoutIter();

    MR::invalidateClipping(this);

    kill();

    MR::hideModel(this);
}

// void FireBallSpreadLava::control() {}

void FireBallSpreadLava::kill() {
    if (MR::isEffectValid(this, "Land")) {
        MR::deleteEffect(this, "Land");
    }

    // mClipAreaDrop->kill();

    LiveActor::kill();
}

void FireBallSpreadLava::attackSensor(HitSensor* pSender, HitSensor* pReceiver) {
    if (MR::isSensorPlayer(pReceiver)) {
        return;
    }

    if (MR::isOnGroundPlayer()) {
        return;
    }

    MR::calcGravity(this);

    f32 f1;
    f32 f2;
    TVec3f vec(-mGravity);
    fn_8003DEF0(&f1, &f2, MR::getSensorPos(pSender), MR::getPlayerPos(), &vec);

    // FIXME
    if (f2 < 10.0f && f1 < _98 - 10.0f) {
        MR::sendMsgEnemyAttackFire(pReceiver, pSender);
    }
}

void FireBallSpreadLava::appearLava(const TVec3f& rPos) {
    mPosition = rPos;
    mRotation.set(0.0f);

    setNerve(GET_NERVE(FireBallSpreadLava, FireBallSpreadLavaNrvAppear));

    makeActorAppeared();

    MR::startHitReaction(this, "着弾");

    // MR::setPosition(mClipAreaDrop, mPosition);
    // mClipAreaDrop->setBaseSize(400.0f);
    // mClipAreaDrop->fn_80285C80(60);
    // mClipAreaDrop->fn_80285CA0(180, 240);
    // mClipAreaDrop->appear();
}

void FireBallSpreadLava::exeHidden() {
}

void FireBallSpreadLava::exeAppear() {
    // FIXME
    _98 = MR::calcNerveRate(this, 60) * 400.0f;

    if (MR::isGreaterEqualStep(this, 60)) {
        setNerve(GET_NERVE(FireBallSpreadLava, FireBallSpreadLavaNrvWait));
    }
}

void FireBallSpreadLava::exeWait() {
    if (MR::isGreaterEqualStep(this, 120)) {
        setNerve(GET_NERVE(FireBallSpreadLava, FireBallSpreadLavaNrvShrink));
    }
}

void FireBallSpreadLava::exeShrink() {
    if (MR::isFirstStep(this)) {
        MR::startActionSound(this, "Shrink");
    }

    // FIXME
    _98 = (1.0f - MR::calcNerveRate(this, 60)) * 400.0f;

    if (MR::isGreaterEqualStep(this, 60)) {
        setNerve(GET_NERVE(FireBallSpreadLava, FireBallSpreadLavaNrvHidden));

        MR::startHitReaction(this, "消滅");

        kill();
    }
}
