#include "LiveActor/LiveActor.hpp"
struct Actor4BD20 { u8 opaque[0x14];TVec3f position;u8 pad[0x70];TVec3f target;u8 pad2[0xc];TVec3f a8,b4;f32 c0,c4;TVec3f up; };
namespace MR { bool isFirstStep(const LiveActor*); }
extern "C" {
extern const u8 lbl_80648B18[],lbl_80648B24[];
extern const f32 lbl_807DC6B4,lbl_807DC6B0,lbl_807DC6B8,lbl_807DC6BC;
extern u32 lbl_807D34F8;
TVec3f* fn_80044550(TVec3f*,const void*);
void fn_80037060(TVec3f*,const TVec3f*,const TVec3f*);
void fn_80023780(TVec3f*,const TVec3f*,f32);
void fn_80033750(void*,const void*,s32);
void fn_8024BD20(Actor4BD20* obj) {
 TVec3f scaledA,differenceA,constantA,scaledB,differenceB,constantB;
 LiveActor* actor=reinterpret_cast<LiveActor*>(obj);
 if(MR::isFirstStep(actor)) {
  obj->up.x=lbl_807DC6B4;obj->up.y=lbl_807DC6B0;obj->up.z=lbl_807DC6B4;
 }
 f32 factor=actor->getNerveStep()/lbl_807DC6B8;factor*=factor;
 fn_80037060(&differenceA,fn_80044550(&constantA,lbl_80648B18),&obj->a8);
 fn_80023780(&scaledA,&differenceA,factor);obj->a8.add(scaledA);
 obj->c0+=factor*(lbl_807DC6BC-obj->c0);
 fn_80037060(&differenceB,fn_80044550(&constantB,lbl_80648B24),&obj->position);
 fn_80023780(&scaledB,&differenceB,factor);obj->position.add(scaledB);
 fn_80033750(obj,&lbl_807D34F8,60);
}
}

extern "C" {
void fn_80031170(void*,const TVec3f*);
extern const u8 lbl_80648B3C[];
extern const f32 lbl_807DC6C4;
extern u32 lbl_807D3500;
void fn_8024BE50(Actor4BD20* obj) {
 TVec3f a,b;
 obj->up.x=lbl_807DC6B4;obj->up.y=lbl_807DC6B0;obj->up.z=lbl_807DC6B4;
 obj->a8=*fn_80044550(&a,lbl_80648B18);
 obj->c0=lbl_807DC6BC;
 fn_80031170(obj,fn_80044550(&b,lbl_80648B24));
}
inline TVec3f constant4BED0(const void* data) ALWAYS_INLINE { TVec3f v;fn_80044550(&v,data);return v; }
inline TVec3f difference4BED0(const TVec3f& a,const TVec3f& b) ALWAYS_INLINE { TVec3f v;fn_80037060(&v,&a,&b);return v; }
inline TVec3f scaled4BED0(const TVec3f& a,f32 f) ALWAYS_INLINE { TVec3f v;fn_80023780(&v,&a,f);return v; }
void fn_8024BED0(Actor4BD20* obj) {
 TVec3f target(obj->target.addInline(constant4BED0(lbl_80648B3C)));
 f32 factor=reinterpret_cast<LiveActor*>(obj)->getNerveStep()/lbl_807DC6B8;factor*=factor;
 obj->a8.add(scaled4BED0(difference4BED0(obj->target,obj->a8),factor));
 obj->c0+=factor*(lbl_807DC6C4-obj->c0);
 obj->position.add(scaled4BED0(difference4BED0(target,obj->position),factor));
 fn_80033750(obj,&lbl_807D3500,60);
}
}
