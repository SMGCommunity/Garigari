#include <JGeometry/TVec.hpp>

struct Item48950 { u8 opaque[0x40]; f32 x; u8 pad44[0xc]; f32 y; u8 pad54[0xc]; f32 z; u8 pad64[0x68]; bool active; u8 pad[0xb]; f32 radius; };
struct Group48950 { u32 opaque; Item48950* items[512]; s32 count; TVec3f center; f32 radius; TVec3f low,high; };
struct Record48950 { u8 opaque[0x60]; };
struct View48950 { u8 opaque[0x14]; Record48950* records; s32 result; u32 value1C; Group48950* groups[32]; s32 count; };
struct Predicate48950 { virtual bool test(Item48950*)=0; };
extern "C" {
void fn_80040510(const TVec3f*,const TVec3f*,TVec3f*,TVec3f*);
void fn_80249F20(View48950*);
bool fn_80248AB0(View48950*,const TVec3f*,const TVec3f*,const TVec3f*,f32);
TVec3f fn_80248010(const Item48950*);
u32 fn_8024B780(Item48950*,Record48950*,u32,const TVec3f*,const TVec3f*);
}
extern "C" u32 fn_80248950(View48950* obj,Record48950* records,u32 capacity,const TVec3f* a,const TVec3f* b) {
 fn_80249F20(obj);
 u32 total=0;
 TVec3f low,high;
 fn_80040510(a,b,&low,&high);
 Group48950** group=obj->groups;
 for(;group!=obj->groups+obj->count;++group) {
  if(group!=obj->groups && !fn_80248AB0(obj,&low,&high,&(*group)->center,(*group)->radius))continue;
  s32 count=(*group)->count;
  Item48950* item;
  for(s32 i=0;i<count;++i) {
   item=(*group)->items[i];
   if(!item->active)continue;
   f32 radius=item->radius;
   TVec3f center=fn_80248010(item);
   if(!fn_80248AB0(obj,&low,&high,&center,radius))continue;
   total+=fn_8024B780(item,records+total,capacity-total,a,b);
   if(capacity<=total)return total;
  }
 }
 return total;
}
