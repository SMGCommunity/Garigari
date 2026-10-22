#pragma once

#define SceneObj_StageSwitchContainer 0xA
#define SceneObj_SwitchWatcherHolder 0xB
#define SceneObj_18 0x18
#define SceneObj_19 0x19
#define SceneObj_PlanetGravityManager 0x3B

class NameObj;

enum SceneObj {
    SceneObj_LiveActorGroupArray = 0x0E,
    SceneObj_GroupCheckManager = 0x66
};

class SceneObjHolder {
public:
    SceneObjHolder();

    NameObj* create(int);
    NameObj* getObj(int) const;
    bool isExist(int) const;
    NameObj* newEachObj(int);

    /* 0x0 */ NameObj* mObjs[0x99];
};

namespace MR {
    NameObj* createSceneObj(int);
    SceneObjHolder* getSceneObjHolder();
    bool isExistSceneObj(int);

    template < class T >
    inline T* getSceneObj(int objID) {
        return reinterpret_cast< T* >(MR::getSceneObjHolder()->getObj(objID));
    }
};  // namespace MR
