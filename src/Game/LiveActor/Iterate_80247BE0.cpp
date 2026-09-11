#include <revolution.h>
struct Item47BE0 { u8 opaque[0xcc]; bool active,flag; u8 pad[6]; void* valueD4; u8 padD8[8]; s32 valueE0; };
struct Group47BE0 { u32 opaque; Item47BE0* items[512]; s32 count; };
struct View47BE0 { u8 opaque[0x20]; Group47BE0* groups[32]; s32 count,valueA4; bool flagA8,flagA9; };
extern "C" {
void fn_8024A4A0(Item47BE0*);
void fn_80248F20(Group47BE0*,Item47BE0*);
void fn_80248D60(Group47BE0*);
}
extern "C" void fn_80247BE0(View47BE0* obj) {
 for(Group47BE0** group=obj->groups;group!=obj->groups+obj->count;++group) {
  s32 count=(*group)->count;
  for(s32 i=0;i<count;++i) {
   Item47BE0* item=(*group)->items[i];
   if(item->active) {
    if(obj->valueA4==item->valueE0)fn_8024A4A0(item);
    if(!item->valueD4 || item->flag) {
     fn_80248F20(*group,item);
     item->flag=false;
    }
   }
  }
  if(obj->flagA9)fn_80248D60(*group);
 }
 obj->flagA9=false;
}

