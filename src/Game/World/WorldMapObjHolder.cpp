#include "Game/World/WorldMapObjHolder.hpp"
#include "Game/World/WorldMapPointPartsHolder.hpp"

WorldMapObjHolder::WorldMapObjHolder(s32 worldNo) : mWorldNo(worldNo), _4(), _8(), _C(), _10(), mPointPartsHolder(), _18(), _1C() {
}

// TODO
void WorldMapObjHolder::init() {
    mPointPartsHolder = new WorldMapPointPartsHolder(this);
    mPointPartsHolder->init();
}

// TODO
void WorldMapObjHolder::appear() {
    mPointPartsHolder->appear();
}

// TODO
void WorldMapObjHolder::kill() {
    mPointPartsHolder->kill();
}
