#pragma once

#define SceneObj_StageSwitchContainer   0xA

class NameObj;

class SceneObjHolder {
public:
    NameObj* create(int);
    NameObj* getObj(int) const;
    bool isExist(int) const;
    NameObj* newEachObj(int);

    NameObj* mObjs[0x99];       // 0x00
};

namespace MR {
    NameObj* createSceneObj(int);
    SceneObjHolder* getSceneObjHolder();
    bool isExistSceneObj(int);

    template <class T>
    inline T getSceneObj(int objID) {
        return reinterpret_cast<T>(MR::getSceneObjHolder()->getObj(objID));
    }
};
