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
extern "C" { extern const char lbl_80695C10[]; extern const ShadowSurfaceSlot lbl_80695C68[]; void fn_800220D0(); }
extern "C" ShadowSurfaceView* fn_802413B0(ShadowSurfaceView* obj) {
    __ct__7NameObjFPCc(obj, lbl_80695C10);
    obj->vtable = lbl_80695C68;
    ShadowSurfaceCallback callback;
    callback.vtable = lbl_80681C10;
    callback.callback = fn_800220D0;
    fn_8004B920(&callback, 0x2B);
    return obj;
}
