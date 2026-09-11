#include <revolution.h>
#include <JGeometry/TVec.hpp>
struct ShadowCircleView { const void* vtable; u8 opaque[0x14]; f32 radius; };
struct ShadowCircleHostView { u8 opaque[0x2C]; f32 scale; };
class ShadowController;
extern "C" {
    void* fn_80240390(void*, const char*);
    void* fn_8023FB40(void*, int);
    extern const char lbl_80695A60[];
    extern void (*const lbl_80695A70[])();
    extern const f32 lbl_807DC530, lbl_807DC534;
    ShadowController* fn_8023FAC0(const void*);
    bool fn_8023F380(const ShadowController*);
    bool fn_8023F3B0(const ShadowController*);
    bool isFollowHostScale__16ShadowControllerCFv(const ShadowController*);
    ShadowCircleHostView* fn_8023F0F0(const ShadowController*);
    void fn_8023F260(const ShadowController*, TVec3f*);
    void fn_8023F290(const ShadowController*, TVec3f*);
    void fn_80063930();
    void fn_80064300(const TVec3f&, const TVec3f&, f32, int, int);
}
extern "C" ShadowCircleView* fn_80240060(ShadowCircleView* obj) {
    fn_80240390(obj, lbl_80695A60);
    obj->vtable = lbl_80695A70;
    obj->radius = lbl_807DC534;
    return obj;
}
extern "C" void fn_802400B0(ShadowCircleView* obj, f32 radius) { obj->radius = radius; }
