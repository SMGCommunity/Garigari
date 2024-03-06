#pragma once

#include <revolution/types.h>

class NameObjHolder;
class NameObjListExecutor;

class GameSystemSceneController {
public:
    NameObjListExecutor* getNameObjListExecutor() const;

    u8 _0[0xA8];
    NameObjHolder* mObjHolder;     // _A8
};