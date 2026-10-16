#include "Game/MapObj/TicoCoin.hpp"
#include "Game/LiveActor/LiveActor.hpp"
#include "Game/LiveActor/Nerve.hpp"
#include "Game/MapObj/ActorStateDemoAppearance.hpp"
#include "Game/System/GameDataFunction.hpp"
#include "Game/System/GameSequenceFunction.hpp"
#include "Game/Util/ActorAnimUtil.hpp"
#include "Game/Util/ActorInitUtil.hpp"
#include "Game/Util/ActorSensorUtil.hpp"
#include "Game/Util/ActorShadowUtil.hpp"
#include "Game/Util/ActorStateUtil.hpp"
#include "Game/Util/ActorSwitchUtil.hpp"
#include "Game/Util/DemoUtil.hpp"
#include "Game/Util/EventUtil.hpp"
#include "Game/Util/LiveActorUtil.hpp"
#include "Game/Util/SceneUtil.hpp"

namespace NrvTicoCoin {
    NEW_NERVE(TicoCoinNrvAppear, TicoCoin, Appear);
    NEW_NERVE(TicoCoinNrvRotate, TicoCoin, Rotate);
    NEW_NERVE(TicoCoinNrvCollect, TicoCoin, Collect);
    NEW_NERVE(TicoCoinNrvDisappear, TicoCoin, Disappear);
}  // namespace NrvTicoCoin

TicoCoin::TicoCoin(const char* pName) : LiveActor(pName), _90(0.0f, 0.0f, 0.0f) {
}

void TicoCoin::init(const JMapInfoIter& rIter) {
    MR::initActor(this, rIter, "TicoCoin", false);
    MR::calcGravity(this);
    initNerve(GET_NERVE(TicoCoin, TicoCoinNrvRotate), 1);

    ActorStateDemoAppearance* stateDemoAppearance = new ActorStateDemoAppearance(this, rIter, "Appear");
    MR::initActorState(this, stateDemoAppearance, GET_NERVE(TicoCoin, TicoCoinNrvAppear), "Appear");

    MR::startBva(this, isCollectedInStage() ? "Empty" : "Normal");

    if (MR::useStageSwitchSyncAppear(this, rIter)) {
        setNerve(GET_NERVE(TicoCoin, TicoCoinNrvAppear));
        MR::invalidateClipping(this);
    }

    if (GameSequenceFunction::isCollectTicoCoinSaved()) {
        makeActorDead();
        setNerve(GET_NERVE(TicoCoin, TicoCoinNrvDisappear));
    }

    if (MR::isStageJungleGliderGalaxyExplainDemo()) {
        MR::registerDemoSimpleCastAll(this);
    }
}

void TicoCoin::initAfterPlacement() {
    MR::setClippingRangeIncludeShadow(this, &_90, 300.0f);
}

void TicoCoin::makeActorAppeared() {
    if (!isNerve(GET_NERVE(TicoCoin, TicoCoinNrvDisappear))) {
        LiveActor::makeActorAppeared();
    }
}

void TicoCoin::control() {
}

bool TicoCoin::receiveMsgPlayerAttack(u32 msg, HitSensor* pSender, HitSensor* pReceiver) {
    return MR::isMsgStarPieceReflect(msg);
}

bool TicoCoin::receiveOtherMsg(u32 msg, HitSensor* pSender, HitSensor* pReceiver) {
    if (MR::isMsgItemGet(msg)) {
        return tryCollect();
    }

    return false;
}

bool TicoCoin::tryCollect() {
    if (isNerve(GET_NERVE(TicoCoin, TicoCoinNrvRotate))) {
        setNerve(GET_NERVE(TicoCoin, TicoCoinNrvCollect));
        return true;
    }

    return false;
}

void TicoCoin::exeAppear() {
    MR::updateActorStateAndNextNerve(this, GET_NERVE(TicoCoin, TicoCoinNrvRotate));
}

void TicoCoin::exeRotate() {
    if (MR::isFirstStep(this)) {
        MR::startAction(this, "Rotate");
    }
}

void TicoCoin::exeCollect() {
    if (MR::isFirstStep(this)) {
        MR::startAction(this, "Get");
        MR::hideModel(this);
        // TODO: ScoreAttackFunction::score1000Points(this)
        if (MR::isProductGameScene()) {
            GameSequenceFunction::collectTicoCoinInStage();
        }
    }

    if (MR::isGreaterStep(this, 2)) {
        MR::explainCometMedalIfAtFirst(this);
        makeActorDead();
        setNerve(GET_NERVE(TicoCoin, TicoCoinNrvDisappear));
    }
}

void TicoCoin::exeDisappear() {
}

bool TicoCoin::isCollectedInStage() const {
    if (MR::isProductGameScene()) {
        return GameDataFunction::isOnGalaxyFlagTicoCoin(MR::getCurrentStageName());
    }

    return false;
}
