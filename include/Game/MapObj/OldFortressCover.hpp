#pragma once

#include "Game/LiveActor/LiveActor.hpp"

class OldFortressCover : public LiveActor {
public:
    OldFortressCover(const char* pName);

    virtual void init(const JMapInfoIter& rIter);

    void exeWait();
    void exeOpen();
    void exeEnd();
};
