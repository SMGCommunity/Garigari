#include "LiveActor/LiveActor.hpp"
struct Child51BB0 { u8 opaque0[0x144]; s32 index144; u8 opaque148[2]; u8 flag14A; };
struct Actor51BB0 : LiveActor { u8 opaque90[0x1c]; void* childAC; Child51BB0* childB0; };
namespace MR { bool isFirstStep(const LiveActor*); }
extern "C" {
void fn_804A2950(void*, const char*, s32, s32, s32);
void fn_8002ED90(void*, const char*);
void fn_80250930(void*);
void fn_80250990(void*);
bool fn_800308A0(const void*);
void fn_804D5F60(s32, s32, const s32*);
bool fn_804D6070();
void fn_80250180(void*);
extern const char lbl_80697328[], lbl_807CFB14[4];
extern u32 lbl_807D3588, lbl_807D358C;
void fn_80251BB0(Actor51BB0* obj) {
    if (MR::isFirstStep(obj)) {
        fn_804A2950(obj->childAC, lbl_80697328, 0, 0, 1);
        fn_8002ED90(obj->childAC, lbl_807CFB14);
        fn_80250930(obj);
    }
    if (fn_800308A0(obj->childAC)) {
        fn_80250990(obj);
        obj->setNerve(reinterpret_cast<const Nerve*>(&lbl_807D3588));
    }
}
void fn_80251C40(Actor51BB0* obj) {
    if (MR::isFirstStep(obj)) {
        s32 value = 1;
        fn_804D5F60(obj->childB0->index144, 0, &value);
    }
    if (!fn_804D6070()) {
        obj->childB0->flag14A = 0;
        fn_80250180(obj);
        obj->setNerve(reinterpret_cast<const Nerve*>(&lbl_807D358C));
    }
}
}
