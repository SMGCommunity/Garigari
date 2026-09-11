#include "System/NerveExecutor.hpp"
struct Actor4E7B0 { u8 opaque[0x90]; u8 flag90; u8 padding[7]; void* value98; void** entries; void* childA0; };
struct Helper4E7B0 : NerveExecutor { Actor4E7B0* actor; };
namespace MR { bool isFirstStep(const NerveExecutor*); bool isGreaterEqualStep(const NerveExecutor*, s32); }
extern "C" {
bool fn_8024C7D0(const void*); bool fn_8024C7A0(const void*); u32 fn_8024C7E0(const void*);
void fn_8024EF00(void*); bool fn_8024EF10(void*);
void fn_80354F40(void*); void fn_80354F30(void*);
void fn_8024EEE0(void*); void fn_8024EE90(void*); void fn_8024EEF0(void*);
extern u32 lbl_807D353C;
void fn_8024E7B0(Helper4E7B0* obj) {
    if (MR::isFirstStep(obj)) {
        if (fn_8024C7D0(obj->actor->value98)) fn_8024EF00(obj->actor->entries[fn_8024C7E0(obj->actor->value98)]);
    }
    if (obj->getNerveStep() % 8 < 4) fn_80354F40(obj->actor->childA0);
    else fn_80354F30(obj->actor->childA0);
    if (fn_8024C7D0(obj->actor->value98) && fn_8024EF10(obj->actor->entries[fn_8024C7E0(obj->actor->value98)])) {
        obj->setNerve(reinterpret_cast<const Nerve*>(&lbl_807D353C));
    } else if (fn_8024C7A0(obj->actor->value98) && MR::isGreaterEqualStep(obj, 40)) {
        fn_80354F30(obj->actor->childA0);
        obj->setNerve(reinterpret_cast<const Nerve*>(&lbl_807D353C));
    }
}
void fn_8024E8E0(Helper4E7B0* obj) {
    if (!obj->actor->flag90) {
        if (fn_8024C7A0(obj->actor->value98)) fn_80354F40(obj->actor->childA0);
        else fn_8024EEE0(obj->actor->entries[fn_8024C7E0(obj->actor->value98)]);
    }
}
void fn_8024E960(Helper4E7B0* obj) {
    if (!obj->actor->flag90) {
        if (fn_8024C7A0(obj->actor->value98)) fn_80354F30(obj->actor->childA0);
        else fn_8024EE90(obj->actor->entries[fn_8024C7E0(obj->actor->value98)]);
    }
}
void fn_8024E9E0(Helper4E7B0* obj) {
    if (!obj->actor->flag90) {
        if (fn_8024C7A0(obj->actor->value98)) fn_80354F40(obj->actor->childA0);
        else fn_8024EEF0(obj->actor->entries[fn_8024C7E0(obj->actor->value98)]);
    }
}
}
