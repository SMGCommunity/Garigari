#include "LiveActor/LiveActor.hpp"
struct Actor51F30 : LiveActor { void* child90; };
namespace MR { bool isFirstStep(const LiveActor*); }
extern "C" {
void fn_802505C0(void*);
void fn_80250060(void*);
void fn_80250000(void*);
bool fn_8024BBB0(const void*);
extern u32 lbl_807D359C;
void fn_80251F30(Actor51F30* obj) {
    if (MR::isFirstStep(obj)) {
        fn_802505C0(obj);
        fn_80250060(obj);
        fn_80250000(obj);
    }
    if (fn_8024BBB0(obj->child90)) obj->setNerve(reinterpret_cast<const Nerve*>(&lbl_807D359C));
}
}
