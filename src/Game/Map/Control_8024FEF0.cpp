#include "LiveActor/LiveActor.hpp"
struct Child4FEF0 : LiveActor { u8 opaque90[0xb4]; s32 value144; };
struct Actor4FEF0 { u8 opaque0[0xb8]; Child4FEF0* previous; Child4FEF0* current; LiveActor* childC0; };
extern "C" {
void fn_80250360(Actor4FEF0*);
void fn_8046D9E0(void*);
bool fn_8024CC80(const LiveActor*);
void fn_802503B0(Actor4FEF0*, s32);
void fn_8024CED0(void*);
void fn_8024FEF0(Actor4FEF0* obj) {
    if (obj->current) {
        if (obj->previous == obj->current) return;
        if (obj->previous) {
            fn_80250360(obj);
            fn_8046D9E0(obj->childC0);
        }
        if (fn_8024CC80(obj->current)) {
            fn_802503B0(obj, obj->current->value144);
            obj->childC0->appear();
        }
        obj->previous = obj->current;
        fn_8024CED0(obj->current);
    } else if (obj->previous) {
        fn_80250360(obj);
        fn_8046D9E0(obj->childC0);
    }
}
}
