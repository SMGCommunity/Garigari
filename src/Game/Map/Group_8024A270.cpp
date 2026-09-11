#include <revolution.h>
struct Group4A270 { s32 index; };
struct Item4A270 { u8 opaque[0xe0];s32 category;Group4A270* group; };
struct Director4A270 { u8 base[0x14];void** holders; };
extern "C" {
Director4A270* fn_80249F20();
void fn_80247CD0(void*,void*,s32);
void fn_80247D20(void*,void*,s32);
void fn_8024A270(Item4A270* obj) {
 s32 category=obj->category;
 // Preserve the retail index snapshot before the director lookup.
 s32 index=static_cast<const volatile Group4A270*>(obj->group)->index;
 fn_80247CD0(fn_80249F20()->holders[category],obj,index);
}
void fn_8024A2D0(Item4A270* obj) {
 s32 category=obj->category;
 // Preserve the retail index snapshot before the director lookup.
 s32 index=static_cast<const volatile Group4A270*>(obj->group)->index;
 fn_80247D20(fn_80249F20()->holders[category],obj,index);
}
}
