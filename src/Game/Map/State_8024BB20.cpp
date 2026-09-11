#define JGEOMETRY_OUTLINE_VEC3_ADD
#include "LiveActor/LiveActor.hpp"
struct Actor4BB20 { u8 opaque[0x90];TVec3f target; };
extern "C" {
extern u32 lbl_807D34F4,lbl_807D34F8,lbl_807D34FC,lbl_807D3500;
extern const u8 lbl_80648B30[];
TVec3f* fn_80044550(TVec3f*,const void*);
inline TVec3f constant4BB20(const void* data) ALWAYS_INLINE { TVec3f v;fn_80044550(&v,data);return v; }
void fn_8024BB20(Actor4BB20* obj,const TVec3f& point) {
 TVec3f sum(point.addInline(constant4BB20(lbl_80648B30)));
 obj->target.x=sum.x;obj->target.y=sum.y;obj->target.z=sum.z;
 reinterpret_cast<LiveActor*>(obj)->setNerve(reinterpret_cast<const Nerve*>(&lbl_807D34FC));
}
bool fn_8024BBA0(const LiveActor* obj) { return obj->isNerve(reinterpret_cast<const Nerve*>(&lbl_807D34F8)); }
bool fn_8024BBB0(const LiveActor* obj) { return obj->isNerve(reinterpret_cast<const Nerve*>(&lbl_807D3500)); }
bool fn_8024BBC0(const LiveActor* obj) { return obj->isNerve(reinterpret_cast<const Nerve*>(&lbl_807D34F4))||obj->isNerve(reinterpret_cast<const Nerve*>(&lbl_807D34F8)); }
bool fn_8024BC20(const LiveActor* obj) { return obj->isNerve(reinterpret_cast<const Nerve*>(&lbl_807D34FC))||obj->isNerve(reinterpret_cast<const Nerve*>(&lbl_807D3500)); }
}
