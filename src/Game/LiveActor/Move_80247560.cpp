#include "LiveActor/LiveActor.hpp"
struct View47560 : LiveActor { TVec3f position90; };
extern "C" {
bool fn_80246FE0(void*);bool fn_8005D3A0(void**);
f32 PSVECDistance(const Vec*,const Vec*);f32 PSVECMag(const Vec*);
void fn_8005D510(TVec3f*,const TVec3f*,void*);
void fn_80037060(TVec3f*,const TVec3f*,const TVec3f*);
void fn_80011BB0(TVec3f*,f32);
f32 fn_80032470(void*);f32 fn_80247480(f32,f32,f32);void fn_8000A550(void*,f32);
extern const f32 lbl_807DC660,lbl_807DC678,lbl_807DC67C,lbl_807DC680,lbl_807DC658;
extern const u32 lbl_807D34D0;
}
extern "C" void fn_80247560(View47560* obj) {
 if(fn_80246FE0(obj))return;
 void* target=0;
 if(!fn_8005D3A0(&target)) { obj->setNerve(reinterpret_cast<const Nerve*>(&lbl_807D34D0));return; }
 if(lbl_807DC660<PSVECDistance(&obj->mPosition,&obj->position90)) { obj->setNerve(reinterpret_cast<const Nerve*>(&lbl_807D34D0));return; }
 TVec3f point;fn_8005D510(&point,&obj->mPosition,target);
 TVec3f delta;fn_80037060(&delta,&point,&obj->mPosition);
 obj->mVelocity.add(delta.scaleInline(lbl_807DC678));
 if(lbl_807DC67C<PSVECMag(&obj->mVelocity))fn_80011BB0(&obj->mVelocity,lbl_807DC67C);
 fn_8000A550(obj,fn_80247480(fn_80032470(obj),lbl_807DC680,lbl_807DC658));
}
