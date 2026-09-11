#include "LiveActor/LiveActor.hpp"
void* operator new(unsigned long);
struct Actor4FA60 : LiveActor { u8 opaque90[0x14]; NameObj* childA4; void* fieldA8; void* fieldAC; u8 opaqueB0[0x10]; NameObj* childC0; u8 opaqueC4[8]; void* fieldCC; };
namespace MR { void connectToScene(NameObj*, int, int, int, int); }
extern "C" {
extern const char lbl_8069712C[], lbl_80697138[];
NameObj* fn_8045EAD0(void*, const char*, s32);
void fn_8045E970(NameObj*);
void* fn_804A2E60();
void* fn_804A2F20();
void fn_8004B340(void*);
NameObj* fn_8046D820(void*, s32, const char*);
void* fn_804A4D70(void*);
void fn_804A5490(void*);
void fn_8024FA60(Actor4FA60* obj) {
    void* allocation = ::operator new(0x34);
    NameObj* child = static_cast<NameObj*>(allocation);
    if (allocation) child = fn_8045EAD0(allocation, lbl_8069712C, 0);
    obj->childA4 = child;
    child->initWithoutIter();
    fn_8045E970(obj->childA4);
    MR::connectToScene(obj->childA4, 14, 13, -1, 81);
}
void fn_8024FAD0(Actor4FA60* obj) {
    obj->fieldA8 = fn_804A2E60();
    fn_8004B340(obj->fieldA8);
    obj->fieldAC = fn_804A2F20();
    fn_8004B340(obj->fieldAC);
}
void fn_8024FB10(Actor4FA60* obj) {
    void* allocation = ::operator new(0x110);
    NameObj* child = static_cast<NameObj*>(allocation);
    if (allocation) child = fn_8046D820(allocation, 12, lbl_80697138);
    obj->childC0 = child;
    child->initWithoutIter();
}
void fn_8024FB60(Actor4FA60* obj) {
    void* child = ::operator new(0x20);
    if (child) child = fn_804A4D70(child);
    obj->fieldCC = child;
    fn_804A5490(child);
}
}
