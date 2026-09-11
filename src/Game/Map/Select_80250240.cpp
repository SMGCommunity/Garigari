#include <revolution.h>
struct Candidate50240 { u8 opaque0[0x144]; s32 value144; };
struct Actor50240 { u8 opaque0[0xa4]; void* childA4; u8 opaqueA8[0x14]; Candidate50240* current; };
extern "C" {
bool fn_8045E990(const void*);
bool fn_8045E9C0(const void*);
void fn_80250240(Actor50240* obj, Candidate50240* candidate) {
    if (fn_8045E990(obj->childA4) || !fn_8045E9C0(obj->childA4)) {
        if (obj->current) {
            if (obj->current->value144 > candidate->value144) obj->current = candidate;
        } else obj->current = candidate;
    }
}
}
