#include <revolution.h>
struct View47D70 { u8 opaque[0x1c]; s32 count; void* group; };
extern "C" { void fn_80248D30(void*,void*);void fn_802490F0(void*,void*); }
extern "C" void fn_80247D70(View47D70* obj,void* item) { fn_80248D30(obj->group,item);++obj->count; }
extern "C" void fn_80247DB0(View47D70* obj,void* item) { fn_802490F0(obj->group,item);--obj->count; }
