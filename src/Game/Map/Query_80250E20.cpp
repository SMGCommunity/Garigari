#include <revolution.h>
struct Record50E20 { u8 opaque[16]; };
struct Actor50E20 { u8 opaque0[0xc4]; Record50E20* records; };
extern "C" {
bool fn_804DF0C0(const Record50E20*, u32*);
bool fn_804DF0B0(const Record50E20*, u64*);
s32 fn_80559F50(const u64*, u16*);
s32 fn_80559C10(u16);
s32 fn_804DF090(const Record50E20*);
s32 fn_804DF080(const Record50E20*);
u32 fn_80250E20(const Actor50E20* obj, s32 index) {
    u32 value;
    if (fn_804DF0C0(&obj->records[index - 1], &value)) {
        u32 result = 0;
        if (value <= 7) result = value - 1;
        return result;
    }
    return 0;
}
bool fn_80250E80(const Actor50E20* obj, s32 index) {
    u64 identity;
    u16 value;
    if (fn_804DF0B0(&obj->records[index - 1], &identity) && fn_80559F50(&identity, &value) == 1)
        return fn_80559C10(value) == 1;
    return false;
}
u16 fn_80250EF0(const Actor50E20* obj, s32 index) {
    u64 identity;
    u16 value;
    if (fn_804DF0B0(&obj->records[index - 1], &identity) && fn_80559F50(&identity, &value)) return value;
    return 0;
}
bool fn_80250F50(const Actor50E20* obj, s32 index) {
    bool result;
    s32 offset = (index - 1) * 16;
    result = false;
    if (fn_804DF090(reinterpret_cast<const Record50E20*>(reinterpret_cast<const u8*>(obj->records) + offset)) >= 120 && fn_804DF080(reinterpret_cast<const Record50E20*>(reinterpret_cast<const u8*>(obj->records) + offset)) >= 240) result = true;
    return result;
}
}
