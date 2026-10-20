#pragma once

class LiveActor;
class JMapInfoIter;
class LodCtrl;

class ClippingDirector {
public:
    ClippingDirector();
    ~ClippingDirector();

    void endInitActorSystemInfo();
    void movement();
    void registerActor(LiveActor*);
    void initActorSystemInfo(LiveActor*, const JMapInfoIter&);
    void entryLodCtrl(LodCtrl*, JMapInfoIter&);
};

namespace MR {
    ClippingDirector* getClippingDirector();
    void addToClippingTarget(LiveActor*);
    void removeFromClippingTarget(LiveActor*);
}
