#include "Game/NameObj/NameObjRegister.hpp"
#include "Game/NameObj/NameObjHolder.hpp"

void NameObjRegister::setCurrentHolder(NameObjHolder* pHolder) {
    mHolder = pHolder;
}

void NameObjRegister::add(NameObj* pObj) {
    mHolder->add(pObj);
}

NameObjRegister::NameObjRegister() {
    mHolder = nullptr;
}
