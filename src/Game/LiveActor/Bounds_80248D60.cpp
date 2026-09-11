#define JGEOMETRY_INLINE_VEC3_CTOR
#define JGEOMETRY_OUTLINE_VEC3_ADD
#include <JGeometry/TVec.hpp>
struct Item48D60 { u8 opaque[0xd8]; f32 radius; };
struct Group48D60 { s32 index; Item48D60* items[512]; s32 count; TVec3f center; f32 radius; TVec3f low,high; };
extern "C" {
f32 PSVECMag(const Vec*);
void fn_8000DBB0(TVec3f*);
TVec3f fn_80248010(const Item48D60*);
void fn_80249010(Group48D60*,TVec3f,TVec3f);
extern const f32 lbl_807DC688,lbl_807DC68C;
}
inline void copy48D60(const TVec3f& source,TVec3f* dest) ALWAYS_INLINE { JGeometry::setTVec3f(&source.x,&dest->x); }
inline TVec3f midpoint48D60(const TVec3f& high,const TVec3f& low,f32 scale) ALWAYS_INLINE {
 TVec3f sum(high);sum+=low;
 TVec3f result(sum);result.x*=scale;result.y*=scale;result.z*=scale;
 return result;
}
extern "C" void fn_80248D60(Group48D60* obj) {
 Item48D60** second;
 fn_8000DBB0(&obj->low);fn_8000DBB0(&obj->high);obj->radius=lbl_807DC688;
 for(Item48D60** item=obj->items;item!=obj->items+obj->count;++item) {
  TVec3f low=fn_80248010(*item),high=fn_80248010(*item);
  f32 radius=(*item)->radius;
  low-=TVec3f(radius,radius,radius);high+=TVec3f(radius,radius,radius);
  fn_80249010(obj,low,high);
 }
 copy48D60(midpoint48D60(obj->high,obj->low,lbl_807DC68C),&obj->center);
 second=obj->items;
 f32 radius=lbl_807DC688;
 for(;second!=obj->items+obj->count;++second) {
  TVec3f delta=fn_80248010(*second);delta-=obj->center;
  f32 distance=PSVECMag(&delta);distance+=(*second)->radius;
  if(radius<distance)radius=distance;
 }
 obj->radius=radius;
}
