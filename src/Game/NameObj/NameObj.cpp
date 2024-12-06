#include "NameObj/NameObj.hpp"
#include "NameObj/NameObjRegister.hpp"
#include "Scene/SceneNameObjMovementController.hpp"
#include "Util/JMapInfo.hpp"
#include "Singleton.hpp"

template<>
NameObjRegister* SingletonHolder<NameObjRegister>::sInstance = nullptr;

NameObj::NameObj(const char *pName) : mName(nullptr), mFlags(0), mExecutorIdx(-1) {
    mName = pName;
    SingletonHolder<NameObjRegister>::get()->add(this);
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
    JMapInfoIter iter(nullptr, -1);
    init(iter);
}

void NameObj::setName(const char *pName) {
    mName = pName;
}

void NameObj::setLinkedInfo(const JMapInfoIter &rIter) {
    mLinkInfo.setLinkedInfo(rIter);
}

void NameObj::executeMovement() {
    if ((mFlags & 0x1u) != 1) {
        movement();
    }
}

void NameObj::requestSuspend() {
    if ((mFlags & 0x4u) == 4) {
        mFlags &= (u16)~4;
    }

    mFlags |= 2;
}

void NameObj::requestResume() {
    if ((mFlags & 0x2u) == 2) {
        mFlags &= (u16)~2;
    }

    mFlags |= 4;
}

void NameObj::syncWithFlags() {
    u16 flag = (mFlags & 0x2);
    if (flag == 0x2) {
        flag = mFlags;
        flag &= (u16)~0x2;
        flag |= 0x1;
        mFlags = flag;
    }

    flag = (mFlags & 0x4u);
    if (flag == 0x4) {
        flag = mFlags & (u16)0xFFFB;
        mFlags = flag & ~0x1;
    }
}

namespace NameObjFunction {
    void requestMovementOn(NameObj *pObj) {
        pObj->requestResume();
        pObj->startMovement();
        MR::notifyRequestNameObjMovementOnOff();
    }

    void requestMovementOff(NameObj *pObj) {
        pObj->requestSuspend();
        pObj->endMovement();
        MR::notifyRequestNameObjMovementOnOff();
    }
};
