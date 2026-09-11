#include <revolution.h>
extern "C" { void fn_80240550(); void fn_802406E0(); }
extern "C" __attribute__((section(".data"))) const char lbl_80695B50[32] = "\x89\x65\x95\x60\x89\xE6\x5B\x83\x7B\x83\x8A\x83\x85\x81\x5B\x83\x80\x83\x7B\x83\x62\x83\x4E\x83\x58\x5D";
extern "C" const f32 lbl_807DC548 = 0.0f;
extern "C" const f32 lbl_807DC54C = 0.5f;
extern "C" const f32 lbl_807DC550 = 100.0f;
extern "C" {
void fn_80241120();
void init__7NameObjFRC12JMapInfoIter();
void initAfterPlacement__7NameObjFv();
void movement__7NameObjFv();
void fn_80241720();
void calcAnim__7NameObjFv();
void calcViewAndEntry__7NameObjFv();
void startMovement__7NameObjFv();
void endMovement__7NameObjFv();
void fn_802407D0();
void fn_80240FD0();
void fn_802416F0();
}
typedef void (*ShadowVolumeSlot)();
extern "C" __attribute__((section(".data"))) const ShadowVolumeSlot lbl_80695B70[14] = {
0,
0,
fn_80241120,
init__7NameObjFRC12JMapInfoIter,
initAfterPlacement__7NameObjFv,
movement__7NameObjFv,
fn_80241720,
calcAnim__7NameObjFv,
calcViewAndEntry__7NameObjFv,
startMovement__7NameObjFv,
endMovement__7NameObjFv,
fn_802407D0,
fn_80240FD0,
fn_802416F0
};
