#include "LiveActor/LiveActor.hpp"
namespace MR {
void connectToSceneMapObjMovement(NameObj*);
void invalidateClipping(LiveActor*);
void initActorCameraProgrammable(const LiveActor*);
}
extern "C" {
extern u32 lbl_807D34F0;
void fn_8024B9A0(LiveActor* obj,const JMapInfoIter&) {
 MR::connectToSceneMapObjMovement(obj);
 MR::invalidateClipping(obj);
 MR::initActorCameraProgrammable(obj);
 obj->initNerve(reinterpret_cast<const Nerve*>(&lbl_807D34F0),0);
 obj->makeActorDead();
}
}
