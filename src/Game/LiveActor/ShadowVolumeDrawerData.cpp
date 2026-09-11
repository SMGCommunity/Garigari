#include <revolution.h>
extern "C" {
void calcAnim__7NameObjFv();
void calcViewAndEntry__7NameObjFv();
void draw__7NameObjCFv();
void endMovement__7NameObjFv();
void fn_80095A40();
void fn_802416D0();
void fn_802416E0();
void fn_802416F0();
void fn_80241720();
void fn_80241820();
void initAfterPlacement__7NameObjFv();
void init__7NameObjFRC12JMapInfoIter();
void movement__7NameObjFv();
void startMovement__7NameObjFv();
}
extern "C" __attribute__((section(".data"))) const char lbl_80695C10[32] = "\x83\x56\x83\x83\x83\x68\x83\x45\x83\x7B\x83\x8A\x83\x85\x81\x5B\x83\x80\x95\x60\x89\xE6\x8F\x89\x8A\xFA\x89\xBB";
typedef void (*VolumeDataSlot)();
extern "C" __attribute__((section(".data"))) const VolumeDataSlot lbl_80695C30[14] = {0,0,fn_80095A40,init__7NameObjFRC12JMapInfoIter,initAfterPlacement__7NameObjFv,movement__7NameObjFv,fn_80241720,calcAnim__7NameObjFv,calcViewAndEntry__7NameObjFv,startMovement__7NameObjFv,endMovement__7NameObjFv,fn_802416D0,fn_802416E0,fn_802416F0};
extern "C" __attribute__((section(".data"))) const VolumeDataSlot lbl_80695C68[12] = {0,0,fn_80241820,init__7NameObjFRC12JMapInfoIter,initAfterPlacement__7NameObjFv,movement__7NameObjFv,draw__7NameObjCFv,calcAnim__7NameObjFv,calcViewAndEntry__7NameObjFv,startMovement__7NameObjFv,endMovement__7NameObjFv,0};
extern "C" const f32 lbl_807DC560 = 0.0f;
