#include "LiveActor/LiveActor.hpp"
struct Actor51FA0 : LiveActor { u8 opaque90[0x18]; void* childA8; };
namespace MR { bool isFirstStep(const LiveActor*); }
extern "C" {
void fn_804A2950(void*, const char*, s32, s32, s32);
void fn_8002ED90(void*, const char*);
void fn_804A2E00(void*, const char*, const char*, const char*);
void fn_80250930(void*);
void fn_80250990(void*);
bool fn_804A2BC0(const void*);
bool fn_800308A0(const void*);
void fn_804A2E20(void*);
bool fn_804A2BA0(const void*);
void fn_80250360(void*);
extern const char lbl_80697058[], lbl_807CFB14[4];
extern u32 lbl_807D35A0, lbl_807D3574;
void fn_80251FA0(Actor51FA0* obj) {
    const char* names = lbl_80697058;
    if (MR::isFirstStep(obj)) {
        fn_804A2950(obj->childA8, names + 0x2e8, 2, 0, 1);
        fn_8002ED90(obj->childA8, lbl_807CFB14);
        fn_804A2E00(obj->childA8, names + 0x300, names + 0x318, names + 0x330);
        fn_80250930(obj);
    }
    if (fn_804A2BC0(obj->childA8)) fn_80250990(obj);
    if (fn_800308A0(obj->childA8)) {
        fn_804A2E20(obj->childA8);
        if (fn_804A2BA0(obj->childA8)) obj->setNerve(reinterpret_cast<const Nerve*>(&lbl_807D35A0));
        else {
            fn_80250360(obj);
            obj->setNerve(reinterpret_cast<const Nerve*>(&lbl_807D3574));
        }
    }
}
}
