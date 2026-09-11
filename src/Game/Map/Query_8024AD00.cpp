#include <JGeometry/TMatrix.hpp>
struct Item4AD00 { u8 opaque[0x34];TMtx34f current;u8 pad[0x60];void* helper;void* sensor; };
struct Hit4AD00 { u8 triangle[0x60];f32 distance;TVec3f position,normal,shift;u8 flag,pad[3]; };
struct Predicate4AD00 { virtual bool test(const Hit4AD00*)=0; };
extern "C" {
u32 fn_80257B50(void*,const TVec3f&,s32,void**,f32*,u8*,f32,f32);
void fn_8024B070(void*,TVec3f*,void*,u8);
u32 fn_80259A10(void*,void*);
void fn_80256AB0(void*,void*,u32,void*);
const TVec3f* fn_80256CD0(void*);
void fn_8000D770(TVec3f*,const TVec3f*,f32);
extern const f32 lbl_807DC69C;
s32 fn_8024AD00(Item4AD00* obj,Hit4AD00* output,s32 capacity,const TVec3f& point,const TVec3f& shift,void** hits,f32* distances,u8* types,Predicate4AD00* predicate,const TVec3f* direction,f32 radius,f32 factor,f32 reciprocal) {
 u32 count=fn_80257B50(obj->helper,point,capacity,hits,distances,types,radius,factor);
 const TVec3f* normal;
 s32 accepted=0;
 for(u32 i=0;i<count;++i,++types) {
  Hit4AD00* out=output+accepted;
  TVec3f local(point);
  fn_8024B070(obj,&local,hits[i],*types);
  obj->current.mult(local,out->position);
  fn_80256AB0(out,obj,fn_80259A10(obj->helper,hits[i]),obj->sensor);
  if(predicate&&predicate->test(out))continue;
  if(direction&&lbl_807DC69C<direction->dot(*fn_80256CD0(out)))continue;
  out->distance=reciprocal*distances[i];
  out->flag=*types;
  out->shift.set<f32>(shift);
  normal=fn_80256CD0(out);
  fn_8000D770(&out->shift,normal,normal->dot(out->shift));
  ++accepted;
 }
 return accepted;
}
}
