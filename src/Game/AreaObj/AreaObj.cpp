#include "Game/AreaObj/AreaObj.hpp"
#include "Game/AreaObj/AreaForm.hpp"
// #include "Game/AreaObj/AreaObjFollower.hpp"
// #include "Game/Map/SleepControllerHolder.hpp"
#include "Game/Map/StageSwitch.hpp"
// #include "Game/Util/AreaObjUtil.hpp"
#include "Game/Util/JMapInfo.hpp"
#include "Game/Util/JMapUtil.hpp"
#include "Game/Util/ObjUtil.hpp"
#include "revolution/types.h"
#include <algorithm>
#include <functional.hpp>

AreaObj::AreaObj(const char* pName)
    : NameObj(pName), mForm(nullptr), mFormType(-1), mIsValid(true), _1D(true), mObjArg0(-1), mObjArg1(-1), mObjArg2(-1), mObjArg3(-1), mObjArg4(-1),
      mObjArg5(-1), mObjArg6(-1), mObjArg7(-1), mPriority(-1), mSwitchCtrl() {
}

AreaObj::AreaObj(int formType, const char* pName)
    : NameObj(pName), mForm(nullptr), mFormType(formType), mIsValid(true), _1D(true), mObjArg0(-1), mObjArg1(-1), mObjArg2(-1), mObjArg3(-1),
      mObjArg4(-1), mObjArg5(-1), mObjArg6(-1), mObjArg7(-1), mPriority(-1), mSwitchCtrl() {
}

void AreaObj::init(const JMapInfoIter& rIter) {
    initForm(rIter);
    // MR::addBaseMatrixFollowerAreaObj(this, rIter);
    MR::getJMapInfoArg0WithInit(rIter, &mObjArg0);
    MR::getJMapInfoArg1WithInit(rIter, &mObjArg1);
    MR::getJMapInfoArg2WithInit(rIter, &mObjArg2);
    MR::getJMapInfoArg3WithInit(rIter, &mObjArg3);
    MR::getJMapInfoArg4WithInit(rIter, &mObjArg4);
    MR::getJMapInfoArg5WithInit(rIter, &mObjArg5);
    MR::getJMapInfoArg6WithInit(rIter, &mObjArg6);
    MR::getJMapInfoArg7WithInit(rIter, &mObjArg7);
    MR::getJMapInfoPriorityWithInit(rIter, &mPriority);

    mSwitchCtrl = MR::createStageSwitchCtrl(this, rIter);

    if (mSwitchCtrl->isValidSwitchAppear()) {
        MR::listenNameObjStageSwitchOnOffAppear(this, mSwitchCtrl, MR::Functor(this, &AreaObj::validate), MR::Functor(this, &AreaObj::invalidate));
        mIsValid = false;
    }

    const char* name;

    if (MR::getObjectName(&name, rIter)) {
        setName(name);
    }

    // MR::getAreaObjManager(getManagerName())->entry(this);
    // MR::getAreaObjManager(getManagerName());
    // SleepControlFunc::addSleepControl(this, rIter);
}

void AreaObj::initForm(const JMapInfoIter& rIter) {
    s32 areaId = 1;
    MR::getJMapInfoAreaIdWithInit(rIter, &areaId);
    if (mFormType == -1) {
        mFormType = areaId;
    }

    mForm = MR::createAreaForm(mFormType);
    mForm->init(rIter);
}

bool AreaObj::isInVolume(const TVec3f& rPos) const {
    return isValid() && mForm->isInVolume(rPos);
}

void AreaObj::onSwitchA() {
    mSwitchCtrl->onSwitchA();
}

void AreaObj::offSwitchA() {
    mSwitchCtrl->offSwitchA();
}

bool AreaObj::isOnSwitchA() const {
    return mSwitchCtrl->isOnSwitchA();
}

bool AreaObj::isOnSwitchB() const {
    return mSwitchCtrl->isOnSwitchB();
}

bool AreaObj::isValidSwitchA() const {
    return mSwitchCtrl->isValidSwitchA();
}

bool AreaObj::isValidSwitchB() const {
    return mSwitchCtrl->isValidSwitchB();
}

bool AreaObj::isNotHemisphere() const {
    return mFormType == AreaForm::Type_Cube1 || mFormType == AreaForm::Type_Cube2 || mFormType == AreaForm::Type_Sphere ||
           mFormType == AreaForm::Type_Cylinder;
}

void AreaObj::setFollowMtx(const TPos3f* pMtx) {
    mForm->_4 = const_cast< TPos3f* >(pMtx);
}

TPos3f* AreaObj::getFollowMtx() const {
    return mForm->_4;
}

AreaObjMgr::AreaObjMgr(s32 count, const char* pName) : NameObj(pName), mArray(), _20(count) {
}

void AreaObjMgr::entry(AreaObj* pAreaObj) {
    if (mArray.capacity() == 0) {
        mArray.init(_20);
    }

    mArray.push_back(pAreaObj);

    for (int i = mArray.size() - 1; i >= 1; i--) {
        int index = i - 1;
        AreaObj* area1 = mArray[i];
        AreaObj* area2 = mArray[index];
        if (area1->getAreaPriority() < area2->getAreaPriority()) {
            mArray[index] = area1;
            mArray[i] = area2;
        } else {
            break;
        }
    }
}

AreaObj* AreaObjMgr::find_in(const TVec3f& rVec) const {
    AreaObj* const* Begin = mArray.begin();
    AreaObj* const* End = mArray.end();
    AreaObj* const* p = std::rfind_if(
        End - 1, Begin - 1,
        std::binder2nd< std::const_mem_fun1_t< bool, AreaObj, const TVec3f& >, const TVec3f& >(std::mem_func(&AreaObj::isInVolume), rVec));

    p = (p == Begin - 1 ? End : p);

    if (p != mArray.end()) {
        return *p;
    }

    return nullptr;
}

void AreaObjMgr::requestMovementOnAll() {
    for (int i = 0; i < mArray.size(); i++) {
        MR::requestMovementOn(mArray[i]);
    }
}
