#include <JGeometry/TVec.hpp>

struct Item48790 { u8 opaque[0x40]; f32 x; u8 pad44[0xc]; f32 y; u8 pad54[0xc]; f32 z; u8 pad64[0x68]; bool active; u8 pad[0xb]; f32 radius; };
struct Group48790 { u32 opaque; Item48790* items[512]; s32 count; TVec3f center; f32 radius; TVec3f low,high; };
struct Record48790 { u8 opaque[0x60]; };
struct View48790 { u8 opaque[0x14]; Record48790* records; s32 result; u32 value1C; Group48790* groups[32]; s32 count; };
struct Predicate48790 { virtual bool test(Item48790*)=0; };
extern "C" {
void fn_80249F20(View48790*);
bool fn_80248AB0(View48790*,const TVec3f*,const TVec3f*,const TVec3f*,f32);
TVec3f fn_80248010(const Item48790*);
u32 fn_8024B690(Item48790*,Record48790*,u32,const TVec3f*,const TVec3f*);
}
extern "C" u32 fn_80248790(View48790* obj,Record48790* records,u32 capacity,const TVec3f* a,const TVec3f* b) {
 fn_80249F20(obj);
 u32 total=0;
 TVec3f low,high;
 if(a->x<b->x) {low.x=a->x;high.x=b->x;} else {low.x=b->x;high.x=a->x;}
 if(a->y<b->y) {low.y=a->y;high.y=b->y;} else {low.y=b->y;high.y=a->y;}
 if(a->z<b->z) {low.z=a->z;high.z=b->z;} else {low.z=b->z;high.z=a->z;}
 Group48790** group=obj->groups;
 for(;group!=obj->groups+obj->count;++group) {
  if(group!=obj->groups && !fn_80248AB0(obj,&low,&high,&(*group)->center,(*group)->radius))continue;
  s32 count=(*group)->count;
  Item48790* item;
  for(s32 i=0;i<count;++i) {
   item=(*group)->items[i];
   if(!item->active)continue;
   f32 radius=item->radius;
   TVec3f center=fn_80248010(item);
   if(!fn_80248AB0(obj,&low,&high,&center,radius))continue;
   total+=fn_8024B690(item,records+total,capacity-total,a,b);
   if(capacity<=total)return total;
  }
 }
 return total;
}
