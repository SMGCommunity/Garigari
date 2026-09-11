#include <JGeometry/TVec.hpp>

struct Item48020 { u8 opaque[0x40]; f32 x; u8 pad44[0xc]; f32 y; u8 pad54[0xc]; f32 z; u8 pad64[0x68]; bool active; u8 pad[0xb]; f32 radius; };
struct Group48020 { u32 opaque; Item48020* items[512]; s32 count; TVec3f center; f32 radius; TVec3f low,high; };
struct Record48020 { u8 opaque[0x8c]; };
struct View48020 { u8 opaque[0x14]; Record48020* records; s32 result; u32 value1C; Group48020* groups[32]; s32 count; };
struct Predicate48020 { virtual bool test(Item48020*)=0; };
extern "C" {
f32 __fabsf(f32);
void fn_80249F20(View48020*);
bool fn_80248AB0(View48020*,const TVec3f*,const TVec3f*,const TVec3f*,f32);
f32 fn_8000E240(const TVec3f*);
TVec3f fn_80248010(const Item48020*) NO_INLINE;
s32 fn_8024AA30(Item48020*,Record48020*,s32,const TVec3f*,void*,void*,f32);

}
extern "C" s32 fn_80248020(View48020* obj,const TVec3f* point,void* argument,Predicate48020* predicate,void* last,f32 extraRadius) {
 fn_80249F20(obj);
 s32 total;
 Group48020** group=obj->groups;
 obj->result=0;
 total=0;
 s32 i;

 for(;group!=obj->groups+obj->count;++group) {
  if(group!=obj->groups) {
   if(!fn_80248AB0(obj,&(*group)->low,&(*group)->high,point,extraRadius))continue;
   f32 radius=extraRadius+(*group)->radius;
   TVec3f delta((*group)->center);delta-=*point;
   if(radius*radius<fn_8000E240(&delta))continue;
  }
  s32 count=(*group)->count;
  for(i=0;i<count;++i) {
   Item48020* item=(*group)->items[i];
   if(!item->active)continue;
   if(predicate && predicate->test(item))continue;
   f32 radius=extraRadius+item->radius;
   TVec3f delta;
   delta.x=__fabsf(fn_80248010(item).x-point->x);
   if(radius<delta.x)continue;
   delta.y=__fabsf(fn_80248010(item).y-point->y);
   if(radius<delta.y)continue;
   delta.z=__fabsf(fn_80248010(item).z-point->z);
   if(radius<delta.z)continue;
   if(fn_8000E240(&delta)>radius*radius)continue;
   total+=fn_8024AA30(item,obj->records+total,32-total,point,argument,last,extraRadius);
   if(total>=32) { obj->result=total;return total; }
  }
 }
 obj->result=total;
 return total;
}
