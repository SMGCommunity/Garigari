#include <revolution.h>
struct Record50120 { u8 opaque[0x10]; };
struct Actor50120 { u8 opaque0[0xc4]; Record50120* records; u8* values; };
extern "C" {
void fn_804D60D0(void*, s32);
u8 fn_804DF0E0(const void*);
void fn_802501E0(Actor50120*);
void fn_80250120(Actor50120* obj) {
    for (s32 i = 0; i < 3; ++i) fn_804D60D0(&obj->records[i], i + 1);
    fn_802501E0(obj);
}
void fn_80250180(Actor50120* obj) {
    for (s32 i = 0; i < 3; ++i) fn_804D60D0(&obj->records[i], i + 1);
    fn_802501E0(obj);
}
void fn_802501E0(Actor50120* obj) {
    for (s32 i = 0; i < 3; ++i) obj->values[i] = fn_804DF0E0(&obj->records[i]);
}
}
