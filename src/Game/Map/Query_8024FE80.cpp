#include <revolution.h>
struct Actor4FE80 { u8 opaque0[0xa0]; void* childA0; void* childA4; u8 opaqueA8[0x18]; void* childC0; };
extern "C" {
bool fn_800308A0(const void*);
bool fn_8045E990(const void*);
bool fn_8024FE80(const Actor4FE80* obj) {
    return fn_800308A0(obj->childA0) && fn_800308A0(obj->childC0) && fn_8045E990(obj->childA4);
}
}
