#include "LiveActor/LiveActor.hpp"
#include "Util/ActorSensorUtil.hpp"
struct View46BD0 : LiveActor { u8 opaque[0x20]; HitSensor* sensor; };
extern "C" { extern const u32 lbl_807D34D8,lbl_807D34DC; }
extern "C" void fn_80246BD0(View46BD0* obj,HitSensor*,HitSensor* other) {
 if(MR::isSensorNpc(other) && obj->isNerve(reinterpret_cast<const Nerve*>(&lbl_807D34D8))) {
  obj->sensor=other;
  obj->setNerve(reinterpret_cast<const Nerve*>(&lbl_807D34DC));
 }
}
