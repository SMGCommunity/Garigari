#include <revolution.h>
extern "C" __attribute__((section(".data"))) const char lbl_80695A18[24] =
    "\x89\x65\x95\x60\x89\xE6[\x90\x85\x96\xCA\x83\x7B\x83\x62\x83\x4E\x83\x58]";
extern "C" {
    void fn_80240000();
    void fn_8023FBC0();
    void init__7NameObjFRC12JMapInfoIter();
    void initAfterPlacement__7NameObjFv();
    void movement__7NameObjFv();
    void calcAnim__7NameObjFv();
    void calcViewAndEntry__7NameObjFv();
    void startMovement__7NameObjFv();
    void endMovement__7NameObjFv();
}
typedef void (*ShadowBoxSlot)();
extern "C" __attribute__((section(".data"))) const ShadowBoxSlot lbl_80695A30[12] = {
    0, 0, fn_80240000, init__7NameObjFRC12JMapInfoIter,
    initAfterPlacement__7NameObjFv, movement__7NameObjFv, fn_8023FBC0,
    calcAnim__7NameObjFv, calcViewAndEntry__7NameObjFv,
    startMovement__7NameObjFv, endMovement__7NameObjFv, 0
};
extern "C" const f32 lbl_807DC518 = 1.0f;
extern "C" const f32 lbl_807DC51C = 0.0f;
extern "C" const f32 lbl_807DC520 = 0.5f;
extern "C" const f32 lbl_807DC524 = -1.0f;
extern "C" const f32 lbl_807DC528 = 100.0f;
