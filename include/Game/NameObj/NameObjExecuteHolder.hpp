#pragma once

#include "Game/NameObj/NameObj.hpp"

class LiveActor;

class NameObjExecuteInfo {
    friend class NameObjExecuteHolder;

    NameObjExecuteInfo();
};

class NameObjExecuteHolder : public NameObj {
    NameObjExecuteHolder(int);
};

namespace MR {
    void connectToDrawTemporarily(NameObj*);
    void disconnectToDrawTemporarily(NameObj*);
};  // namespace MR
