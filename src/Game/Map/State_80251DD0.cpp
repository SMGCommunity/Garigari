#include "LiveActor/LiveActor.hpp"
struct Actor51DD0 : LiveActor { u8 opaque90[0x68]; u8 enabledF8; };
namespace MR { bool isFirstStep(const LiveActor*); }
extern "C" {
void fn_8024FDF0(void*);
void fn_8005AFD0(const char*, s32);
bool fn_8024FE80(const void*);
extern const char lbl_80697298[], lbl_806972AC[];
extern u32 lbl_807D3594;
void fn_80251DD0(Actor51DD0* obj) {
    if (MR::isFirstStep(obj)) {
        fn_8024FDF0(obj);
        fn_8005AFD0(lbl_80697298, 30);
        fn_8005AFD0(lbl_806972AC, 30);
        obj->enabledF8 = 0;
    }
    if (fn_8024FE80(obj)) obj->setNerve(reinterpret_cast<const Nerve*>(&lbl_807D3594));
}
}
