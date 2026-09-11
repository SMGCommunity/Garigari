#include "LiveActor/LiveActor.hpp"
struct Actor4C380 { u8 opaque[0x90];f32 value; };
struct Info4C380 { u8 opaque[8];s16 count; };
namespace MR { bool isFirstStep(const LiveActor*); }
extern "C" {
extern const char lbl_80696A88[];
void fn_8000A010(void*,const char*);
Info4C380* fn_8000AFB0(void*);
void fn_8000A7F0(void*,f32);
bool fn_80009950(void*);
void fn_8024C380(Actor4C380* obj) {
 LiveActor* actor=reinterpret_cast<LiveActor*>(obj);
 if(MR::isFirstStep(actor)) {
  fn_8000A010(obj,lbl_80696A88);
  f32 count=fn_8000AFB0(obj)->count;
  fn_8000A7F0(obj,count-obj->value);
 }
 if(fn_80009950(obj))actor->kill();
}
}
