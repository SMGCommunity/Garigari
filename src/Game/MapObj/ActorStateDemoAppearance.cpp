#include "Game/MapObj/ActorStateDemoAppearance.hpp"
#include "Game/LiveActor/LiveActor.hpp"
#include "Game/LiveActor/Nerve.hpp"
#include "Game/Util/ActorAnimUtil.hpp"
#include "Game/Util/ActorCameraUtil.hpp"
#include "Game/Util/DemoUtil.hpp"
#include "Game/Util/NerveUtil.hpp"

namespace NrvActorStateDemoAppearance {
    NEW_NERVE(ActorStateDemoAppearanceNrvAppear, ActorStateDemoAppearance, Appear);
    NEW_NERVE(ActorStateDemoAppearanceNrvWait, ActorStateDemoAppearance, Wait);
}

ActorStateDemoAppearance::ActorStateDemoAppearance(LiveActor* pHost, const JMapInfoIter& rIter, const char* pActionName)
    : ActorStateBase< LiveActor >("デモ出現状態", pHost), mCameraInfo(), mActionName(pActionName), mCameraTime(-1), _1C(-1), mIsInitCamera(), _21() {
    initNerve(GET_NERVE(ActorStateDemoAppearance, ActorStateDemoAppearanceNrvAppear));
    mIsInitCamera = MR::initMultiActorCamera(mHost, rIter, &mCameraInfo, "出現デモカメラ");
}

void ActorStateDemoAppearance::appear() {
    ActorStateBaseInterface::appear();

    if (mIsInitCamera) {
        setNerve(GET_NERVE(ActorStateDemoAppearance, ActorStateDemoAppearanceNrvAppear));
        mCameraTime = MR::getMultiActorCameraFrames(mHost, mCameraInfo, "出現デモカメラ");

        if (mCameraTime <= 0) {
            mCameraTime = 120;
        }
    } else {
        if (mActionName != nullptr) {
            MR::startAction(mHost, mActionName);
        }

        setNerve(GET_NERVE(ActorStateDemoAppearance, ActorStateDemoAppearanceNrvWait));
    }
}

void ActorStateDemoAppearance::exeAppear() {
    if (MR::tryStartDemo(mHost, "出現デモ")) {
        setNerve(GET_NERVE(ActorStateDemoAppearance, ActorStateDemoAppearanceNrvWait));
        MR::startMultiActorCameraTargetSelf(mHost, mCameraInfo, "出現デモカメラ", -1);

        if (mActionName != nullptr) {
            MR::startAction(mHost, mActionName);
        }
    }
}

void ActorStateDemoAppearance::exeWait() {
    if (isDemoEnd()) {
        if (mIsInitCamera) {
            MR::endMultiActorCamera(mHost, mCameraInfo, "出現デモカメラ", false, -1);
            MR::endDemo(mHost, "出現デモ");
        }

        kill();
    }    
}

bool ActorStateDemoAppearance::isDemoEnd() const {
    if (_21) {
        return MR::isActionEnd(mHost);
    }

    if (_1C > 0) {
        if (MR::isGreaterEqualStep(this, _1C)) {
            return true;
        }
    } else if (MR::isGreaterEqualStep(this, mCameraTime)) {
        return true;
    }

    return false;
}
