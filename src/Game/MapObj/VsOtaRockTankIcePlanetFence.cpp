#include "Game/MapObj/VsOtaRockTankIcePlanetFence.hpp"
#include "Game/LiveActor/LiveActor.hpp"
#include "Game/Util/ActorInitUtil.hpp"

VsOtaRockTankIcePlanetFence::VsOtaRockTankIcePlanetFence(const char* pName) : LiveActor(pName) {
}

void VsOtaRockTankIcePlanetFence::init(const JMapInfoIter& rIter) {
    MR::initActor(this, rIter, false);
    makeActorAppeared();
}
