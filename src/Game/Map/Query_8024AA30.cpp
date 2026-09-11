#define JGEOMETRY_OUTLINE_VEC3_ADD
#include <JGeometry/TMatrix.hpp>
struct Item4AA30 { u8 base[0x34];TMtx34f current,inverse,previous;u8 pad[0x10];s32 count; };
extern "C" {
f32 PSVECMag(const Vec*);
void fn_8024A1C0(const TMtx34f*,TVec3f*);
void fn_8006FCA0(const TMtx34f*,const TVec3f*,TVec3f*);
s32 fn_8024AD00(void*,void*,s32,const TVec3f&,const TVec3f&,void*,void*,void*,void*,const TVec3f*,f32,f32,f32);
extern const f32 lbl_807DC698,lbl_807DC69C,lbl_807DC6A0,lbl_807DC6AC;
inline TVec3f difference4AA30(const TVec3f& a,const TVec3f& b) ALWAYS_INLINE { TVec3f result(a);result.sub(b);return result; }
inline TVec3f sum4AA30(const TVec3f& a,const TVec3f& b) ALWAYS_INLINE { TVec3f result(a);result.add(b);return result; }
s32 fn_8024AA30(Item4AA30* obj,void* output,s32 capacity,const TVec3f& point,bool moving,void* predicate,f32 radius) {
 u32 a[64],b[64],c[16];
 TMtx34f previousInverse;
 TVec3f local,scale;
 obj->inverse.mult(point,local);
 fn_8024A1C0(&obj->inverse,&scale);
 f32 factor=(scale.x+scale.y+scale.z)/lbl_807DC6A0;
 f32 reciprocal=lbl_807DC698/factor;
 radius*=factor;
 TVec3f shift(0,0,0);
 if(moving&&obj->count==0) {
  PSMTXInverse(obj->previous.mMtx,previousInverse.mMtx);
  TVec3f old;
  previousInverse.mult(point,old);
  TVec3f delta=difference4AA30(local,old);
  TVec3f worldDelta(delta);
  fn_8006FCA0(&obj->current,&worldDelta,&worldDelta);
  const TVec3f* extra;
  s32 steps=static_cast<s32>(lbl_807DC6AC*PSVECMag(reinterpret_cast<const Vec*>(&delta)))+1;
  TVec3f step(delta);
  if(steps>1)step.scale(lbl_807DC698/steps);
  TVec3f offset;offset.z=lbl_807DC69C;offset.y=lbl_807DC69C;offset.x=lbl_807DC69C;
  for(s32 i=0;i<=steps;++i) {
   shift.set<f32>(-difference4AA30(delta,offset));
   fn_8006FCA0(&obj->current,&shift,&shift);
   extra=&worldDelta;
   if(i==steps)extra=0;
   s32 result=fn_8024AD00(obj,output,capacity,sum4AA30(old,offset),shift,a,b,c,predicate,extra,radius,factor,reciprocal);
   if(result)return result;
   offset.add(step);
  }
  return false;
 }
 return fn_8024AD00(obj,output,capacity,local,TVec3f(0,0,0),a,b,c,predicate,0,radius,factor,reciprocal);
}
}
