#include <revolution.h>
struct Actor4FDF0 { u8 opaque0[0xa0]; void* childA0; void* childA4; u8 opaqueA8[0x18]; void* childC0; };
extern "C" {
bool fn_800308A0(const void*);
void fn_8046D140(void*);
void fn_8046DB00(void*);
void fn_8046D9E0(void*);
bool fn_8045E990(const void*);
void fn_8045E960(void*);
void fn_8024FDF0(Actor4FDF0* obj) {
    if (!fn_800308A0(obj->childA0)) {
        fn_8046D140(obj->childA0);
        if (!fn_800308A0(obj->childC0)) fn_8046DB00(obj->childC0);
    }
    if (!fn_800308A0(obj->childC0)) fn_8046D9E0(obj->childC0);
    if (!fn_8045E990(obj->childA4)) fn_8045E960(obj->childA4);
}
}
