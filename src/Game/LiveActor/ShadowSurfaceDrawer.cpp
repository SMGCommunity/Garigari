#include <revolution.h>
struct ShadowSurfaceView { const void* vtable; };
typedef void (*ShadowSurfaceSlot)();
struct ShadowSurfaceCallback { const void* vtable; ShadowSurfaceSlot callback; };
extern "C" {
    void* __ct__7NameObjFPCc(void*, const char*);
    void* __dt__7NameObjFv(void*, int);
    void* fn_8023FA70(void*, const char*);
    extern const ShadowSurfaceSlot lbl_80695AA0[];
    extern const ShadowSurfaceSlot lbl_80695ACC[];
    extern const u8 lbl_80681C10[];
    void fn_802402D0();
    void fn_8004B920(const ShadowSurfaceCallback*, int);
    void fn_800639B0(int, int, int);
    void fn_805CDC50(int, int, int, int, int, int, int);
    void fn_805CDB40(int, const u32*);
    void fn_805CFEB0(int, int, int);
    void fn_805CCA20(int);
    void fn_805CFE50(int);
    void fn_805CFE80(int);
    void fn_805D0000(int, int);
    void* createSceneObj__2MRFi(int);
    void connectToScene__2MRFP7NameObjiiii(void*, int, int, int, int);
}
extern "C" ShadowSurfaceView* fn_80240270(ShadowSurfaceView* obj, const char* name) {
    __ct__7NameObjFPCc(obj, name);
    obj->vtable = lbl_80695ACC;
    ShadowSurfaceCallback callback;
    callback.vtable = lbl_80681C10;
    callback.callback = fn_802402D0;
    fn_8004B920(&callback, 0x2A);
    return obj;
}
extern "C" void fn_802402D0() {
    fn_800639B0(0, 1, 1);
    fn_805CDC50(4, 0, 0, 0, 0, 0, 2);
    fn_805CDC50(5, 0, 0, 0, 0, 0, 2);
    u32 color = 0x80;
    fn_805CDB40(4, &color);
    fn_805CFEB0(1, 3, 0);
    fn_805CCA20(2);
    fn_805CFE50(1);
    fn_805CFE80(1);
    fn_805D0000(1, 0);
}
extern "C" ShadowSurfaceView* fn_80240390(ShadowSurfaceView* obj, const char* name) {
    fn_8023FA70(obj, name);
    obj->vtable = lbl_80695AA0;
    createSceneObj__2MRFi(0x4F);
    connectToScene__2MRFP7NameObjiiii(obj, -1, -1, -1, 0x2A);
    return obj;
}
extern "C" ShadowSurfaceView* fn_802403F0(ShadowSurfaceView* obj, int deleting) {
    if (obj) {
        __dt__7NameObjFv(obj, 0);
        if (deleting > 0) ::operator delete(obj);
    }
    return obj;
}
extern "C" {
    void fn_8023FB40();
    void init__7NameObjFRC12JMapInfoIter();
    void initAfterPlacement__7NameObjFv();
    void movement__7NameObjFv();
    void draw__7NameObjCFv();
    void calcAnim__7NameObjFv();
    void calcViewAndEntry__7NameObjFv();
    void startMovement__7NameObjFv();
    void endMovement__7NameObjFv();
}
extern "C" __attribute__((section(".data"))) const ShadowSurfaceSlot lbl_80695AA0[11] = {
    0, 0, fn_8023FB40, init__7NameObjFRC12JMapInfoIter,
    initAfterPlacement__7NameObjFv, movement__7NameObjFv, draw__7NameObjCFv,
    calcAnim__7NameObjFv, calcViewAndEntry__7NameObjFv,
    startMovement__7NameObjFv, endMovement__7NameObjFv
};
extern "C" __attribute__((section(".data"))) const ShadowSurfaceSlot lbl_80695ACC[11] = {
    0, 0, reinterpret_cast<ShadowSurfaceSlot>(fn_802403F0), init__7NameObjFRC12JMapInfoIter,
    initAfterPlacement__7NameObjFv, movement__7NameObjFv, draw__7NameObjCFv,
    calcAnim__7NameObjFv, calcViewAndEntry__7NameObjFv,
    startMovement__7NameObjFv, endMovement__7NameObjFv
};
