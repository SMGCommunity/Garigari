#include <revolution.h>
struct Method4FA20 { u32 a, b, c; };
struct Callback4FA20 { const void* vtable; void* actor; Method4FA20 method; };
extern "C" {
extern const void* lbl_80697468[];
inline Callback4FA20* init4FA20(Callback4FA20* obj, void* actor, const Method4FA20& method) ALWAYS_INLINE {
    obj->vtable = lbl_80697468;
    obj->actor = actor;
    obj->method.a = method.a;
    obj->method.b = method.b;
    obj->method.c = method.c;
    return obj;
}
Callback4FA20* fn_8024FA20(Callback4FA20* obj, void* actor, const Method4FA20& method) {
    return init4FA20(obj, actor, Method4FA20(method));
}
}
