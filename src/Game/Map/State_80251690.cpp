#include "LiveActor/LiveActor.hpp"
#include "System/NerveExecutor.hpp"
#include "Scene/SceneObjHolder.hpp"
struct Actor51690 : LiveActor { LiveActor* child90; u8 opaque94[0x38]; NerveExecutor* childCC; void* childD0; u8 opaqueD4[0x24]; u8 enabledF8; };
namespace MR { bool isFirstStep(const LiveActor*); bool isValidSwitchA(const LiveActor*); bool onSwitchA(LiveActor*); }
extern "C" {
void fn_804A5470(void*);
void fn_80059AD0();
void fn_8005DFF0(void*);
void fn_8001D220();
void fn_80060290();
bool fn_804A54D0(const void*);
bool fn_804A54A0(const void*);
bool fn_80355470(const void*);
bool fn_80355510(const void*);
void fn_8024BB10(void*);
void fn_80250610(void*, f32);
void fn_8024FD80(void*);
void fn_80250790(void*);
void fn_80483E00(void*);
void fn_80250060(void*);
void fn_8005E030(void*);
void fn_80250A70(void*);
bool fn_8024BBA0(const void*);
bool fn_800602A0();
void fn_802508D0(void*);
extern u32 lbl_807D3564, lbl_807D3568, lbl_807D356C, lbl_807D3578;
extern const f32 lbl_807DC724;
void fn_80251690(Actor51690* obj) {
    if (MR::isFirstStep(obj)) {
        fn_804A5470(obj->childCC);
        fn_80059AD0();
        fn_8005DFF0(obj);
        fn_8001D220();
        fn_80060290();
        obj->enabledF8 = 0;
    }
    obj->childCC->updateNerve();
    if (fn_804A54D0(obj->childCC)) obj->enabledF8 = 1;
    if (!fn_804A54A0(obj->childCC)) {
        obj->child90->appear();
        if (fn_80355470(MR::getSceneObjHolder()->getObj(0x76))) {
            if (fn_80355510(MR::getSceneObjHolder()->getObj(0x76)))
                obj->setNerve(reinterpret_cast<const Nerve*>(&lbl_807D3568));
            else obj->setNerve(reinterpret_cast<const Nerve*>(&lbl_807D3564));
        } else obj->setNerve(reinterpret_cast<const Nerve*>(&lbl_807D356C));
    }
}
void fn_80251790(Actor51690* obj) {
    if (MR::isFirstStep(obj)) {
        if (MR::isValidSwitchA(obj)) MR::onSwitchA(obj);
        fn_8024BB10(obj->child90);
        fn_80250610(obj, lbl_807DC724);
        fn_8024FD80(obj);
        fn_80250790(obj);
        fn_80483E00(obj->childD0);
        fn_80250060(obj);
        fn_8005E030(obj);
        fn_80250A70(obj);
    }
    if (fn_8024BBA0(obj->child90) && fn_800602A0()) {
        fn_802508D0(obj);
        obj->setNerve(reinterpret_cast<const Nerve*>(&lbl_807D3578));
    }
}
}
