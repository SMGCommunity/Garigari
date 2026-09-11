#include <JGeometry/TVec.hpp>

struct Item47DF0 { u8 opaque[0x40]; f32 x; u8 pad44[0xc]; f32 y; u8 pad54[0xc]; f32 z; u8 pad64[0x68]; bool active; u8 pad[0xb]; f32 radius; };
struct Group47DF0 { u32 opaque; Item47DF0* items[512]; s32 count; TVec3f center; f32 radius; TVec3f low,high; };
struct View47DF0 { u8 opaque[0x18]; s32 result; u32 value1C; Group47DF0* groups[32]; s32 count; };
struct Predicate47DF0 { virtual bool test(Item47DF0*)=0; };
extern "C" {
f32 __fabsf(f32);
void fn_80249F20(View47DF0*);
bool fn_80248AB0(View47DF0*,const TVec3f*,const TVec3f*,const TVec3f*,f32);
f32 fn_8000E240(const TVec3f*);
TVec3f fn_80248010(const Item47DF0*) NO_INLINE;
bool fn_8024A880(Item47DF0*,void*,const TVec3f*,void*);
extern const f32 lbl_807DC688;
}
extern "C" s32 fn_80247DF0(View47DF0* obj,const TVec3f* point,void* argument,Predicate47DF0* predicate,void* last) {
 fn_80249F20(obj);
 Group47DF0** group=obj->groups;
 obj->result=0;

 for(;group!=obj->groups+obj->count;++group) {
  if(group!=obj->groups) {
   if(!fn_80248AB0(obj,&(*group)->low,&(*group)->high,point,lbl_807DC688))continue;
   f32 radius=(*group)->radius;
   TVec3f delta((*group)->center);delta-=*point;
   if(radius*radius<fn_8000E240(&delta))continue;
  }
  s32 count=(*group)->count;
  Item47DF0* item;
  for(s32 i=0;i<count;++i) {
   item=(*group)->items[i];
   if(!item->active)continue;
   if(predicate && predicate->test(item))continue;
   f32 radius=item->radius;
   TVec3f delta;
   delta.x=__fabsf(fn_80248010(item).x-point->x);
   if(radius<delta.x)continue;
   delta.y=__fabsf(fn_80248010(item).y-point->y);
   if(radius<delta.y)continue;
   delta.z=__fabsf(fn_80248010(item).z-point->z);
   if(radius<delta.z)continue;
   if(fn_8000E240(&delta)>radius*radius)continue;
   if(fn_8024A880(item,argument,point,last)) { obj->result=1;return 1; }
  }
 }
 return obj->result;
}

extern "C" TVec3f fn_80248010(const Item47DF0* item) {
 f32 z=item->z,y=item->y,x=item->x;
 TVec3f result;result.set<f32>(x,y,z);return result;
}
