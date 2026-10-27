#include "Game/Enemy/Foomin.hpp"
#include "Game/LiveActor/Nerve.hpp"
#include "Game/Util/ActorInitUtil.hpp"

namespace NrvFoomin {
    NEW_NERVE(FoominNrvWait, Foomin, Wait);
    NEW_NERVE(FoominNrvWaitDelay, Foomin, WaitDelay);
    NEW_NERVE(FoominNrvAttackSign, Foomin, AttackSign);
    NEW_NERVE(FoominNrvAttack, Foomin, Attack);
}; // namespace nrvFoomin


Foomin::Foomin(const char* pName) : LiveActor(pName), mSupportTicoStop(), _94(0.0f, 0.0f, 1.0f), mMovementSpeed(250), mFirstFlipDelay() {}



void Foomin::makeActorAppeared() {
    if (mFirstFlipDelay > 0) {
        setNerve(GET_NERVE(Foomin, FoominNrvWaitDelay));
    } else {
        setNerve(GET_NERVE(Foomin, FoominNrvWait));
    }

    LiveActor::makeActorAppeared();
}
