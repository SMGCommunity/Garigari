#include "LiveActor/LiveActor.hpp"
struct Child52090 { u8 opaque0[0x144]; s32 index144; };
struct Actor52090 : LiveActor { u8 opaque90[0x20]; Child52090* childB0; };
namespace MR { bool isFirstStep(const LiveActor*); }
extern "C" {
void fn_804D5EE0(s32);
bool fn_804D6070();
bool fn_804D60A0();
void fn_80250180(void*);
void fn_80250360(void*);
void fn_80250990(void*);
extern u32 lbl_807D35A8, lbl_807D3574;
void fn_80252090(Actor52090* obj) {
    if (MR::isFirstStep(obj)) fn_804D5EE0(obj->childB0->index144);
    if (!fn_804D6070()) {
        if (fn_804D60A0()) {
            fn_80250180(obj);
            obj->setNerve(reinterpret_cast<const Nerve*>(&lbl_807D35A8));
        } else {
            fn_80250360(obj);
            fn_80250990(obj);
            obj->setNerve(reinterpret_cast<const Nerve*>(&lbl_807D3574));
        }
    }
}
}
