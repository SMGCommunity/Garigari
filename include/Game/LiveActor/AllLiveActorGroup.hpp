#pragma once

#include "Game/LiveActor/LiveActorGroup.hpp"

class JMapInfoIter;

class AllLiveActorGroup : public LiveActorGroup {
public:
    AllLiveActorGroup();
    ~AllLiveActorGroup();

    void initActorSystemInfo(const JMapInfoIter&);
};

namespace MR {
    AllLiveActorGroup* getAllLiveActorGroup();
    void startInitLiveActorSystemInfo();
    void initLiveActorSystemInfo(const JMapInfoIter&);
    void endInitLiveActorSystemInfo();
}
