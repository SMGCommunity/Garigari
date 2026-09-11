#include <revolution.h>
extern "C" {
void fn_80241350();
void init__7NameObjFRC12JMapInfoIter();
void initAfterPlacement__7NameObjFv();
void movement__7NameObjFv();
void fn_80241720();
void calcAnim__7NameObjFv();
void calcViewAndEntry__7NameObjFv();
void startMovement__7NameObjFv();
void endMovement__7NameObjFv();
void fn_80241250();
void fn_80242150();
void fn_802416F0();
}
extern "C" __attribute__((section(".data"))) const char lbl_80695BA8[24] = "\x89\x65\x95\x60\x89\xE6\x5B\x83\x7B\x83\x8A\x83\x85\x81\x5B\x83\x80\x89\x7E\x92\x8C\x5D";
extern "C" __attribute__((section(".data"))) const char lbl_80695BC0[24]="ShadowVolumeCylinder";
typedef void (*CylinderDataSlot)();
extern "C" __attribute__((section(".data"))) const CylinderDataSlot lbl_80695BD8[14]={0,0,fn_80241350,init__7NameObjFRC12JMapInfoIter,initAfterPlacement__7NameObjFv,movement__7NameObjFv,fn_80241720,calcAnim__7NameObjFv,calcViewAndEntry__7NameObjFv,startMovement__7NameObjFv,endMovement__7NameObjFv,fn_80241250,fn_80242150,fn_802416F0};
extern "C" const f32 lbl_807DC558=100.0f;
