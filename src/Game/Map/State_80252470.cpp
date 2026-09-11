#include "LiveActor/LiveActor.hpp"
struct Value52470 { bool tag; u16 value; };
struct Actor52470 : LiveActor { u8 opaque90[0x18]; void* childA8; u8 opaqueAC[0x24]; void* childD0; void* childD4; u8 opaqueD8[8]; u8 flagE0; };
namespace MR { bool isFirstStep(const LiveActor*); }
extern "C" {
void fn_804A2950(void*, const char*, s32, s32, s32);
void fn_8002ED90(void*, const char*);
Value52470* fn_8024C740(Value52470*);
void fn_80483440(void*, Value52470*);
void fn_8024C670(u16*, const Value52470*);
s32 fn_80483450(const void*);
void fn_80482EC0(void*, s32, const u16*);
void fn_804A2E00(void*, const char*, const char*, const char*);
bool fn_80483050(const void*);
bool fn_804A2BC0(const void*);
void fn_80482F60(void*);
bool fn_804A2BB0(const void*);
void fn_80250990(void*);
bool fn_800308A0(const void*);
void fn_804A2E20(void*);
bool fn_804A2BA0(const void*);
extern const char lbl_80697058[], lbl_807CFB14[4];
extern u32 lbl_807D35C0, lbl_807D35A8, lbl_807D35AC;
void fn_80252470(Actor52470* obj) {
    const char* names = lbl_80697058;
    u16 name[12];
    Value52470 value;
    if (MR::isFirstStep(obj)) {
        if (obj->flagE0) {
            fn_804A2950(obj->childA8, names + 0x360, 2, 1, 1);
            fn_8002ED90(obj->childA8, lbl_807CFB14);
        } else {
            fn_804A2950(obj->childA8, names + 0x378, 2, 1, 1);
            fn_8002ED90(obj->childA8, lbl_807CFB14);
        }
        fn_8024C740(&value);
        fn_80483440(obj->childD0, &value);
        fn_8024C670(name, &value);
        fn_80482EC0(obj->childD4, fn_80483450(obj->childD0), name);
        fn_804A2E00(obj->childA8, names + 0x300, names + 0x390, names + 0x330);
    }
    if (!fn_80483050(obj->childD4) && fn_804A2BC0(obj->childA8)) fn_80482F60(obj->childD4);
    if (fn_804A2BC0(obj->childA8) && fn_804A2BB0(obj->childA8)) fn_80250990(obj);
    if (fn_800308A0(obj->childA8)) {
        fn_804A2E20(obj->childA8);
        if (fn_804A2BA0(obj->childA8)) obj->setNerve(reinterpret_cast<const Nerve*>(&lbl_807D35C0));
        else if (obj->flagE0) obj->setNerve(reinterpret_cast<const Nerve*>(&lbl_807D35A8));
        else obj->setNerve(reinterpret_cast<const Nerve*>(&lbl_807D35AC));
    }
}
}
