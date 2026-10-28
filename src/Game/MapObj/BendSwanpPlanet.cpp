#include "Game/MapObj/BendSwanpPlanet.hpp"
#include "Game/LiveActor/CollisionObj.hpp"
#include "Game/LiveActor/Nerve.hpp"
#include "Game/Util/ActorAnimUtil.hpp"
#include "Game/Util/ActorInitUtil.hpp"
#include "Game/Util/ActorSwitchUtil.hpp"
#include "Game/Util/JointUtil.hpp"
#include "Game/Util/LiveActorUtil.hpp"
#include "Game/Util/ModelUtil.hpp"
#include <cstdio>

namespace NrvBendSwanpPlanet {
    NEW_NERVE(BendSwanpPlanetNrvWaitA, BendSwanpPlanet, WaitA);
    NEW_NERVE(BendSwanpPlanetNrvMoveA, BendSwanpPlanet, MoveA);
    NEW_NERVE(BendSwanpPlanetNrvWaitB, BendSwanpPlanet, WaitB);
    NEW_NERVE(BendSwanpPlanetNrvMoveB, BendSwanpPlanet, MoveB);
    NEW_NERVE(BendSwanpPlanetNrvWaitC, BendSwanpPlanet, WaitC);
};  // namespace NrvBendSwanpPlanet

namespace {
    const char* cCollisionNames[] = {
        "BendSwanpPlanetPartsA",
        "BendSwanpPlanetPartsB",
        "BendSwanpPlanetPartsC",
    };
};

BendSwanpPlanet::BendSwanpPlanet(const char* pName) : LiveActor(pName), mCollisionObjs() {
}

void BendSwanpPlanet::init(const JMapInfoIter& rIter) {
    MR::initActor(this, rIter, false);

    f32 boundingRadius = 0.0f;
    MR::calcModelBoundingRadius(&boundingRadius, this);

    MR::setClippingTypeSphere(this, boundingRadius);
    MR::setClippingFarMax(this);

    mCollisionObjs = new CollisionObj*[ARRAY_SIZE(cCollisionNames)];

    for (s32 i = 0; i < ARRAY_SIZE(cCollisionNames); i++) {
        char jointName[256];
        snprintf(jointName, sizeof(jointName), "Collision[%s]", cCollisionNames[i]);

        mCollisionObjs[i] = MR::createCollisionObj(this, cCollisionNames[i], getSensor(nullptr), MR::getJointMtx(this, cCollisionNames[i]));
        MR::validateCollisionParts(mCollisionObjs[i]);
    }

    MR::initUseStageSwitchReadA(this, rIter);
    MR::initUseStageSwitchReadB(this, rIter);

    initNerve(GET_NERVE(BendSwanpPlanet, BendSwanpPlanetNrvWaitA));

    makeActorAppeared();
}

void BendSwanpPlanet::exeWaitA() {
    if (MR::isFirstStep(this)) {
        MR::startAction(this, "WaitA");
    }

    if (MR::isOnSwitchA(this)) {
        setNerve(GET_NERVE(BendSwanpPlanet, BendSwanpPlanetNrvMoveA));
    }
}

void BendSwanpPlanet::exeMoveA() {
    if (MR::isFirstStep(this)) {
        MR::startAction(this, "MoveA");
    }

    if (MR::isActionEnd(this)) {
        setNerve(GET_NERVE(BendSwanpPlanet, BendSwanpPlanetNrvWaitB));
    }
}

void BendSwanpPlanet::exeWaitB() {
    if (MR::isFirstStep(this)) {
        MR::startAction(this, "WaitB");
    }

    if (MR::isOnSwitchB(this)) {
        setNerve(GET_NERVE(BendSwanpPlanet, BendSwanpPlanetNrvMoveB));
    }
}

void BendSwanpPlanet::exeMoveB() {
    if (MR::isFirstStep(this)) {
        MR::startAction(this, "MoveB");
    }

    if (MR::isActionEnd(this)) {
        setNerve(GET_NERVE(BendSwanpPlanet, BendSwanpPlanetNrvWaitC));
    }
}

void BendSwanpPlanet::exeWaitC() {
    if (MR::isFirstStep(this)) {
        MR::startAction(this, "WaitC");
    }
}
