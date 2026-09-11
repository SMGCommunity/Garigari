#include "LiveActor/LiveActor.hpp"
struct Actor4F320 : LiveActor { u8 opaque90[0x68]; u8 flagF8; };
namespace MR {
void connectToScene(LiveActor*, int, int, int, int);
void addHitSensorPriorBinder(LiveActor*, const char*, u16, f32, const TVec3f&);
void invalidateClipping(LiveActor*);
void initUseStageSwitchWriteA(LiveActor*, const JMapInfoIter&);
}
extern "C" {
extern const char lbl_80697074[], lbl_8069707C[];
extern const f32 lbl_807DC724, lbl_807DC738;
extern u32 lbl_807D3560;
void fn_8024F700(LiveActor*);
void fn_8024F760(LiveActor*);
void fn_8024F7B0(LiveActor*);
void fn_8024F900(LiveActor*);
void fn_8024FA60(LiveActor*);
void fn_8024FAD0(LiveActor*);
void fn_8024FB10(LiveActor*);
void fn_8024FB60(LiveActor*);
void fn_8024FBB0(LiveActor*);
void fn_8024FC00(LiveActor*);
void fn_8024FC70(LiveActor*);
void fn_8024FCC0(LiveActor*);
void fn_8001F360(LiveActor*, const JMapInfoIter&);
void fn_802509F0(LiveActor*, const JMapInfoIter&);
void fn_8024F320(Actor4F320* obj, const JMapInfoIter& iter) {
    MR::connectToScene(obj, 0x20, -1, -1, -1);
    obj->initHitSensor(1);
    MR::addHitSensorPriorBinder(obj, lbl_80697074, 8, lbl_807DC738, TVec3f(lbl_807DC724, lbl_807DC724, lbl_807DC724));
    obj->initSound(4, lbl_8069707C, 0, TVec3f(lbl_807DC724));
    fn_8024F700(obj);
    MR::invalidateClipping(obj);
    fn_8024F760(obj);
    fn_8024F7B0(obj);
    fn_8024F900(obj);
    fn_8024FA60(obj);
    fn_8024FAD0(obj);
    fn_8024FB10(obj);
    fn_8024FB60(obj);
    fn_8024FBB0(obj);
    fn_8024FC00(obj);
    fn_8024FC70(obj);
    fn_8024FCC0(obj);
    obj->initNerve(reinterpret_cast<const Nerve*>(&lbl_807D3560), 0);
    fn_8001F360(obj, iter);
    fn_802509F0(obj, iter);
    MR::initUseStageSwitchWriteA(obj, iter);
    obj->flagF8 = 0;
    obj->appear();
}
}
