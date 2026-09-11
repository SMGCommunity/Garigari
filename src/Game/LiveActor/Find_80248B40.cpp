#include <revolution.h>
struct Value48B40 { u8 opaque[0x24]; void* key; };
struct Item48B40 { u8 opaque[0xc8]; Value48B40* value; };
struct Group48B40 { u32 opaque; Item48B40* items[512]; s32 count; };
struct View48B40 { u8 opaque[0x20]; Group48B40* groups[32]; s32 count; };
extern "C" bool fn_80248B40(View48B40* obj,Item48B40** output,const Item48B40* target) {
 for(Group48B40** group=obj->groups;group!=obj->groups+obj->count;++group) {
  s32 count=(*group)->count;
  for(s32 i=0;i<count;++i) {
   Item48B40* item=(*group)->items[i];
   if(item->value->key==target->value->key) { *output=item;return true; }
  }
 }
 return false;
}
