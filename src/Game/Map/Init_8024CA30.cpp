#include "LiveActor/LiveActor.hpp"
namespace MR {
void connectToSceneMapObjMovement(NameObj*);
NameObj* createSceneObj(int);
void invalidateClipping(LiveActor*);
}
extern "C" {
void fn_8024D580(void*);
void fn_8024D5F0(void*);
void fn_8024D670(void*);
void fn_8024D790(void*);
void fn_8005C0D0(void*, const TVec3f&, f32);
void fn_80054650(TVec3f*, f32);
void fn_80059890();
extern const f32 lbl_807DC6D4, lbl_807DC6E4, lbl_807DC6E0;
extern const char lbl_80696CC8[];
extern u32 lbl_807D3518;
inline TVec3f soundOffset4CA30(f32 value) ALWAYS_INLINE { TVec3f result; fn_80054650(&result, value); return result; }
void fn_8024CA30(LiveActor* obj, const JMapInfoIter&) {
    MR::connectToSceneMapObjMovement(obj);
    MR::createSceneObj(0x76);
    fn_8024D580(obj);
    fn_8024D5F0(obj);
    fn_8024D670(obj);
    fn_8024D790(obj);
    fn_8005C0D0(obj, TVec3f(lbl_807DC6D4, lbl_807DC6E4, lbl_807DC6D4), lbl_807DC6E0);
    MR::invalidateClipping(obj);
    obj->initSound(4, lbl_80696CC8, 0, soundOffset4CA30(lbl_807DC6D4));
    obj->initNerve(reinterpret_cast<const Nerve*>(&lbl_807D3518), 0);
    fn_80059890();
    obj->makeActorAppeared();
}
}
