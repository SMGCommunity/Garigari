#include <revolution.h>
struct Actor515A0 { u8 opaque0[0xa0]; void* childA0; void* childA4; };
extern "C" {
bool fn_8005E720(const void*, s32);
void* fn_8005E820();
void fn_8005E880(void*, const char*, void*);
void fn_8005EC60(const char*, const char*);
void fn_8005EC00(const char*, const char*);
void fn_8005EAE0(const char*, const char*);
void fn_8005E940(void*);
void fn_8005E790(void*);
extern const char lbl_80697058[];
void fn_802515A0(Actor515A0* obj) {
    const char* names = lbl_80697058;
    if (fn_8005E720(obj, 1)) {
        fn_8005E880(obj->childA4, names + 0x270, fn_8005E820());
        fn_8005E880(obj->childA0, names + 0x27c, fn_8005E820());
        fn_8005E880(obj->childA0, names + 0x284, fn_8005E820());
        fn_8005E880(obj->childA0, names + 0x290, fn_8005E820());
        fn_8005EC60(names + 0x27c, names + 0x270);
        fn_8005EC60(names + 0x284, names + 0x290);
        fn_8005EC00(names + 0x27c, names + 0x284);
        fn_8005EC00(names + 0x270, names + 0x290);
        fn_8005EAE0(names + 0x270, names + 0x290);
    }
    fn_8005E940(obj->childA4);
    fn_8005E940(obj->childA0);
    fn_8005E790(obj);
}
}
