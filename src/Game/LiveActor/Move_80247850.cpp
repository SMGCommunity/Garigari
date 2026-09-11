#include "LiveActor/LiveActor.hpp"
#include "Util/MathUtil.hpp"
extern "C" {
extern const char lbl_806964F8[];
extern const f32 lbl_80648AF8[3];
void fn_80051590(TMtx34f*,const char*);
TVec3f* fn_80044550(TVec3f*,const void*);
f32 fn_80032470(void*);f32 fn_80247480(f32,f32,f32);void fn_8000A550(void*,f32);
bool fn_80009990(void*,f32);
extern const f32 lbl_807DC684,lbl_807DC638,lbl_807DC658,lbl_807DC634;
extern const u32 lbl_807D34E8;
}
extern "C" void fn_80247850(LiveActor* obj) {
 TMtx34f matrix;fn_80051590(&matrix,lbl_806964F8);
 TVec3f point,temp;
 matrix.mult(*fn_80044550(&temp,lbl_80648AF8),point);
 MR::vecBlend(&obj->mPosition,obj->mPosition,point,lbl_807DC684);
 fn_8000A550(obj,fn_80247480(fn_80032470(obj),lbl_807DC638,lbl_807DC658));
 if(fn_80009990(obj,lbl_807DC634))obj->setNerve(reinterpret_cast<const Nerve*>(&lbl_807D34E8));
}
