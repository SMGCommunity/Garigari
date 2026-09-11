#include <revolution.h>
extern "C" { void fn_802400C0(); void fn_80240210(); }
// Target Shift-JIS name and verified scalar constants.
extern "C" __attribute__((section(".data"))) const char lbl_80695A60[16] =
    "\x89\x65\x95\x60\x89\xE6[\x90\x85\x96\xCA\x89\x7E]";
extern "C" const f32 lbl_807DC530 = 1.0f;
extern "C" const f32 lbl_807DC534 = 100.0f;
extern "C" {
    void init__7NameObjFRC12JMapInfoIter();
    void initAfterPlacement__7NameObjFv();
    void movement__7NameObjFv();
    void calcAnim__7NameObjFv();
    void calcViewAndEntry__7NameObjFv();
    void startMovement__7NameObjFv();
    void endMovement__7NameObjFv();
}
typedef void (*ShadowCircleSlot)();
extern "C" __attribute__((section(".data"))) const ShadowCircleSlot lbl_80695A70[12] = {
    0, 0, reinterpret_cast<ShadowCircleSlot>(fn_80240210), init__7NameObjFRC12JMapInfoIter,
    initAfterPlacement__7NameObjFv, movement__7NameObjFv,
    reinterpret_cast<ShadowCircleSlot>(fn_802400C0), calcAnim__7NameObjFv,
    calcViewAndEntry__7NameObjFv, startMovement__7NameObjFv, endMovement__7NameObjFv, 0
};
