#include "LiveActor/LiveActor.hpp"
#include "Scene/SceneObjHolder.hpp"
struct Actor51850 : LiveActor { void* child90; u8 opaque94[0x18]; void* childAC; };
namespace MR { bool isFirstStep(const LiveActor*); }
extern "C" {
void fn_804A2950(void*, const char*, s32, s32, s32);
void fn_8002ED90(void*, const char*);
void fn_80250930(void*);
void fn_80250990(void*);
bool fn_800308A0(const void*);
bool fn_80355470(const void*);
bool fn_804A2B90(const void*);
void fn_804A2AF0(void*);
void fn_8024BB10(void*);
void fn_80250610(void*, f32);
void fn_802508D0(void*);
bool fn_8024BBA0(const void*);
extern const char lbl_806972F8[], lbl_80697310[], lbl_807CFB14[4];
extern u32 lbl_807D3564, lbl_807D3570, lbl_807D3578;
extern const f32 lbl_807DC724;
void fn_80251850(Actor51850* obj) {
    if (MR::isFirstStep(obj)) {
        fn_804A2950(obj->childAC, lbl_806972F8, 0, 0, 1);
        fn_8002ED90(obj->childAC, lbl_807CFB14);
        fn_80250930(obj);
    }
    if (fn_800308A0(obj->childAC)) {
        fn_80250990(obj);
        obj->setNerve(reinterpret_cast<const Nerve*>(&lbl_807D3564));
    }
}
void fn_802518E0(Actor51850* obj) {
    if (MR::isFirstStep(obj)) {
        fn_804A2950(obj->childAC, lbl_80697310, 1, 0, 1);
        fn_8002ED90(obj->childAC, lbl_807CFB14);
        fn_80250930(obj);
    }
    if (fn_80355470(MR::getSceneObjHolder()->getObj(0x76)) && fn_804A2B90(obj->childAC))
        obj->setNerve(reinterpret_cast<const Nerve*>(&lbl_807D3570));
}
void fn_80251980(Actor51850* obj) {
    if (MR::isFirstStep(obj)) {
        fn_804A2AF0(obj->childAC);
        fn_80250990(obj);
    }
    if (fn_800308A0(obj->childAC)) obj->setNerve(reinterpret_cast<const Nerve*>(&lbl_807D3564));
}
void fn_802519E0(Actor51850* obj) {
    if (MR::isFirstStep(obj)) {
        fn_8024BB10(obj->child90);
        fn_80250610(obj, lbl_807DC724);
        fn_802508D0(obj);
    }
    if (fn_8024BBA0(obj->child90)) obj->setNerve(reinterpret_cast<const Nerve*>(&lbl_807D3578));
}
}
