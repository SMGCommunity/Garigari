#include "LiveActor/ShadowHolderView.hpp"

struct ShadowClipFlag { u8 _0[0x73]; u8 clipped; };
extern "C" {
    void fn_8023EA30(ShadowHolderView*);
    void fn_8023EEC0(ShadowController*);
    void fn_8023EF90(ShadowController*);
    void fn_8023EE60(ShadowController*, f32);
    void fn_8023EE10(ShadowController*);
    void* fn_80061640(const char*);
    int fn_80061720(void*, int);
    extern const char lbl_80695990[];
    extern const char lbl_806959A8[];
}
extern "C" void fn_8023E8C0(ShadowHolderView* c) { fn_8023EA30(c); }
extern "C" void fn_8023E8D0(ShadowHolderView* c) {
    ShadowController* controller;
    const u32 count = c->registered.count;
    for (u32 i = 0; i < count; ++i) {
        controller = c->registered.array[i];
        fn_8023EEC0(controller);
        fn_8023EF90(controller);
    }
}
extern "C" void fn_8023E940(ShadowHolderView* c) {
    void* area = fn_80061640(lbl_80695990);
    if (area) {
        const int distance = fn_80061720(area, 0);
        const int enabled = fn_80061720(area, 1);
        c->distance = distance != -1 ? static_cast<f32>(distance) : c->defaultDistance;
        c->enabled = enabled == -1;
    } else {
        c->enabled = c->defaultEnabled;
        c->distance = c->defaultDistance;
    }
    area = fn_80061640(lbl_806959A8);
    if (area) {
        const int value = fn_80061720(area, 2);
        if (value != -1 && c->enabled) c->enabled = 0;
    }
}
extern "C" void fn_8023EA30(ShadowHolderView* c) {
    fn_8023E940(c);
    const u32 count = c->pending.count;
    for (u32 i = 0; i < count; ++i) {
        if (c->enabled) fn_8023EE60(c->pending.array[i], c->distance);
        else reinterpret_cast<ShadowClipFlag*>(c->pending.array[i])->clipped = 0;
        fn_8023EE10(c->pending.array[i]);
    }
    c->pending.count = 0;
}

extern "C" __attribute__((section(".data"))) const char lbl_80695990[24] = "ShadowFarClipCtrlArea";
extern "C" __attribute__((section(".data"))) const char lbl_806959A8[20] = "ViewGroupCtrlArea";

extern "C" {
    void fn_8023F9F0();
    void init__7NameObjFRC12JMapInfoIter();
    void draw__7NameObjCFv();
    void calcAnim__7NameObjFv();
    void calcViewAndEntry__7NameObjFv();
    void startMovement__7NameObjFv();
    void endMovement__7NameObjFv();
}
typedef void (*ShadowHolderVTableSlot)();
extern "C" __attribute__((section(".data"))) const ShadowHolderVTableSlot __vt__22ShadowControllerHolder[11] = {
    nullptr, nullptr, fn_8023F9F0, init__7NameObjFRC12JMapInfoIter,
    reinterpret_cast<ShadowHolderVTableSlot>(fn_8023E8D0),
    reinterpret_cast<ShadowHolderVTableSlot>(fn_8023E8C0),
    draw__7NameObjCFv, calcAnim__7NameObjFv, calcViewAndEntry__7NameObjFv,
    startMovement__7NameObjFv, endMovement__7NameObjFv
};
