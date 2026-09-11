#include "LiveActor/LiveActor.hpp"
#include "Util/LiveActorUtil.hpp"
extern "C" {
extern const char lbl_806964D8[];
extern const f32 lbl_80648AF8[3];
void fn_80051590(TMtx34f*,const char*);
TVec3f* fn_80044550(TVec3f*,const void*);
bool fn_800503F0();
extern const u32 lbl_807D34D0;
}
namespace MR { void startAction(const LiveActor*,const char*); }
extern "C" void fn_80247900(LiveActor* obj) {
 const char* names=lbl_806964D8;
 if(MR::isFirstStep(obj))MR::startAction(obj,names+0x2c);
 TMtx34f matrix;fn_80051590(&matrix,names+0x20);
 TVec3f temp;matrix.mult(*fn_80044550(&temp,lbl_80648AF8),obj->mPosition);
 if(!fn_800503F0()) {
  MR::startAction(obj,names);
  obj->setNerve(reinterpret_cast<const Nerve*>(&lbl_807D34D0));
 }
}
