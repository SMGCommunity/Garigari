#include "NameObj/NameObjRegister.hpp"
#include "NameObj/NameObjHolder.hpp"

void NameObjRegister::setCurrentHolder(NameObjHolder *pHolder) {
    mHolder = pHolder;
}

void NameObjRegister::add(NameObj *pObj) {
    mHolder->add(pObj);
}

NameObjRegister::NameObjRegister() {
    mHolder = nullptr;
}
