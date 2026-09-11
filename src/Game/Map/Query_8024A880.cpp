#define JGEOMETRY_OUTLINE_VEC3_ADD
#include <JGeometry/TMatrix.hpp>
struct Item4A880 { u8 opaque[0x64];TMtx34f inverse;u8 pad[0x30];void* helper;void* sensor; };
struct Triangle4A880 { u8 opaque[0x60]; };
struct Hit4A880 { Triangle4A880 triangle;f32 distance;TVec3f position; };
struct Predicate4A880 { virtual bool test(const Triangle4A880*)=0; };
extern "C" {
void fn_8024A1C0(const TMtx34f*,TVec3f*);
void* fn_80257470(void*,const TVec3f*,f32*,f32);
void fn_80256A30(Triangle4A880*);
u32 fn_80259A10(void*,void*);
void fn_80256AB0(void*,void*,u32,void*);
const TVec3f* fn_80256CC0(void*,int);
extern const f32 lbl_807DC6A0;
inline TVec3f scaled4A880(const TVec3f& v,f32 factor) ALWAYS_INLINE { TVec3f result(v);result.scale(factor);return result; }
inline TVec3f sum4A880(const TVec3f& v,const TVec3f& b) ALWAYS_INLINE { TVec3f result(v);result.add(b);return result; }
bool fn_8024A880(Item4A880* obj,Hit4A880* output,const TVec3f& point,Predicate4A880* predicate) {
 TVec3f local,scale;
 obj->inverse.mult(point,local);
 fn_8024A1C0(&obj->inverse,&scale);
 f32 y=__fabsf(scale.y),x=__fabsf(scale.x),z=__fabsf(scale.z);
 f32 factor=lbl_807DC6A0/(x+y+z);
 TVec3f query;query.x=local.x;query.y=local.y;query.z=local.z;
 f32 distance;
 void* hit=fn_80257470(obj->helper,&query,&distance,factor);
 if(!hit)return false;
 if(predicate) {
  Triangle4A880 triangle;
  fn_80256A30(&triangle);
  fn_80256AB0(&triangle,obj,fn_80259A10(obj->helper,hit),obj->sensor);
  if(predicate&&predicate->test(&triangle))return false;
 }
 if(output) {
  fn_80256AB0(output,obj,fn_80259A10(obj->helper,hit),obj->sensor);
  factor=distance*factor;
  output->distance=factor;
  output->position=sum4A880(point,scaled4A880(*fn_80256CC0(output,0),factor));
 }
 return true;
}
}
