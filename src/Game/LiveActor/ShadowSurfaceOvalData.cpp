#include <revolution.h>
extern "C" { void fn_80240550(); void fn_802406E0(); }
// Target Shift-JIS display name, resource name, and scalar constants.
extern "C" __attribute__((section(".data"))) const char lbl_80695AF8[20] =
    "\x89\x65\x95\x60\x89\xE6\x5B\x90\x85\x96\xCA\x91\xC8\x89\x7E\x89\x65\x5D";
extern "C" __attribute__((section(".data"))) const char lbl_80695B0C[20] = "ShadowVolumeSphere";
extern "C" const f32 lbl_807DC538 = 1.0f;
extern "C" const f32 lbl_807DC53C = 100.0f;
extern "C" const f32 lbl_807DC540 = 200.0f;
extern "C" const f32 lbl_807DC544 = 0.9f;
extern "C" {
    void init__7NameObjFRC12JMapInfoIter();
    void initAfterPlacement__7NameObjFv();
    void movement__7NameObjFv();
    void calcAnim__7NameObjFv();
    void calcViewAndEntry__7NameObjFv();
    void startMovement__7NameObjFv();
    void endMovement__7NameObjFv();
}
typedef void (*ShadowOvalSlot)();
extern "C" __attribute__((section(".data"))) const ShadowOvalSlot lbl_80695B20[12] = {
    0, 0, reinterpret_cast<ShadowOvalSlot>(fn_802406E0), init__7NameObjFRC12JMapInfoIter,
    initAfterPlacement__7NameObjFv, movement__7NameObjFv,
    reinterpret_cast<ShadowOvalSlot>(fn_80240550), calcAnim__7NameObjFv,
    calcViewAndEntry__7NameObjFv, startMovement__7NameObjFv, endMovement__7NameObjFv, 0
};
