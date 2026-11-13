#include "Game/MapObj/WhiteSnowTree.hpp"
#include "Game/LiveActor/LiveActor.hpp"
#include "Game/Util/ActorInitUtil.hpp"

WhiteSnowTree::WhiteSnowTree(const char* pName) : LiveActor(pName) {
}

void WhiteSnowTree::init(const JMapInfoIter& rIter) {
    MR::initActor(this, rIter, "WhiteSnowTree", false);
    makeActorAppeared();
}
