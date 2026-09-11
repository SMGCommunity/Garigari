#include "LiveActor/LiveActor.hpp"
struct Actor4CC70 : LiveActor {
    u8 flag90;
    u8 opaque91[7];
    void* value98;
    u8 opaque9C[0xaf];
    u8 flag14B;
    u8 opaque14C[0x1d];
    u8 flag169;
};
extern "C" {
extern u32 lbl_807D3518, lbl_807D351C, lbl_807D3520, lbl_807D3524, lbl_807D3528;
void fn_8024E370(void*);
void fn_8024C770(void*, const void*);
bool fn_8024C7A0(const void*);
bool fn_8024CC70(const LiveActor* obj) { return obj->isNerve(reinterpret_cast<const Nerve*>(&lbl_807D3518)); }
bool fn_8024CC80(const LiveActor* obj) { return obj->isNerve(reinterpret_cast<const Nerve*>(&lbl_807D351C)); }
void fn_8024CC90(Actor4CC70* obj) {
    obj->setNerve(reinterpret_cast<const Nerve*>(&lbl_807D3520));
    fn_8024E370(obj);
    obj->flag90 = 1;
}
void fn_8024CCD0(Actor4CC70* obj, const void* value, u8 flag) {
    fn_8024C770(obj->value98, value);
    if (fn_8024C7A0(value)) obj->setNerve(reinterpret_cast<const Nerve*>(&lbl_807D3528));
    else obj->setNerve(reinterpret_cast<const Nerve*>(&lbl_807D3524));
    fn_8024E370(obj);
    obj->flag169 = 0;
    obj->flag90 = 0;
    obj->flag14B = flag;
}
}
