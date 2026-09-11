#include "LiveActor/LiveActor.hpp"
#include "LiveActor/HitSensor.hpp"
struct View47670 : LiveActor { u8 opaque[0x20]; HitSensor* other; };
extern "C" {
extern const char lbl_806964E4[];
bool fn_8000DF00(const HitSensor*,const HitSensor*,f32);
void fn_8000DBB0(TVec3f*);
f32 fn_80032470(void*);f32 fn_80247480(f32,f32,f32);void fn_8000A550(void*,f32);
void fn_80037060(TVec3f*,const TVec3f*,const TVec3f*);
void fn_80011BB0(TVec3f*,f32);f32 PSVECMag(const Vec*);
bool fn_80246FE0(void*);
extern const f32 lbl_807DC684,lbl_807DC658,lbl_807DC678,lbl_807DC67C,lbl_807DC680;
}
extern "C" void fn_80247670(View47670* obj) {
 HitSensor* sensor=obj->getSensor(lbl_806964E4);
 if(fn_8000DF00(sensor,obj->other,sensor->mRadius+obj->other->mRadius)) {
  fn_8000DBB0(&obj->mVelocity);
  fn_8000A550(obj,fn_80247480(fn_80032470(obj),lbl_807DC684,lbl_807DC658));
 } else {
  TVec3f v;fn_80037060(&v,&obj->other->mOffset,&obj->mPosition);
  fn_80011BB0(&v,lbl_807DC678);
  obj->mVelocity.add(v);
  if(lbl_807DC67C<PSVECMag(&obj->mVelocity))fn_80011BB0(&obj->mVelocity,lbl_807DC67C);
  fn_8000A550(obj,fn_80247480(fn_80032470(obj),lbl_807DC680,lbl_807DC658));
 }
 fn_80246FE0(obj);
}
