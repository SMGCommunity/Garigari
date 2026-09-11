#include "LiveActor/LiveActor.hpp"
#include "Util/LiveActorUtil.hpp"
extern "C" {
f32 fn_80032470(void*);
f32 fn_80247480(f32,f32,f32);
void fn_8000A550(void*,f32);
extern const f32 lbl_807DC63C,lbl_807DC658,lbl_807DC674;
extern const u32 lbl_807D34D0;
}
extern "C" void fn_802474B0(LiveActor* obj) {
 if(MR::isFirstStep(obj) && !MR::isInvalidClipping(obj))MR::invalidateClipping(obj);
 fn_8000A550(obj,fn_80247480(fn_80032470(obj),lbl_807DC63C,lbl_807DC658));
 obj->mVelocity.x*=lbl_807DC674;obj->mVelocity.y*=lbl_807DC674;obj->mVelocity.z*=lbl_807DC674;
 if(MR::isStep(obj,30))obj->setNerve(reinterpret_cast<const Nerve*>(&lbl_807D34D0));
}
