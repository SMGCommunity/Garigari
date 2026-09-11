#include "LiveActor/LiveActor.hpp"
struct Child51A50 { u8 opaque0[0x14a]; u8 flag14A; };
struct Actor51A50 : LiveActor { void* child90; u8 opaque94[0x1c]; Child51A50* childB0; };
namespace MR { bool isFirstStep(const LiveActor*); }
extern "C" {
void fn_802500C0(void*);
void fn_8024FFA0(void*);
void fn_8005CF80();
void fn_8024FEF0(void*);
void fn_8005CD90();
void fn_80251430(void*);
void fn_802505C0(void*);
void fn_80250060(void*);
void fn_80250000(void*);
void fn_8024D000(void*, s32);
void fn_8024CFE0(void*);
bool fn_8024BBB0(const void*);
void fn_8024FDF0(void*);
bool fn_8024FE80(const void*);
extern u32 lbl_807D3580, lbl_807D358C, lbl_807D3584;
void fn_80251A50(Actor51A50* obj) {
    if (MR::isFirstStep(obj)) {
        fn_802500C0(obj);
        fn_8024FFA0(obj);
        fn_8005CF80();
    } else fn_8024FEF0(obj);
    fn_8005CD90();
    fn_80251430(obj);
}
void fn_80251AB0(Actor51A50* obj) {
    if (MR::isFirstStep(obj)) {
        fn_802505C0(obj);
        fn_80250060(obj);
        fn_80250000(obj);
        fn_8024D000(obj->childB0, 40);
        fn_8024CFE0(obj->childB0);
    }
    if (fn_8024BBB0(obj->child90)) {
        if (obj->childB0->flag14A) obj->setNerve(reinterpret_cast<const Nerve*>(&lbl_807D3580));
        else obj->setNerve(reinterpret_cast<const Nerve*>(&lbl_807D358C));
    }
}
void fn_80251B50(Actor51A50* obj) {
    if (MR::isFirstStep(obj)) fn_8024FDF0(obj);
    if (fn_8024FE80(obj)) obj->setNerve(reinterpret_cast<const Nerve*>(&lbl_807D3584));
}
}
