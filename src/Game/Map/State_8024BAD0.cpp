#include "LiveActor/LiveActor.hpp"
#include "Util/ActorCameraUtil.hpp"
extern "C" {
extern u32 lbl_807D34F4;
void fn_8024BAD0(LiveActor* obj) {
 obj->LiveActor::kill();
 MR::endActorCameraProgrammable(obj,-1,true);
}
void fn_8024BB10(LiveActor* obj) {
 obj->setNerve(reinterpret_cast<const Nerve*>(&lbl_807D34F4));
}
}
