#include "LiveActor/LiveActor.hpp"
#include "Util/LiveActorUtil.hpp"
#include "Util/MathUtil.hpp"
struct View47340 : LiveActor { TVec3f position90; };
extern "C" {
bool fn_80246FE0(void*);bool fn_80247130(void*);bool fn_80247220(void*);
f32 fn_80032470(void*);
f32 fn_80247480(f32,f32,f32) NO_INLINE;
void fn_8000A550(void*,f32);
void fn_80037060(TVec3f*,const TVec3f*,const TVec3f*);
bool fn_8003F1A0(const TVec3f*,f32);
f32 PSVECMag(const Vec*);f32 PSVECDistance(const Vec*,const Vec*);
void fn_80011BB0(TVec3f*,f32);
extern const f32 lbl_807DC630,lbl_807DC658,lbl_807DC66C,lbl_807DC650,lbl_807DC670,lbl_807DC640,lbl_807DC64C;
}
extern "C" void fn_80247340(View47340* obj) {
 if(fn_80246FE0(obj))return;
 if(fn_80247130(obj))return;
 if(fn_80247220(obj))return;
 fn_8000A550(obj,fn_80247480(fn_80032470(obj),lbl_807DC630,lbl_807DC658));
 obj->mVelocity.x*=lbl_807DC66C;obj->mVelocity.y*=lbl_807DC66C;obj->mVelocity.z*=lbl_807DC66C;
 TVec3f v;fn_80037060(&v,&obj->position90,&obj->mPosition);
 if(fn_8003F1A0(&v,lbl_807DC650))return;
 MR::normalize(&v);
 obj->mVelocity.add(v.scaleInline(lbl_807DC670));
 if(lbl_807DC640<PSVECMag(&obj->mVelocity))fn_80011BB0(&obj->mVelocity,lbl_807DC640);
 if(MR::isInvalidClipping(obj) && PSVECDistance(&obj->position90,&obj->mPosition)<lbl_807DC64C)MR::validateClipping(obj);
}
extern "C" f32 fn_80247480(f32 value,f32 target,f32 step) {
 if(value<target) { value+=step;if(value>target)value=target; }
 else { value-=step;if(value<target)value=target; }
 return value;
}
