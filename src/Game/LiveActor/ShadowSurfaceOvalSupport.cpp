#include <revolution.h>
#include <JGeometry/TVec.hpp>
struct ShadowOvalColor { u8 r, g, b, a; };
struct ShadowOvalView {
    const void* vtable;
    u8 opaque[0x14];
    void* model;
    TVec3f size;
    ShadowOvalColor color;
};
extern "C" {
    void* fn_80240390(void*, const char*);
    void* fn_80042D10(const char*);
    extern const char lbl_80695AF8[], lbl_80695B0C[];
    extern const void* lbl_80695B20[];
    extern const f32 lbl_807DC53C, lbl_807DC540;
}
extern "C" ShadowOvalView* fn_80240450(ShadowOvalView* obj) {
    fn_80240390(obj, lbl_80695AF8);
    obj->vtable = lbl_80695B20;
    obj->model = 0;
    obj->size.x = lbl_807DC53C;
    obj->size.y = lbl_807DC53C;
    obj->size.z = lbl_807DC540;
    obj->color.r = 0;
    obj->color.g = 0;
    obj->color.b = 0;
    obj->color.a = 0x40;
    obj->model = fn_80042D10(lbl_80695B0C);
    return obj;
}
extern "C" void fn_802404E0(ShadowOvalView* obj, ShadowOvalColor color) {
    union { u32 word; ShadowOvalColor bytes; } copy;
    copy.word = *reinterpret_cast<const u32*>(&color);
    obj->color.r = copy.bytes.r;
    obj->color.g = copy.bytes.g;
    obj->color.b = copy.bytes.b;
    obj->color.a = copy.bytes.a;
}
extern "C" void fn_80240520(ShadowOvalView* obj, u8 alpha) { obj->color.a = alpha; }
extern "C" void fn_80240530(ShadowOvalView* obj, const TVec3f& size) {
    JGeometry::setTVec3f(&size.x, &obj->size.x);
}
