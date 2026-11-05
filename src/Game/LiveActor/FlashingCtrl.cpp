#include "Game/LiveActor/FlashingCtrl.hpp"
#include "Game/Scene/SceneFunction.hpp"
#include "Game/Util/ActionSoundUtil.hpp"
#include "Game/Util/DemoUtil.hpp"
#include "Game/Util/LiveActorUtil.hpp"
#include "Game/Util/ObjUtil.hpp"

FlashingCtrl::FlashingCtrl(LiveActor* pActor, bool toggleDraw)
    : NameObj("点滅"), mActor(pActor), mToggleDraw(toggleDraw), mIsEnded(true), mOverrideInterval(), mTimer(), mFlashStartTime(), mDoBlink() {
    // TODO: MovementType enum
    MR::connectToScene(this, MR::MovementType_MapObj, MR::CalcAnimType_None, MR::DrawBufferType_None, MR::DrawType_None);
}

void FlashingCtrl::movement() {
    if (mIsEnded) {
        return;
    }

    if (--mTimer <= 0 || MR::isClipped(mActor) || MR::isDead(mActor)) {
        end();
    } else if (MR::isDemoActive()) {
        if (mToggleDraw && MR::isNoEntryDrawBuffer(mActor)) {
            MR::onEntryDrawBuffer(mActor);
        }
    } else if (isNowFlashing()) {
        updateFlashing();
    }
}

void FlashingCtrl::start(int timer) {
    mIsEnded = false;
    mTimer = timer;
    mFlashStartTime = 180;
    mOverrideInterval = 0;
}

void FlashingCtrl::end() {
    mTimer = 0;
    mIsEnded = true;

    if (mToggleDraw && !MR::isDead(mActor) && !MR::isClipped(mActor) && MR::isNoEntryDrawBuffer(mActor)) {
        MR::onEntryDrawBuffer(mActor);
    }
}

s32 FlashingCtrl::getCurrentInterval() const {
    if (mOverrideInterval) {
        return 8;
    }

    return mTimer < 90 ? 5 : 10;
}

bool FlashingCtrl::isNowFlashing() const {
    return mTimer <= mFlashStartTime;
}

bool FlashingCtrl::isNowOn() const {
    return !((mTimer / getCurrentInterval()) & 1);
}

void FlashingCtrl::updateFlashing() {
    if (!mToggleDraw) {
        return;
    }

    if (isNowOn()) {
        MR::offEntryDrawBuffer(mActor);

        if (mDoBlink) {
            MR::startActionSoundState0(mActor, "Blink");
            mDoBlink = false;
        }
    } else {
        MR::onEntryDrawBuffer(mActor);
        mDoBlink = true;
    }
}
