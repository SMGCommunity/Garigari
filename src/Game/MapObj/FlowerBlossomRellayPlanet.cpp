#include "Game/MapObj/FlowerBlossomRellayPlanet.hpp"
#include "Game/LiveActor/LiveActor.hpp"
#include "Game/LiveActor/Nerve.hpp"
#include "Game/Util/ActorInitUtil.hpp"
#include "Game/Util/ActorSwitchUtil.hpp"
#include "Game/Util/DemoUtil.hpp"
#include "Game/Util/LiveActorUtil.hpp"

namespace NrvFlowerBlossomRellayPlanet {
    NEW_NERVE(FlowerBlossomRellayPlanetNrvWait, FlowerBlossomRellayPlanet, Wait);
    NEW_NERVE(FlowerBlossomRellayPlanetNrvBloomStart, FlowerBlossomRellayPlanet, BloomStart);
    NEW_NERVE(FlowerBlossomRellayPlanetNrvBloomEnd, FlowerBlossomRellayPlanet, BloomEnd);
};  // namespace NrvFlowerBlossomRellayPlanet

FlowerBlossomRellayPlanet::FlowerBlossomRellayPlanet(const char* pName) : LiveActor(pName) {
}

void FlowerBlossomRellayPlanet::init(const JMapInfoIter& rIter) {
    MR::initActor(this, rIter, false);

    initNerve(GET_NERVE(FlowerBlossomRellayPlanet, FlowerBlossomRellayPlanetNrvWait));

    MR::tryRegisterDemoCast(this, rIter);

    makeActorAppeared();
}

void FlowerBlossomRellayPlanet::exeWait() {
    if (MR::isValidSwitchB(this) && MR::isOnSwitchB(this)) {
        setNerve(GET_NERVE(FlowerBlossomRellayPlanet, FlowerBlossomRellayPlanetNrvBloomStart));
    }
}

void FlowerBlossomRellayPlanet::exeBloomStart() {
    if (MR::tryStartDemoRegistered(this, nullptr)) {
        MR::startHitReaction(this, "咲いた");
        setNerve(GET_NERVE(FlowerBlossomRellayPlanet, FlowerBlossomRellayPlanetNrvBloomEnd));
    }
}

void FlowerBlossomRellayPlanet::exeBloomEnd() {
    if (MR::isDemoActive() && MR::isDemoPartLastStep(nullptr)) {
        MR::onSwitchA(this);
    }
}
