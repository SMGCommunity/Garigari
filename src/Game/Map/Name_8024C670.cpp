#include <revolution.h>
extern "C" {
bool fn_8024C7D0(const void*);
u32 fn_8024C7E0(const void*);
bool fn_8024C7A0(const void*);
u16 fn_8024C7B0(const void*);
extern const char* lbl_80696BFC[];
const u16* fn_800413C0(const char*);
void fn_800410A0(u16*, const u16*, u32);
s32 fn_8055AEF0(void*, u32, u32, u16);
void fn_8024C670(u16* destination, const void* value) {
    if (fn_8024C7D0(value)) {
        fn_800410A0(destination, fn_800413C0(lbl_80696BFC[fn_8024C7E0(value)]), 24);
        destination[11] = 0;
    }
    else if (fn_8024C7A0(value)) {
        u16 scratch[32];
        u16 index = fn_8024C7B0(value);
        if (fn_8055AEF0(scratch, 0, 0, index) == 0) {
            fn_800410A0(destination, scratch, 24);
            destination[11] = 0;
        }
    }
}
}
