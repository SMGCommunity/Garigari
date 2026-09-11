#include <revolution.h>
struct View43580 { void* first; s32 count; void* third; void* fourth; void** entries; };
struct Item43600 { u8 opaque[0x12]; s16 index; };
extern "C" View43580* fn_80243580(View43580* obj) {
 obj->first=0; obj->count=0; obj->third=0; obj->fourth=0; obj->entries=0;
 obj->entries=new void*[256];
 for(int i=0;i<256;i++)obj->entries[i]=0;
 return obj;
}
extern "C" void fn_80243600(View43580* obj, Item43600* item, s32 index) {
 item->index=index;
 if(index>=obj->count)obj->count=index+1;
}
