#include "LiveActor/LiveActor.hpp"
#include "Util/ActorCameraUtil.hpp"
struct Actor4BA00 { u8 opaque[0x14];TVec3f position;u8 pad[0x88];TVec3f a8,b4;f32 c0,c4;TVec3f up; };
extern "C" {
extern u32 lbl_807D34F8;
extern const f32 lbl_807DC6B4,lbl_807DC6B0,lbl_807DC6BC;
extern const u8 lbl_80648B18[],lbl_80648B24[];
TVec3f* fn_80044550(TVec3f*,const void*);
void fn_80031170(void*,const TVec3f*);
void fn_8000BA60(void*,f32);
void fn_8024BA00(Actor4BA00* obj) {
 LiveActor* actor=reinterpret_cast<LiveActor*>(obj);
 actor->LiveActor::appear();
 actor->setNerve(reinterpret_cast<const Nerve*>(&lbl_807D34F8));
 MR::startActorCameraProgrammable(actor,0);
 obj->up.x=lbl_807DC6B4;obj->up.y=lbl_807DC6B0;obj->up.z=lbl_807DC6B4;
 TVec3f first;
 obj->a8=obj->b4=*fn_80044550(&first,lbl_80648B18);
 obj->c0=obj->c4=lbl_807DC6BC;
 TVec3f second;
 fn_80031170(obj,fn_80044550(&second,lbl_80648B24));
 MR::setProgrammableCameraParam(actor,obj->b4,obj->position,obj->up);
 fn_8000BA60(obj,obj->c4);
}
}
