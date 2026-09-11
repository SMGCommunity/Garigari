#include <revolution.h>
struct ModelFD0 { virtual void opaque0();virtual void opaque1();virtual void opaque2();virtual void opaque3();virtual void opaque4();virtual void invoke(); };
struct ViewFD0 { u8 opaque[0x90]; ModelFD0* volatile model; void* data; };
struct ResourceFD0 { u8 opaque[0xA0]; u32 a,b,unused,c; };
struct StateFD0 { u8 opaque[0x10C]; u32 a,b,c; };
extern "C" {
ResourceFD0* fn_80042CF0(const void*);
void fn_8051E070(void*);
void fn_8051DC40(void*);
extern StateFD0 lbl_8072C240;
extern volatile u32 lbl_807D62F0;
}
extern "C" void fn_80242FD0(const ViewFD0* obj) {
 ResourceFD0* resource=fn_80042CF0(obj);
 lbl_8072C240.a=resource->a;lbl_8072C240.b=resource->b;lbl_8072C240.c=resource->c;
 lbl_807D62F0=0;
 obj->model->invoke();fn_8051E070(obj->data);fn_8051DC40(obj->data);
}
