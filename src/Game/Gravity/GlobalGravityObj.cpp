#include "Game/Gravity/GlobalGravityObj.hpp"
#include "Game/Gravity/GravityCreator.hpp"
#include "Game/Gravity/GravityFollower.hpp"
#include "Game/Gravity/PlanetGravity.hpp"
#include "Game/Util/ActorInitUtil.hpp"
#include "Game/Util/ActorSwitchUtil.hpp"
#include "Game/Util/DemoUtil.hpp"
#include "Game/Util/LiveActorUtil.hpp"
#include "Game/Util/ObjUtil.hpp"


GlobalGravityObj::GlobalGravityObj(const char* pName) : LiveActor(pName), mGravityCreator() {
}

void GlobalGravityObj::init(const JMapInfoIter& rIter) {
    MR::initDefaultPos(this, rIter);
    mGravityCreator->createFromJMap(rIter);

    MR::initUseStageSwitchReadA(this, rIter);
    MR::initUseStageSwitchReadB(this, rIter);

    if (MR::isValidSwitchA(this) || MR::isValidSwitchB(this)) {
        MR::connectToSceneMapObjMovement(this);
    }

    MR::invalidateClipping(this);
    MR::registerDemoSimpleCastAll(this);
    MR::addBaseMatrixFollowerGravity(this, rIter);

    makeActorAppeared();
    MR::useStageSwitchAwake(this, rIter);
}

void GlobalGravityObj::makeActorAppeared() {
    LiveActor::makeActorAppeared();

    PlanetGravity* pGravity = mGravityCreator->getGravity();
    pGravity->mAppeared = true;

    updateSwitch();
}

void GlobalGravityObj::makeActorDead() {
    LiveActor::makeActorDead();

    PlanetGravity* pGravity = mGravityCreator->getGravity();
    pGravity->mAppeared = false;
}

void GlobalGravityObj::updateSwitch() {
    if (MR::isValidSwitchA(this) || MR::isValidSwitchB(this)) {
        bool switchA = true;
        bool switchB = true;

        if (MR::isValidSwitchA(this)) {
            switchA = MR::isOnSwitchA(this);
        }

        if (MR::isValidSwitchB(this)) {
            switchB = MR::isOnSwitchB(this) == false;
        }

        PlanetGravity* pGravity = mGravityCreator->getGravity();
        pGravity->mActivated = switchA && switchB;
    }
}

void GlobalGravityObj::movement() {
    updateSwitch();
}

PlanetGravity* GlobalGravityObj::getGravity() {
    return mGravityCreator->getGravity();
}

namespace MR {
    NameObj* createGlobalBarrelGravityObj(const char* pName) {
        GlobalGravityObj* pObj = new GlobalGravityObj(pName);
        pObj->mGravityCreator = new BarrelGravityCreator();
        return pObj;
    }

    NameObj* createGlobalCubeGravityObj(const char* pName) {
        GlobalGravityObj* pObj = new GlobalGravityObj(pName);
        pObj->mGravityCreator = new CubeGravityCreator();
        return pObj;
    }

    NameObj* createGlobalConeGravityObj(const char* pName) {
        GlobalGravityObj* pObj = new GlobalGravityObj(pName);
        pObj->mGravityCreator = new ConeGravityCreator();
        return pObj;
    }

    NameObj* createGlobalDiskGravityObj(const char* pName) {
        GlobalGravityObj* pObj = new GlobalGravityObj(pName);
        pObj->mGravityCreator = new DiskGravityCreator();
        return pObj;
    }

    NameObj* createGlobalDiskTorusGravityObj(const char* pName) {
        GlobalGravityObj* pObj = new GlobalGravityObj(pName);
        pObj->mGravityCreator = new DiskTorusGravityCreator();
        return pObj;
    }

    NameObj* createGlobalPlaneGravityObj(const char* pName) {
        GlobalGravityObj* pObj = new GlobalGravityObj(pName);
        pObj->mGravityCreator = new PlaneGravityCreator();
        return pObj;
    }

    NameObj* createGlobalPlaneInBoxGravityObj(const char* pName) {
        GlobalGravityObj* pObj = new GlobalGravityObj(pName);
        pObj->mGravityCreator = new PlaneInBoxGravityCreator();
        return pObj;
    }

    NameObj* createGlobalPlaneInCylinderGravityObj(const char* pName) {
        GlobalGravityObj* pObj = new GlobalGravityObj(pName);
        pObj->mGravityCreator = new PlaneInCylinderGravityCreator();
        return pObj;
    }

    NameObj* createGlobalPointGravityObj(const char* pName) {
        GlobalGravityObj* pObj = new GlobalGravityObj(pName);
        pObj->mGravityCreator = new PointGravityCreator();
        return pObj;
    }

    NameObj* createGlobalSegmentGravityObj(const char* pName) {
        GlobalGravityObj* pObj = new GlobalGravityObj(pName);
        pObj->mGravityCreator = new SegmentGravityCreator();
        return pObj;
    }

    NameObj* createGlobalWireGravityObj(const char* pName) {
        GlobalGravityObj* pObj = new GlobalGravityObj(pName);
        pObj->mGravityCreator = new WireGravityCreator();
        return pObj;
    }

    NameObj* createZeroGravitySphereObj(const char* pName) {
        GlobalGravityObj* pObj = new GlobalGravityObj(pName);
        pObj->mGravityCreator = new PlaneZeroGravityCreator();
        return pObj;
    }

    NameObj* createZeroGravityBoxObj(const char* pName) {
        GlobalGravityObj* pObj = new GlobalGravityObj(pName);
        pObj->mGravityCreator = new PlaneZeroInBoxGravityCreator();
        return pObj;
    }

    NameObj* createZeroGravityCylinderObj(const char* pName) {
        GlobalGravityObj* pObj = new GlobalGravityObj(pName);
        pObj->mGravityCreator = new PlaneZeroInCylinderGravityCreator();
        return pObj;
    }
};  // namespace MR
