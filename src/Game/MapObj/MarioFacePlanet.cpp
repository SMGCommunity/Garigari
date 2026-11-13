#include "Game/MapObj/MarioFacePlanet.hpp"
#include "Game/LiveActor/Nerve.hpp"
#include "Game/Util/ActorInitUtil.hpp"
#include "Game/Util/ActorSwitchUtil.hpp"
#include "Game/Util/DemoUtil.hpp"
#include "Game/Util/EventUtil.hpp"
#include "Game/Util/LiveActorUtil.hpp"

namespace NrvMarioFacePlanet {
    NEW_NERVE(MarioFacePlanetNrvWait, MarioFacePlanet, Wait);
};  // namespace NrvMarioFacePlanet

MarioFacePlanet::MarioFacePlanet(const char* pName) : LiveActor(pName) {
}

void MarioFacePlanet::init(const JMapInfoIter& rIter) {
    MR::initActor(this, rIter, false);

    MR::initFurPlanet(this);

    initNerve(GET_NERVE(MarioFacePlanet, MarioFacePlanetNrvWait));

    if (MR::tryRegisterDemoCast(this, rIter)) {
        MR::tryRegisterDemoActionFunctor(this, MR::Functor(this, &MarioFacePlanet::listenDemoAction), nullptr);
    }

    MR::registerDemoSimpleCastAll(this);

    MR::useStageSwitchSyncAppear(this, rIter);
}

void MarioFacePlanet::listenDemoAction() {
    MR::explainMarioFacePlanetAtFirst(this);
}

void MarioFacePlanet::exeWait() {
}
