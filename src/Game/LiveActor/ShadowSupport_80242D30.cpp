#include <revolution.h>
struct View42D30 { u8 opaque[0x28]; f32 radius; };
extern "C" {
void* fn_8023FAC0(const void*);
bool fn_8023F380(const void*);
bool fn_8023F3B0(const void*);
}
extern "C" void fn_80242D30(View42D30* obj,f32 radius) { obj->radius=radius; }
extern "C" bool fn_80242D40(const void* obj) {
 void* controller=fn_8023FAC0(obj);
 return fn_8023F380(controller)&&fn_8023F3B0(controller);
}
