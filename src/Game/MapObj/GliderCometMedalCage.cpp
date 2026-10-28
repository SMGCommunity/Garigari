#include "Game/MapObj/GliderCometMedalCage.hpp"
#include "Game/LiveActor/Nerve.hpp"
#include "Game/Util/ActorAnimUtil.hpp"
#include "Game/Util/ActorInitUtil.hpp"
#include "Game/Util/ActorSwitchUtil.hpp"
#include "Game/Util/JMapInfo.hpp"
#include "Game/Util/LiveActorUtil.hpp"

namespace NrvGliderCometMedalCage {
    NEW_NERVE(NrvGliderCometMedalCageNrvWait, GliderCometMedalCage, Wait);
    NEW_NERVE(NrvGliderCometMedalCageNrvMove, GliderCometMedalCage, Move);
};  // namespace NrvGliderCometMedalCage

GliderCometMedalCage::GliderCometMedalCage(const char* pName) : LiveActor(pName), _90() {
}

void GliderCometMedalCage::init(const JMapInfoIter& rIter) {
    MR::initActor(this, rIter, false);

    initNerve(GET_NERVE(GliderCometMedalCage, NrvGliderCometMedalCageNrvWait));

    makeActorAppeared();
}

void GliderCometMedalCage::exeWait() {
    if (MR::isFirstStep(this)) {
        MR::startAction(this, "Wait");
    }

    if (MR::isOnSwitchB(this)) {
        setNerve(GET_NERVE(GliderCometMedalCage, NrvGliderCometMedalCageNrvMove));
    }
}

void GliderCometMedalCage::exeMove() {
    if (MR::isFirstStep(this)) {
        MR::startAction(this, "Move");
        MR::startHitReaction(this, "オープン");
        MR::invalidateCollisionParts(this);
    }
}
