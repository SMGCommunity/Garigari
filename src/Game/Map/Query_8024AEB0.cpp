#include <JGeometry/TMatrix.hpp>
struct Item4AEB0 { u8 opaque[0x34];TMtx34f current,inverse,previous;void* helper;void* sensor; };
struct Hit4AEB0 { u8 triangle[0x60];f32 distance;TVec3f position,normal,shift;u8 flag,pad[3]; };
struct Predicate4AEB0 { virtual bool test(const Hit4AEB0*)=0; };
extern "C" {
void fn_8024A1C0(const TMtx34f*,TVec3f*);
void fn_8024B070(void*,TVec3f*,void*,u8);
u32 fn_80259A10(void*,void*);
void fn_80256AB0(void*,void*,u32,void*);
extern const f32 lbl_807DC698,lbl_807DC6A0;
u32 fn_80257E20(void*,const TVec3f*,s32,void**,f32*,u8*,f32,f32,f32);
s32 fn_8024AEB0(Item4AEB0* obj,Hit4AEB0* output,s32 capacity,const TVec3f& point,Predicate4AEB0* predicate,f32 radius,f32 argument) {
 void* hits[64];f32 distances[64];u8 types[64];
 TVec3f local,scale;
 obj->inverse.mult(point,local);
 fn_8024A1C0(&obj->inverse,&scale);
 f32 factor=(scale.x+scale.y+scale.z)/lbl_807DC6A0;
 TVec3f query;query.x=local.x;query.y=local.y;query.z=local.z;
 u32 count;
 f32 scaledRadius=radius*factor;
 count=fn_80257E20(obj->helper,&query,capacity,hits,distances,types,scaledRadius,factor,argument);
 factor=lbl_807DC698/factor;
 s32 accepted=0;
 for(u32 i=0;i<count;++i) {
  Hit4AEB0* out=output+accepted;
  TVec3f adjusted(local);
  fn_8024B070(obj,&adjusted,hits[i],types[i]);
  obj->current.mult(adjusted,out->position);
  fn_80256AB0(out,obj,fn_80259A10(obj->helper,hits[i]),obj->sensor);
  if(predicate&&predicate->test(out))continue;
  out->distance=factor*distances[i];out->flag=types[i];
  ++accepted;
 }
 return accepted;
}
}
