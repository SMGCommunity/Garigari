#pragma once

#include "Game/NameObj/NameObj.hpp"

class LiveActor;

class NameObjExecuteInfo {
    friend class NameObjExecuteHolder;

public:
    NameObjExecuteInfo();
};

class NameObjExecuteHolder : public NameObj {
public:
    NameObjExecuteHolder(int);
};

namespace MR {
    void connectToDrawTemporarily(NameObj*);
    void disconnectToDrawTemporarily(NameObj*);
};  // namespace MR
