#include "Game/Screen/CometMedalCounter.hpp"
#include "Game/LiveActor/Nerve.hpp"
#include "Game/Screen/CounterLayoutAppearer.hpp"
#include "Game/Screen/CounterLayoutController.hpp"
#include "Game/Screen/LayoutActor.hpp"
#include "Game/System/GameDataFunction.hpp"
#include "Game/System/GameSequenceFunction.hpp"
#include "Game/Util/LayoutUtil.hpp"
#include "Game/Util/LiveActorUtil.hpp"
#include "Game/Util/ObjUtil.hpp"
#include "Game/Util/SceneUtil.hpp"
#include "JSystem/JGeometry/TVec.hpp"

namespace NrvCometMedalCounter {
    NEW_NERVE(CometMedalCounterNrvHidden, CometMedalCounter, Hidden);
    NEW_NERVE(CometMedalCounterNrvAppear, CometMedalCounter, Appear);
    NEW_NERVE(CometMedalCounterNrvWait, CometMedalCounter, Wait);
    NEW_NERVE(CometMedalCounterNrvFlash, CometMedalCounter, Flash);
    NEW_NERVE(CometMedalCounterNrvDisappear, CometMedalCounter, Disappear);
}  // namespace NrvCometMedalCounter

CometMedalCounter::CometMedalCounter() : LayoutActor("コメットメダルカウンター", true), _2C(), _30(), _34(), _38(), mIsCollected(), _3D() {
}

void CometMedalCounter::init(const JMapInfoIter& rIter) {
    initLayoutManager("CometMedalCounter", 3);
    _30 = new CounterLayoutAppearer(this, TVec2f(-50.0f, 0.0f));
    MR::connectToSceneLayout(this);
    initNerve(GET_NERVE(CometMedalCounter, CometMedalCounterNrvHidden));

    if (!isAppearInCurrentScenario()) {
        MR::startAnimAndSetFrameAndStop(this, "Icon", 2.0f, 2);
    }
    else if (GameSequenceFunction::isCollectTicoCoinSaved() || GameDataFunction::isOnGalaxyFlagTicoCoin(MR::getCurrentStageName())) {
        MR::startAnimAndSetFrameAndStop(this, "Icon", 1.0f, 2);
        mIsCollected = true;
    } else {
        mIsCollected = false;
        MR::startAnimAndSetFrameAndStop(this, "Icon", 0.0f, 2);
    }
}

void CometMedalCounter::appear() {
    if (!isAppearInCurrentScenario()) {
        return;
    }

    _30->reset();
    setNerve(GET_NERVE(CometMedalCounter, CometMedalCounterNrvHidden));
    LayoutActor::appear();
    _3D = false;
    MR::requestMovementOn(this);
}

void CometMedalCounter::forceAppear(bool a1) {
    bool isWait;

    if (!a1) {
        isWait = false;

        if (isNerve(GET_NERVE(CometMedalCounter, CometMedalCounterNrvWait)) || isNerve(GET_NERVE(CometMedalCounter, CometMedalCounterNrvFlash))) {
            isWait = true;
        }
    }
    else {
        isWait = true;
    }

    if (!isWait) {
        appear();
        setNerve(GET_NERVE(CometMedalCounter, CometMedalCounterNrvAppear));
    }

    _3D = true;
}

void CometMedalCounter::disappear() {
    _3D = false;
    setNerve(GET_NERVE(CometMedalCounter, CometMedalCounterNrvDisappear));
}

bool CometMedalCounter::isWait() const {
    bool isWait = false;

    if (isNerve(GET_NERVE(CometMedalCounter, CometMedalCounterNrvWait)) || isNerve(GET_NERVE(CometMedalCounter, CometMedalCounterNrvFlash))) {
        isWait = true;
    }

    return isWait;
}

void CometMedalCounter::control() {
    _30->update();

    if (!mIsCollected && GameSequenceFunction::isCollectTicoCoinInStage() && !isNerve(GET_NERVE(CometMedalCounter, CometMedalCounterNrvFlash)) &&
        !isNerve(GET_NERVE(CometMedalCounter, CometMedalCounterNrvAppear))) {
        if (!isNerve(GET_NERVE(CometMedalCounter, CometMedalCounterNrvWait))) {
            setNerve(GET_NERVE(CometMedalCounter, CometMedalCounterNrvAppear));
        } else {
            setNerve(GET_NERVE(CometMedalCounter, CometMedalCounterNrvFlash));
        }
    }
}

bool CometMedalCounter::isAppearInCurrentScenario() const {
    bool isAppearInCurrentScenario = false;

    if (MR::isProductGameScene() && MR::getCurrentStagePowerStarNum() != 0 && MR::getCurrentScenarioNo() == 1) {
        isAppearInCurrentScenario = true;
    }

    return isAppearInCurrentScenario;
}

void CometMedalCounter::exeHidden() {
    if (MR::isFirstStep(this)) {
        MR::hideLayout(this);
    }
}

void CometMedalCounter::exeAppear() {
    if (MR::isFirstStep(this)) {
        MR::showLayout(this);
        _30->appear(TVec2f(0.0f, 0.0f));
        MR::startAnim(this, "Wait", 1);
    }

    if (_30->isAppeared()) {
        setNerve(GET_NERVE(CometMedalCounter, CometMedalCounterNrvWait));
    }
}

void CometMedalCounter::exeWait() {
    if (!_3D && mIsCollected && CounterLayoutController::isWaitToDisappearCounter(this)) {
        setNerve(GET_NERVE(CometMedalCounter, CometMedalCounterNrvDisappear));
    }
}

void CometMedalCounter::exeFlash() {
    if (MR::isFirstStep(this)) {
        MR::startAnimAndSetFrameAndStop(this, "Icon", 1.0f, 2);
        MR::startAnim(this, "Flash", 0);
    }

    if (MR::isAnimStopped(this, 0)) {
        mIsCollected = true;
        setNerve(GET_NERVE(CometMedalCounter, CometMedalCounterNrvWait));
    }
}

void CometMedalCounter::exeDisappear() {
    if (MR::isFirstStep(this)) {
        _30->disappear();
    }

    if (_30->isDisappeared()) {
        setNerve(GET_NERVE(CometMedalCounter, CometMedalCounterNrvHidden));
    }
}
