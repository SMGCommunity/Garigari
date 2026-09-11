#include "LiveActor/LiveActor.hpp"
struct Actor52770 : LiveActor { u8 opaque90[0x1c]; void* childAC; };
namespace MR { bool isFirstStep(const LiveActor*); }
extern "C" {
void fn_804A2950(void*, const char*, s32, s32, s32);
void fn_8002ED90(void*, const char*);
void fn_80250930(void*);
void fn_80250990(void*);
bool fn_800308A0(const void*);
extern const char lbl_80697404[], lbl_807CFB14[4];
extern u32 lbl_807D358C;
void fn_80252770(Actor52770* obj) {
    if (MR::isFirstStep(obj)) {
        fn_804A2950(obj->childAC, lbl_80697404, 0, 0, 1);
        fn_8002ED90(obj->childAC, lbl_807CFB14);
        fn_80250930(obj);
    }
    if (fn_800308A0(obj->childAC)) {
        fn_80250990(obj);
        obj->setNerve(reinterpret_cast<const Nerve*>(&lbl_807D358C));
    }
}
}
