#include <revolution.h>
struct Record50FC0 { u8 opaque[16]; };
struct Actor50FC0 { u8 opaque0[0xc4]; Record50FC0* records; u8 opaqueC8[0x10]; u64* identityD8; };
extern "C" {
bool fn_8024C7D0(const void*);
u32 fn_8024C7E0(const void*);
u16 fn_8024C7B0(const void*);
void fn_804D5FC0(void*, const u64*, const u32*);
void fn_804D6010();
s32 fn_8055AEF0(void*, u32, u32, u16);
void fn_80251050(Actor50FC0*, u64*, const void*);
bool fn_804DF0C0(const Record50FC0*, u32*);
bool fn_804DF0B0(const Record50FC0*, u64*);
u32 fn_80250E20(const Actor50FC0*, s32);
bool fn_80250E80(const Actor50FC0*, s32);
u16 fn_80250EF0(const Actor50FC0*, s32);
void fn_8024C7C0(void*, u32);
void fn_8024C790(void*, u16);
void fn_80250FC0(Actor50FC0* obj, void* destination, const void* value) {
    if (fn_8024C7D0(value)) {
        u32 index = fn_8024C7E0(value) + 1;
        fn_804D5FC0(destination, 0, &index);
    } else {
        fn_80251050(obj, obj->identityD8, value);
        fn_804D5FC0(destination, obj->identityD8, 0);
    }
    fn_804D6010();
}
void fn_80251050(Actor50FC0*, u64* output, const void* value) {
    u32 buffer[16];
    u16 index = fn_8024C7B0(value);
    if (fn_8055AEF0(buffer, 0, 0, index) == 0) *output = ((u64)buffer[11] << 32) | buffer[12];
}
void fn_802510B0(Actor50FC0* obj, void* value, s32 index) {
    u64 identity;
    u32 word;
    if (fn_804DF0C0(&obj->records[index - 1], &word)) fn_8024C7C0(value, fn_80250E20(obj, index));
    else if (fn_804DF0B0(&obj->records[index - 1], &identity) && fn_80250E80(obj, index)) { u16 selected = fn_80250EF0(obj, index); fn_8024C790(value, selected); }
    else fn_8024C7C0(value, 0);
}
}
