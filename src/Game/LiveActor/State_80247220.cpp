#include "LiveActor/LiveActor.hpp"
#include "Util/ActorMovementUtil.hpp"
extern "C" {
bool fn_800503F0();
extern const f32 lbl_807DC660;
extern const u32 lbl_807D34E0;
}
extern "C" bool fn_80247220(LiveActor* obj) {
 if(lbl_807DC660<MR::calcDistanceToPlayer(obj))return false;
 if(!fn_800503F0())return false;
 obj->setNerve(reinterpret_cast<const Nerve*>(&lbl_807D34E0));
 return true;
}
