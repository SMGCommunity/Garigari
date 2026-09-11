#pragma once

#include <revolution.h>
class LiveActor;
class ShadowController;

namespace MR {
    template<class T> class AssignableArray;
    template<class T> struct Vector;

    // Only this specialization's verified array/capacity/count prefix is exposed.
    template<> struct Vector<AssignableArray<ShadowController*> > {
        Vector();
        void push_back(ShadowController* const&);
        ShadowController** array;
        u32 capacity;
        s32 count;
    };
}

class ShadowControllerList {
public:
    ShadowControllerList(LiveActor*, u32);
    void addController(ShadowController*);
    u32 getControllerCount() const;
    ShadowController* getController(u32) const;
    ShadowController* getController(const char*) const;
    void resetCalcCount();
    void requestCalc();

    MR::Vector<MR::AssignableArray<ShadowController*> > mList;
    LiveActor* mHost; // 0xC; total verified allocation 0x10.
};
