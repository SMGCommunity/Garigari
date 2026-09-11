#pragma once
class LiveActor;
class LodCtrl;
class JMapInfoIter;

// Recovered interface only; object storage has not yet been reconstructed.
class ClippingDirector {
public:
    void registerActor(LiveActor*);
    void entryLodCtrl(LodCtrl*, const JMapInfoIter&);
};
namespace MR {
    ClippingDirector* getClippingDirector();
}
