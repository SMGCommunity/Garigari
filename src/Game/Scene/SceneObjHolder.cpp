#include "Game/Scene/SceneObjHolder.hpp"
#include "Game/NameObj/NameObj.hpp"
#include "Game/Util/SingletonHolder.hpp"
#include "Game/System/GameSystem.hpp"

SceneObjHolder::SceneObjHolder() {
    for (int i = 0; i < SceneObj_NumMax; i++) {
        mObj[i] = nullptr;
    }
}

NameObj* SceneObjHolder::create(int id) {
    NameObj* pObj = mObj[id];

    if (pObj != nullptr) {
        return pObj;
    }

    pObj = newEachObj(id);
    pObj->initWithoutIter();

    mObj[id] = pObj;

    return pObj;
}

NameObj* SceneObjHolder::getObj(int id) const {
    return mObj[id];
}

bool SceneObjHolder::isExist(int id) const {
    return mObj[id] != nullptr;
}

NameObj* SceneObjHolder::newEachObj(int id) {
    switch (id) {
    // Good luck to the poor soul who does this
    default:
        return nullptr;
    }
}

namespace MR {
    NameObj* createSceneObj(int id) {
        return getSceneObjHolder()->create(id);
    }

    //SceneObjHolder* getSceneObjHolder() {
    //    return SingletonHolder< GameSystem >::get()->mSceneController->getSceneObjHolder();
    //}

    //bool isExistSceneObj(int id) {
    //    GameSystemSceneController* pSceneController = SingletonHolder< GameSystem >::get()->mSceneController;

    //    if (pSceneController == nullptr) {
    //        return false;
    //    }

    //    if (!pSceneController->isExistSceneObjHolder()) {
    //        return false;
    //    }

    //    return MR::getSceneObjHolder()->isExist(id);
    //}
};  // namespace MR
