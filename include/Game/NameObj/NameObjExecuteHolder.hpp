#pragma once

#include "Game/NameObj/NameObj.hpp"

class LiveActor;

struct NameObjExecuteInfo {
    friend class NameObjExecuteHolder;

    NameObjExecuteInfo();
};

struct NameObjExecuteHolder : NameObj {
    NameObjExecuteHolder(int);
};

namespace MR {
    void connectToDrawTemporarily(NameObj*);
    void disconnectToDrawTemporarily(NameObj*);
}  // namespace MR
