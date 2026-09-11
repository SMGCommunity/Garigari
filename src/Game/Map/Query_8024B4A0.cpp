#define JGEOMETRY_OUTLINE_VEC3_ADD
#include <JGeometry/TMatrix.hpp>
struct Item4B4A0 { u8 opaque[0x34];TMtx34f current,inverse,previous;void* helper;void* sensor; };
struct Hit4B4A0 { u8 triangle[0x60];f32 distance;TVec3f position,normal,shift;u8 flag,pad[3]; };
struct Predicate4B4A0 { virtual bool test(const Hit4B4A0*)=0; };
extern "C" {
f32 PSVECMag(const TVec3f*);
void fn_80258100(void*,const TVec3f*,const TVec3f*,f32*,u8*,u32*,void**,s32);
u32 fn_80259A10(void*,void*);
void fn_80256AB0(void*,void*,u32,void*);
s32 fn_8024B4A0(Item4B4A0* obj,Hit4B4A0* output,s32 capacity,const TVec3f& point,const TVec3f& delta,Predicate4B4A0* predicate) {
 f32 distances[64];void* hits[64];u8 types[64];
 TVec3f local,direction;
 f32 length=PSVECMag(&delta);
 obj->inverse.mult(point,local);
 obj->inverse.mult(point.addInline(delta),direction);
 direction=direction.subInline(local);
 u32 count=0;
 fn_80258100(obj->helper,&local,&direction,distances,types,&count,hits,capacity);
 s32 accepted=0;
 for(u32 i=0;i<count;++i) {
  f32 distance=distances[i];
  Hit4B4A0* out=output+accepted;
  TVec3f position(local.addInline(direction.scaleInline(distance)));
  obj->current.mult(position,position);
  fn_80256AB0(out,obj,fn_80259A10(obj->helper,hits[i]),obj->sensor);
  if(predicate&&predicate->test(out))continue;
  out->distance=length*distances[i];
  out->position=position;
  out->flag=types[i];
  ++accepted;
 }
 return accepted;
}
}
