#include <revolution.h>
struct View47CD0 { u8 opaque[0x1c]; s32 count; void* groups[32]; };
extern "C" { void fn_80248D30(void*,void*);void fn_802490F0(void*,void*); }
extern "C" void fn_80247CD0(View47CD0* obj,void* item,s32 index) {
 fn_80248D30(obj->groups[index],item);++obj->count;
}
extern "C" void fn_80247D20(View47CD0* obj,void* item,s32 index) {
 fn_802490F0(obj->groups[index],item);--obj->count;
}
