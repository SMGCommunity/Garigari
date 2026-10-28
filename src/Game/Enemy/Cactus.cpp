#include "Game/Enemy/Cactus.hpp"
#include "Game/LiveActor/Nerve.hpp"
#include "Game/Util/ActorInitUtil.hpp"
#include "Game/Util/ActorSensorUtil.hpp"

namespace NrvCactus {
    NEW_NERVE(CactusNrvWait, Cactus, Wait);
};  // namespace NrvCactus

Cactus::Cactus(const char* pName) : LiveActor(pName) {
}

void Cactus::init(const JMapInfoIter& rIter) {
    MR::initActor(this, rIter, false);
    initNerve(GET_NERVE(Cactus, CactusNrvWait));
    makeActorAppeared();
}

void Cactus::attackSensor(HitSensor* pSender, HitSensor* pReceiver) {
    if (MR::isEqualSensor(pSender, this, "Body") && isNerveWait()) {
        MR::sendMsgEnemyAttack(pReceiver, pSender);
    }
}

bool Cactus::isNerveWait() const {
    return isNerve(GET_NERVE(Cactus, CactusNrvWait));
}

inline void Cactus::exeWait() {
}
