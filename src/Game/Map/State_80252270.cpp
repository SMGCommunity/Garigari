#include "LiveActor/LiveActor.hpp"
struct Actor52270 : LiveActor { u8 opaque90[0x14]; LiveActor* childA4; u8 opaqueA8[0x28]; void* childD0; u8 opaqueD4[12]; u8 flagE0; };
namespace MR { bool isFirstStep(const LiveActor*); void startActionSound(const LiveActor*, const char*, long, long, long); }
extern "C" {
bool fn_80483430(const void*);
bool fn_80483420(const void*);
void fn_80483380(void*);
bool fn_8045E990(const void*);
void fn_8045E960(void*);
bool fn_80250570(const void*);
void fn_80250990(void*);
extern const char lbl_806973A0[];
extern u32 lbl_807D35CC, lbl_807D35B8, lbl_807D35B4;
void fn_80252270(Actor52270* obj) {
    if (MR::isFirstStep(obj) && !obj->flagE0) obj->childA4->appear();
    if (fn_80483430(obj->childD0)) {
        MR::startActionSound(obj, lbl_806973A0, -1, -1, -1);
        fn_80483380(obj->childD0);
        if (!fn_8045E990(obj->childA4)) fn_8045E960(obj->childA4);
        obj->setNerve(reinterpret_cast<const Nerve*>(&lbl_807D35CC));
    } else if (fn_80483420(obj->childD0)) {
        MR::startActionSound(obj, lbl_806973A0, -1, -1, -1);
        fn_80483380(obj->childD0);
        if (!fn_8045E990(obj->childA4)) fn_8045E960(obj->childA4);
        obj->setNerve(reinterpret_cast<const Nerve*>(&lbl_807D35B8));
    } else if (fn_80250570(obj)) {
        fn_80483380(obj->childD0);
        fn_8045E960(obj->childA4);
        fn_80250990(obj);
        obj->setNerve(reinterpret_cast<const Nerve*>(&lbl_807D35B4));
    }
}
}
