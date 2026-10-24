#include "Game/World/MiniComet.hpp"
#include "Game/LiveActor/Nerve.hpp"
#include "Game/Util/ActorAnimUtil.hpp"
#include "Game/Util/ActorInitUtil.hpp"
#include "Game/Util/DemoUtil.hpp"
#include "Game/Util/LiveActorUtil.hpp"

namespace NrvMiniComet {
    NEW_NERVE(MiniCometNrvDemo, MiniComet, Demo);
};

MiniComet::MiniComet(const char* pName) : LiveActor("コメット（ワールドマップ）"), mName(pName) {
}

void MiniComet::init(const JMapInfoIter& rIter) {
    MR::initActor(this, rIter, "MiniComet", false);
    initNerve(GET_NERVE(MiniComet, MiniCometNrvDemo));

    MR::invalidateClipping(this);

    MR::registerDemoSimpleCastAll(this);

    makeActorAppeared();
}

void MiniComet::appear() {
    LiveActor::appear();
    MR::startAction(this, "Appear");
}

void MiniComet::exeDemo() {
    if (MR::isActionEnd(this)) {
        kill();
    }
}
