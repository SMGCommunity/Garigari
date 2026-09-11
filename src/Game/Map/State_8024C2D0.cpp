#include "LiveActor/LiveActor.hpp"
namespace MR { bool isFirstStep(const LiveActor*); }
extern "C" {
extern u32 lbl_807D3508,lbl_807D350C;
extern const char lbl_80696A80[],lbl_80696A68[];
void fn_8000A010(void*,const char*);
void fn_8000A000(void*,const char*);
bool fn_80009950(void*);
void fn_8024C2D0(LiveActor* obj) {
 obj->LiveActor::appear();
 obj->setNerve(reinterpret_cast<const Nerve*>(&lbl_807D3508));
}
void fn_8024C310(LiveActor* obj) {
 if(MR::isFirstStep(obj)) {
  fn_8000A010(obj,lbl_80696A80);
  fn_8000A000(obj,lbl_80696A68);
 }
 if(fn_80009950(obj))obj->setNerve(reinterpret_cast<const Nerve*>(&lbl_807D350C));
}
}
