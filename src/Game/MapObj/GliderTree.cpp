#include "Game/MapObj/GliderTree.hpp"
#include "Game/LiveActor/LiveActor.hpp"
#include "Game/LiveActor/Nerve.hpp"
#include "Game/Util/ActorAnimUtil.hpp"
#include "Game/Util/ActorInitUtil.hpp"
#include "Game/Util/ActorSensorUtil.hpp"
#include "Game/Util/JMapUtil.hpp"
#include "Game/Util/LiveActorUtil.hpp"

namespace NrvGliderTree {
    NEW_NERVE(GliderTreeNrvWait, GliderTree, Wait);
    NEW_NERVE(GliderTreeNrvSwing, GliderTree, Swing);
};  // namespace NrvGliderTree

GliderTree::GliderTree(const char* pName) : LiveActor(pName) {
}

void GliderTree::init(const JMapInfoIter& rIter) {
    const char* pObjName;
    MR::getObjectName(&pObjName, rIter);

    MR::initActor(this, rIter, pObjName, false);

    initNerve(GET_NERVE(GliderTree, GliderTreeNrvWait));

    makeActorAppeared();
}

bool GliderTree::receiveOtherMsg(u32 msg, HitSensor* pSender, HitSensor* pReceiver) {
    if (!isNerve(GET_NERVE(GliderTree, GliderTreeNrvWait))) {
        return false;
    }

    if (!MR::isSensorPlayerOrRide(pSender)) {
        return false;
    }

    if (msg == ACTMES_GLI_BIRD_TOUCH) {
        setNerve(GET_NERVE(GliderTree, GliderTreeNrvSwing));
        return true;
    }

    return false;
}

void GliderTree::exeWait() {
}

void GliderTree::exeSwing() {
    if (MR::isFirstStep(this)) {
        MR::startAction(this, "Swing");
    }

    if (MR::isActionEnd(this)) {
        setNerve(GET_NERVE(GliderTree, GliderTreeNrvWait));
    }
}
