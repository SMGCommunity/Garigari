#include "Game/NameObj/NameObj.hpp"
#include "Game/NameObj/NameObjRegister.hpp"
#include "Game/Scene/SceneNameObjMovementController.hpp"
#include "Game/SingletonHolder.hpp"

NameObj::NameObj(const char *pName) : mLinkInfo() {
    mName = NULL;
    mFlags = 0;
    mExecutionIdx = -1;
    mLinkInfo.reset();
    mName = pName;
    SingletonHolder<NameObjRegister>::sInstance->add(this);
}

NameObj::~NameObj() {

}

void NameObj::init(const JMapInfoIter &) {

}

void NameObj::initAfterPlacement() {

}

void NameObj::movement() {

}

void NameObj::draw() const {

}

void NameObj::calcAnim() {

}

void NameObj::calcViewAndEntry() {

}

void NameObj::initWithoutIter() {
    JMapInfoIter iter;
    iter.mInfo = 0;
    iter._4 = -1;
    init(iter);
}

void NameObj::setName(const char *pName) {
    mName = pName;
}

void NameObj::setLinkedInfo(const JMapInfoIter &rIter) {
    mLinkInfo.setLinkedInfo(rIter);
}

void NameObj::executeMovement() {
    if ((mFlags & 0x1) != (u32)1) {
        movement();
    }
}

void NameObj::requestSuspend() {
    if ((mFlags & 4) == 4u) {
        mFlags &= 0xFFFB;
    }

    mFlags |= 2;
}

void NameObj::requestResume() {
    if ((mFlags & 2) == 2u) {
        mFlags &= 0xFFFD;
    }

    mFlags |= 4;
}

void NameObj::syncWithFlags() {
    if ((mFlags & 2) == 2u) {
        mFlags = mFlags & 0xFFFD | 1;
    }

    if ((mFlags & 4) == 4u) {
        u16 flag = mFlags & 0xFFFB;
        flag &= ~0x1;
        mFlags = flag;
    }
}

void NameObjFunction::requestMovementOn(NameObj *pObj) {
    pObj->requestResume();
    pObj->startMovement();
    MR::notifyRequestNameObjMovementOnOff();
}

void NameObjFunction::requestMovementOff(NameObj *pObj) {
    pObj->requestSuspend();
    pObj->endMovement();
    MR::notifyRequestNameObjMovementOnOff();
}