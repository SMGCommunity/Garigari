#include <revolution.h>
struct View43B20 { u8 opaque[0xac]; f32 value,step; };
extern "C" const f32 lbl_807DC5D8,lbl_807DC5DC,lbl_807DC5E0;
extern "C" void fn_80243B20(View43B20* obj,s32 frames) {
 if(frames<=0){obj->value=lbl_807DC5D8;obj->step=lbl_807DC5DC;}
 else obj->step=lbl_807DC5D8/frames;
}
extern "C" void fn_80243B80(View43B20* obj,s32 frames) {
 if(frames<=0){obj->value=lbl_807DC5DC;obj->step=lbl_807DC5DC;}
 else obj->step=lbl_807DC5E0/frames;
}
