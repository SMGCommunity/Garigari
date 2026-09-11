#include <revolution.h>
struct ShadowBoxView { const void* vtable; u8 opaque[0x14]; f32 x, y, z; };
extern "C" {
    void* fn_80240390(void*, const char*);
    extern const char lbl_80695A18[];
    extern const u8 lbl_80695A30[];
    extern const f32 lbl_807DC528;
}
extern "C" ShadowBoxView* fn_8023FAE0(ShadowBoxView* obj) {
    fn_80240390(obj, lbl_80695A18);
    obj->vtable = lbl_80695A30;
    obj->x = lbl_807DC528;
    obj->y = lbl_807DC528;
    obj->z = lbl_807DC528;
    return obj;
}
