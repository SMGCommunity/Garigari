#include "Game/MapObj/Sun.hpp"
#include "Game/Util/ActorInitUtil.hpp"
#include "Game/Util/LiveActorUtil.hpp"
#include "Game/Util/ObjUtil.hpp"

Sun::Sun(const char* pName) : LiveActor(pName) {
}

void Sun::init(const JMapInfoIter& rIter) {
    MR::initActor(this, "Sun", false);
    MR::connectToSceneSun(this);
    MR::invalidateClipping(this);
    makeActorAppeared();
}

Sun::~Sun() {
}
