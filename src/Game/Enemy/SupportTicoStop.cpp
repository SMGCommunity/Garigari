#include "Game/Enemy/SupportTicoStop.hpp"
#include "Game/Enemy/AnimScaleController.hpp"
#include "Game/LiveActor/Nerve.hpp"
#include "Game/Util/ActorAnimUtil.hpp"
#include "Game/Util/ActorMovementUtil.hpp"
#include "Game/Util/EffectUtil.hpp"
#include "Game/Util/SoundUtil.hpp"
#include "Game/Util/SupportPlayUtil.hpp"

namespace NrvSupportTicoStop {
    NEW_NERVE(SupportTicoStopNrvWait, SupportTicoStop, Wait);
    NEW_NERVE(SupportTicoStopNrvStop, SupportTicoStop, Stop);
    NEW_NERVE(SupportTicoStopNrvEnd, SupportTicoStop, End);
};  // namespace NrvSupportTicoStop

SupportTicoStop::SupportTicoStop(LiveActor* pHost, AnimScaleController* pScaleController)
    : NerveExecutor("スターポインタ停止"), mHost(pHost), mScaleController(pScaleController), _10(), _14(), _15(), mUsePointerTouch() {
    initNerve(GET_NERVE(SupportTicoStop, SupportTicoStopNrvWait));

    if (MR::isExistEffectKeeper(pHost) && !MR::isRegisteredEffect(pHost, "Touch")) {
        mUsePointerTouch = true;
        MR::addEffect(pHost, "PointerTouch");
    }
}

bool SupportTicoStop::tryStop() {
    if (MR::attachSupportTicoToTarget(mHost)) {
        if (!isStopped()) {
            _14 = true;
            setNerve(GET_NERVE(SupportTicoStop, SupportTicoStopNrvStop));
        }

        return true;
    }

    if (isStopped()) {
        return true;
    }

    _15 = true;
    return false;
}

bool SupportTicoStop::tryEnd() {
    if (isStopped()) {
        setNerve(GET_NERVE(SupportTicoStop, SupportTicoStopNrvEnd));
        return true;
    }

    return false;
}

bool SupportTicoStop::isStopped() const {
    return isNerve(GET_NERVE(SupportTicoStop, SupportTicoStopNrvStop));
}

void SupportTicoStop::exeStop() {
    if (getNerveStep() == 0) {
        MR::startDPDHitSound();
        _10 = 0;

        if (MR::isExistEffectKeeper(mHost)) {
            MR::emitEffect(mHost, mUsePointerTouch ? "PointerTouch" : "Touch");
        }

        if (MR::isExistBck(mHost, nullptr)) {
            MR::setBckRate(mHost, 0.0f);
        }

        if (mScaleController != nullptr) {
            mScaleController->startDpdHitVibration();
        }
    }

    resetTouchBools();

    MR::startDPDFreezeLevelSound(mHost);
    MR::zeroVelocity(mHost);

    if (MR::attachSupportTicoToTarget(mHost)) {
        _10 = 0;
    } else {
        _10++;
    }

    if (_10 > 0) {
        setNerve(GET_NERVE(SupportTicoStop, SupportTicoStopNrvEnd));
    }
}

void SupportTicoStop::exeWait() {
    resetTouchBools();
}

void SupportTicoStop::exeEnd() {
    if (getNerveStep() == 0) {
        _15 = true;

        if (mScaleController != nullptr) {
            mScaleController->startAnim();
        }

        if (MR::isExistEffectKeeper(mHost)) {
            MR::deleteEffect(mHost, mUsePointerTouch ? "PointerTouch" : "Touch");
        }

        if (MR::isExistBck(mHost, nullptr)) {
            MR::setBckRate(mHost, 1.0f);
        }
    } else {
        resetTouchBools();
    }

    setNerve(GET_NERVE(SupportTicoStop, SupportTicoStopNrvWait));
}
