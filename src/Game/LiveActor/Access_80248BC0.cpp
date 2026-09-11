#include <revolution.h>
struct Record48BC0 { u8 opaque[0x8c]; };
struct Group48BC0 { u8 opaque[0x830]; };
struct View48BC0 { u8 opaque[0x14]; Record48BC0* records; u8 pad[8]; Group48BC0* groups[32]; s32 count; u32 argument; bool ready; };
extern "C" {
s32 fn_80057C20();
Group48BC0* __ct__10Group48C70Fl(Group48BC0*,s32);
}
extern "C" Record48BC0* fn_80248BC0(View48BC0* obj,s32 index) { return obj->records+index; }
extern "C" Group48BC0* fn_80248BD0(View48BC0* obj,s32 index) {
 if(!obj->ready) {
  s32 count=fn_80057C20();
  for(s32 i=0;i<count;++i) {
   Group48BC0* group=static_cast<Group48BC0*>(::operator new(sizeof(Group48BC0)));
   if(group)group=__ct__10Group48C70Fl(group,i);
   s32 slot=obj->count;
   obj->count=slot+1;
   obj->groups[slot]=group;
  }
  obj->ready=true;
 }
 return obj->groups[index];
}
