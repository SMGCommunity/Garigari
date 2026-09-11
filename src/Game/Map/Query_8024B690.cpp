#include <JGeometry/TMatrix.hpp>
struct Item4B690 { u8 opaque[0x64];TMtx34f inverse;u8 pad[0x30];void* helper;void* sensor; };
struct Triangle4B690 { u8 opaque[0x60]; };
extern "C" {
void fn_805C7D30(const TMtx34f*,TPos3f*);
u32 fn_80257780(void*,const TVec3f*,const TVec3f*,void**,s32);
u32 fn_80259A10(void*,void*);
void fn_80256AB0(void*,void*,u32,void*);
u32 fn_8024B690(Item4B690* obj,Triangle4B690* output,s32 capacity,const TVec3f& a,const TVec3f& b) {
 void* hits[512];TPos3f matrix;TVec3f localA,localB;
 fn_805C7D30(&obj->inverse,&matrix);
 matrix.zeroTrans();
 obj->inverse.mult(a,localA);
 obj->inverse.mult(b,localB);
 u32 count=fn_80257780(obj->helper,&localA,&localB,hits,capacity);
 if(!count)return 0;
 for(u32 i=0;i<count;++i) {
  fn_80256AB0(output+i,obj,fn_80259A10(obj->helper,hits[i]),obj->sensor);
 }
 return count;
}
}
