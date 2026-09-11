#include "LiveActor/LiveActor.hpp"
#include "Util/MathUtil.hpp"
#include <JMath/JMath.hpp>
struct View46C40 : LiveActor { u8 opaque[12]; f32 x,y,z,w; };
extern "C" {
f32 PSVECMag(const Vec*);
extern const f32 lbl_807DC640,lbl_807DC630,lbl_807DC638,lbl_807DC650,lbl_807DC654,lbl_807DC658;
void fn_8002B390(void*,TVec3f*,void*,void*);
void fn_8003CEB0(void*,const TVec3f*,const TVec3f*,f32);
void fn_80010480(void*);
bool fn_8003F1A0(const TVec3f*,f32);
void fn_8003E8C0(TVec3f*,const TVec3f*,const TVec3f*,const TVec3f*,f32,f32);
void fn_805C8C70(const void*,const void*,void*);
}
extern "C" void fn_80246C40(View46C40* obj) {
 TVec3f v;fn_8002B390(obj,&v,0,0);
 TVec3f a,b;
 a.set<f32>(lbl_807DC640*(obj->x*obj->y)-lbl_807DC640*(obj->w*obj->z),
 lbl_807DC630-lbl_807DC640*(obj->x*obj->x)-lbl_807DC640*(obj->z*obj->z),
 lbl_807DC640*(obj->y*obj->z)+lbl_807DC640*(obj->w*obj->x));
 b.set<f32>(lbl_807DC640*(obj->x*obj->z)+lbl_807DC640*(obj->w*obj->y),
 lbl_807DC640*(obj->y*obj->z)-lbl_807DC640*(obj->w*obj->x),
 lbl_807DC630-lbl_807DC640*(obj->x*obj->x)-lbl_807DC640*(obj->y*obj->y));
 const TVec3f& neg=-v;
 f32 q[4];fn_8003CEB0(q,&a,&neg,lbl_807DC630);
 TVec3f vel(obj->mVelocity);
 if(PSVECMag(&vel)<lbl_807DC638) { fn_80010480(&obj->x);return; }
 MR::vecKillElement(vel,v,&vel);
 if(fn_8003F1A0(&vel,lbl_807DC650)) { fn_80010480(&obj->x);return; }
 MR::normalize(&vel);
 TVec3f projected;
 JMAVECScaleAdd(&a,&vel,&projected,-a.dot(vel));
 MR::normalizeOrZero(&projected);
 if(!fn_8003F1A0(&projected,lbl_807DC650)) {
  TVec3f next;
  fn_8003E8C0(&next,&b,&projected,&a,lbl_807DC654,lbl_807DC658);
  f32 q2[4];fn_8003CEB0(q2,&b,&next,lbl_807DC630);
  fn_805C8C70(q2,&obj->x,&obj->x);
 }
 fn_80010480(&obj->x);
}
