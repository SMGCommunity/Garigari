#include "LiveActor/LiveActor.hpp"
struct Actor52860 : LiveActor { u8 opaque90[0x1c]; void* childAC; u8 opaqueB0[0x30]; u8 flagE0; };
namespace MR { bool isFirstStep(const LiveActor*); }
extern "C" {
void fn_804A2950(void*, const char*, s32, s32, s32);
void fn_8002ED90(void*, const char*);
bool fn_800308A0(const void*);
extern const char lbl_8069741C[], lbl_807CFB14[4];
extern u32 lbl_807D35A8, lbl_807D35AC;
void fn_80252860(Actor52860* obj) {
    if (MR::isFirstStep(obj)) {
        fn_804A2950(obj->childAC, lbl_8069741C, 0, 0, 1);
        fn_8002ED90(obj->childAC, lbl_807CFB14);
    }
    if (fn_800308A0(obj->childAC)) {
        if (obj->flagE0) obj->setNerve(reinterpret_cast<const Nerve*>(&lbl_807D35A8));
        else obj->setNerve(reinterpret_cast<const Nerve*>(&lbl_807D35AC));
    }
}
}
