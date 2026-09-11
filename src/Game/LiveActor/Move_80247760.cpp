#include "LiveActor/LiveActor.hpp"
#include "Util/LiveActorUtil.hpp"
extern "C" {
extern const char lbl_806964F8[];
extern const f32 lbl_80648AF8[3];
void fn_80051590(TMtx34f*,const char*);
TVec3f* fn_80044550(TVec3f*,const void*);
void fn_80037060(TVec3f*,const TVec3f*,const TVec3f*);
void fn_80011BB0(TVec3f*,f32);f32 PSVECMag(const Vec*);f32 PSVECDistance(const Vec*,const Vec*);
bool fn_80009990(void*,f32);void fn_8000DBB0(TVec3f*);
extern const f32 lbl_807DC678,lbl_807DC640,lbl_807DC664,lbl_807DC634;
extern const u32 lbl_807D34E4;
}
extern "C" void fn_80247760(LiveActor* obj) {
 if(MR::isLessStep(obj,300))return;
 TMtx34f matrix;fn_80051590(&matrix,lbl_806964F8);
 TVec3f point;
 TVec3f delta;
 TVec3f temp;
 matrix.mult(*fn_80044550(&temp,lbl_80648AF8),point);
 fn_80037060(&delta,&point,&obj->mPosition);
 fn_80011BB0(&delta,lbl_807DC678);
 obj->mVelocity.add(delta);
 if(lbl_807DC640<PSVECMag(&obj->mVelocity))fn_80011BB0(&obj->mVelocity,lbl_807DC640);
 if(PSVECDistance(&obj->mPosition,&point)<lbl_807DC664 && fn_80009990(obj,lbl_807DC634)) {
  fn_8000DBB0(&obj->mVelocity);
  obj->setNerve(reinterpret_cast<const Nerve*>(&lbl_807D34E4));
 }
}
