#include <revolution.h>

class ShadowController;
// Verified NameObj prefix and the controller slot used by these routines.
struct ShadowDrawerView {
    const void* vtable;
    u8 opaque[0x10];
    ShadowController* controller;
};
extern "C" {
    void* __ct__7NameObjFPCc(void*, const char*);
    extern void (*const lbl_806959E8[])();
}
extern "C" ShadowDrawerView* fn_8023FA70(ShadowDrawerView* drawer, const char* name) {
    __ct__7NameObjFPCc(drawer, name);
    drawer->vtable = lbl_806959E8;
    drawer->controller = 0;
    return drawer;
}
extern "C" ShadowController* fn_8023FAC0(const ShadowDrawerView* drawer) {
    return drawer->controller;
}
extern "C" void fn_8023FAD0(ShadowDrawerView* drawer, ShadowController* controller) {
    drawer->controller = controller;
}
extern "C" {
    void fn_80095AA0();
    void init__7NameObjFRC12JMapInfoIter();
    void initAfterPlacement__7NameObjFv();
    void movement__7NameObjFv();
    void draw__7NameObjCFv();
    void calcAnim__7NameObjFv();
    void calcViewAndEntry__7NameObjFv();
    void startMovement__7NameObjFv();
    void endMovement__7NameObjFv();
}
typedef void (*ShadowDrawerSlot)();
extern "C" __attribute__((section(".data"))) const ShadowDrawerSlot lbl_806959E8[12] = {
    0, 0, fn_80095AA0, init__7NameObjFRC12JMapInfoIter,
    initAfterPlacement__7NameObjFv, movement__7NameObjFv, draw__7NameObjCFv,
    calcAnim__7NameObjFv, calcViewAndEntry__7NameObjFv,
    startMovement__7NameObjFv, endMovement__7NameObjFv, 0
};
