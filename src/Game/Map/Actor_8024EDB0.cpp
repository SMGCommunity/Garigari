#include "LiveActor/LiveActor.hpp"
#include <JGeometry/TMatrix.hpp>
struct Actor4EDB0 : LiveActor { const TMtx34f* matrix; };
namespace MR {
bool isFirstStep(const LiveActor*);
void startAction(const LiveActor*, const char*);
bool isActionEnd(const LiveActor*);
void setBaseTRMtx(LiveActor*, MtxPtr);
void initActor(LiveActor*, const char*, bool);
void initLightCtrl(LiveActor*);
void invalidateClipping(LiveActor*);
void emitEffect(LiveActor*, const char*);
void deleteEffect(LiveActor*, const char*);
}
extern "C" {
void* __ct__9LiveActorFPCc(void*, const char*);
void fn_8004AD40(LiveActor*);
extern const void* lbl_80696FA8[];
extern const f32 lbl_807DC718;
extern u32 lbl_807D3550, lbl_807D3554, lbl_807D3558, lbl_807D355C;
extern const char lbl_80696F8C[], lbl_80696F9C[];
extern const char lbl_80696F60[], lbl_80696F68[], lbl_80696F70[], lbl_80696F78[];
Actor4EDB0* fn_8024EDB0(Actor4EDB0* obj, const char* model, const TMtx34f* matrix, const char* name) {
    __ct__9LiveActorFPCc(obj, name);
    obj->matrix = matrix;
    *reinterpret_cast<const void**>(obj) = lbl_80696FA8;
    MR::initActor(obj, model, false);
    fn_8004AD40(obj);
    obj->initEffectKeeper(0, 0, false);
    MR::initLightCtrl(obj);
    obj->mScale.x = lbl_807DC718;
    obj->mScale.y = lbl_807DC718;
    obj->mScale.z = lbl_807DC718;
    obj->initNerve(reinterpret_cast<const Nerve*>(&lbl_807D3550), 0);
    MR::invalidateClipping(obj);
    obj->makeActorDead();
    return obj;
}
void fn_8024EE80(LiveActor* obj) { obj->LiveActor::calcAnim(); }
void fn_8024EE90(LiveActor* obj) {
    if (!obj->isNerve(reinterpret_cast<const Nerve*>(&lbl_807D3550))) obj->setNerve(reinterpret_cast<const Nerve*>(&lbl_807D3550));
}
void fn_8024EEE0(LiveActor* obj) { obj->setNerve(reinterpret_cast<const Nerve*>(&lbl_807D3554)); }
void fn_8024EEF0(LiveActor* obj) { obj->setNerve(reinterpret_cast<const Nerve*>(&lbl_807D3558)); }
void fn_8024EF00(LiveActor* obj) { obj->setNerve(reinterpret_cast<const Nerve*>(&lbl_807D355C)); }
bool fn_8024EF10(const LiveActor* obj) { return obj->isNerve(reinterpret_cast<const Nerve*>(&lbl_807D3550)); }
void fn_8024EF20(LiveActor* obj) { MR::emitEffect(obj, lbl_80696F60); }
void fn_8024EF30(LiveActor* obj) { MR::emitEffect(obj, lbl_80696F68); }
void fn_8024EF40(LiveActor* obj) { MR::emitEffect(obj, lbl_80696F70); }
void fn_8024EF50(LiveActor* obj) { MR::emitEffect(obj, lbl_80696F78); }
void fn_8024EF60(LiveActor* obj) { MR::deleteEffect(obj, lbl_80696F78); }
void fn_8024EF70(LiveActor* obj) {
    if (MR::isFirstStep(obj)) MR::startAction(obj, lbl_80696F8C);
    if (MR::isActionEnd(obj)) obj->setNerve(reinterpret_cast<const Nerve*>(&lbl_807D3550));
}
void fn_8024EFD0(LiveActor* obj) {
    if (MR::isFirstStep(obj)) MR::startAction(obj, lbl_80696F9C);
    if (MR::isActionEnd(obj)) obj->setNerve(reinterpret_cast<const Nerve*>(&lbl_807D3550));
}
void fn_8024F030(Actor4EDB0* obj) {
    const TMtx34f* matrix = obj->matrix;
    obj->mPosition.set<f32>(matrix->mMtx[0][3], matrix->mMtx[1][3], matrix->mMtx[2][3]);
    MR::setBaseTRMtx(obj, const_cast<TMtx34f*>(obj->matrix)->mMtx);
}
}
