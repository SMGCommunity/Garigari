#include "LiveActor/LiveActorGroup.hpp"
#include "LiveActor/LiveActor.hpp"
#include "Util.hpp"

LiveActorGroup::LiveActorGroup(const char *pName, int max) : NameObjGroup(pName, max) {

}

void LiveActorGroup::registerActor(LiveActor *pActor) {
    registerObj(pActor);
}

LiveActor* LiveActorGroup::getActor(int idx) const {
    return getObj<LiveActor*>(idx);
}


LiveActor* LiveActorGroup::getDeadActor() const {
    for (s32 i = 0; i < mObjectCount; i++) {
        if (MR::isDead(getObj<LiveActor*>(i))) {
            return getObj<LiveActor*>(i);
        }
    }

    return nullptr;
}

s32 LiveActorGroup::getLivingActorNum() const {
    s32 count = 0;
    for (s32 i = 0; i < mObjectCount; i++) {
        if (!MR::isDead(getObj<LiveActor*>(i))) {
            count++;
        }
    }

    return count;
}

void LiveActorGroup::killAll() {
    for (s32 i = 0; i < mObjectCount; i++) {
        getObj<LiveActor*>(i)->kill();
    }
}

void LiveActorGroup::appearAll() {
    for (s32 i = 0; i < mObjectCount; i++) {
        getObj<LiveActor*>(i)->makeActorAppeared();
    }
}


void LiveActorGroup::makeAllDead() {
    for (s32 i = 0; i < mObjectCount; i++) {
        getObj<LiveActor*>(i)->makeActorDead();
    }
}
