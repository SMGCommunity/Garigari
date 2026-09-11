#include "LiveActor/LiveActor.hpp"
namespace MR { void initActor(LiveActor*,const char*,bool);void invalidateClipping(LiveActor*); }
extern "C" {
extern const char lbl_80696A68[];
extern u32 lbl_807D350C;
void fn_8004AE10(void*);
void fn_8024C260(LiveActor* obj,const JMapInfoIter&) {
 MR::initActor(obj,lbl_80696A68,false);
 fn_8004AE10(obj);
 MR::invalidateClipping(obj);
 obj->initNerve(reinterpret_cast<const Nerve*>(&lbl_807D350C),0);
 obj->makeActorDead();
}
}
