#include "LiveActor/LiveActor.hpp"
struct Actor4BC80 { u8 opaque[0xa8];TVec3f a8,b4;f32 c0,c4;TVec3f up; };
namespace MR { bool isFirstStep(const LiveActor*); }
extern "C" {
extern const f32 lbl_80648B18[3],lbl_80648B24[3];
extern const f32 lbl_807DC6C0,lbl_807DC6B4,lbl_807DC6B0;
void fn_80031180(void*,f32,f32,f32);
void fn_8024BC80(Actor4BC80* obj) {
 if(MR::isFirstStep(reinterpret_cast<const LiveActor*>(obj))) {
  obj->a8.set<float>(lbl_80648B18[0],lbl_807DC6C0+lbl_80648B18[1],lbl_80648B18[2]);
  fn_80031180(obj,lbl_80648B24[0],lbl_807DC6C0+lbl_80648B18[1],lbl_80648B24[2]);
  obj->up.x=lbl_807DC6B4;obj->up.y=lbl_807DC6B0;obj->up.z=lbl_807DC6B4;
 }
}
}
