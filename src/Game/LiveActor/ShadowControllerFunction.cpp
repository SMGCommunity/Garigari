#include "LiveActor/LiveActor.hpp"
#include "LiveActor/ShadowControllerList.hpp"
#include "Scene/SceneObjHolder.hpp"

// Only the retail holder prefix and its vector at offset 0x14 are needed here.
struct ShadowRegisteredHolder {
    u8 _0[0x14];
    MR::Vector<MR::AssignableArray<ShadowController*> > controllers;
};

extern "C" bool fn_80057470(const LiveActor*);

namespace MR {
    void addShadowController(ShadowController* controller) {
        ShadowRegisteredHolder* holder = reinterpret_cast<ShadowRegisteredHolder*>(getSceneObjHolder()->getObj(0x4C));
        holder->controllers.push_back(controller);
    }

    void requestCalcActorShadowAppear(LiveActor* actor) {
        if (!fn_80057470(actor)) {
            if (actor->mShadowList) actor->mShadowList->resetCalcCount();
            if (actor->mShadowList) actor->mShadowList->requestCalc();
        }
    }

    void requestCalcActorShadow(LiveActor* actor) {
        if (actor->mShadowList) actor->mShadowList->requestCalc();
    }
}
