#include "LiveActor/LiveActor.hpp"
#include "Util/ActorCameraUtil.hpp"
struct Actor4BFF0 { u8 opaque[0x14];TVec3f position;u8 pad[0x70];TVec3f target;u8 pad2[0xc];TVec3f a8,b4;f32 c0,c4;TVec3f up; };
extern "C" {
extern const u8 lbl_80648B3C[];
extern const f32 lbl_807DC6C4;
TVec3f* fn_80044550(TVec3f*,const void*);
void fn_80031170(void*,const TVec3f*);
void fn_8000BA60(void*,f32);
inline TVec3f constant4BFF0(const void* data) ALWAYS_INLINE { TVec3f v;fn_80044550(&v,data);return v; }
void fn_8024BFF0(Actor4BFF0* obj) {
 TVec3f target(obj->target.addInline(constant4BFF0(lbl_80648B3C)));
 obj->c0=lbl_807DC6C4;
 fn_80031170(obj,&target);
}
void fn_8024C060(Actor4BFF0* obj) {
 MR::setProgrammableCameraParam(reinterpret_cast<LiveActor*>(obj),obj->b4,obj->position,obj->up);
 fn_8000BA60(obj,obj->c4);
 obj->b4=obj->a8;
 obj->c4=obj->c0;
}
}
