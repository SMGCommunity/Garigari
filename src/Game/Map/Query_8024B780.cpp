#include <JGeometry/TMatrix.hpp>
struct Item4B780 { u8 opaque[0x64];TMtx34f inverse;u8 pad[0x30];void* helper;void* sensor; };
struct Triangle4B780 { u8 opaque[0x60]; };
extern "C" {
void fn_80040510(const TVec3f*,u32,TVec3f*,TVec3f*);
void fn_805C7D30(const TMtx34f*,TPos3f*);
u32 fn_80257780(void*,const TVec3f*,const TVec3f*,void**,s32);
u32 fn_80259A10(void*,void*);
void fn_80256AB0(void*,void*,u32,void*);
u32 fn_8024B780(Item4B780* obj,Triangle4B780* output,s32 capacity,const TVec3f* input,u32 inputCount) {
 void* hits[512];TVec3f points[32];TPos3f matrix;TVec3f localA,localB;
 fn_805C7D30(&obj->inverse,&matrix);
 matrix.zeroTrans();
 for(u32 i=0;i<inputCount;++i)obj->inverse.mult(input[i],points[i]);
 fn_80040510(points,inputCount,&localA,&localB);
 u32 count=fn_80257780(obj->helper,&localA,&localB,hits,capacity);
 if(!count)return 0;
 for(u32 i=0;i<count;++i) {
  fn_80256AB0(output+i,obj,fn_80259A10(obj->helper,hits[i]),obj->sensor);
 }
 return count;
}
}
