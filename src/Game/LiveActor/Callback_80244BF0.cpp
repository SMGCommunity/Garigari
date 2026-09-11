#include "LiveActor/View442B0.hpp"
struct Clone44C20 { const void* vtable; void* target; u32 a,b,c; };
extern "C" {
void* __nw__FUlP7JKRHeapi(u32,void*,int);
extern const void* lbl_80696130[];
void* fn_802449A0(void*,int);
void* __dt__7NameObjFv(void*,int);
}
extern "C" void fn_80244BF0(const Callback442B0* obj) {
 (static_cast<View442B0*>(obj->obj)->*obj->method)();
}
extern "C" Clone44C20* fn_80244C20(const Clone44C20* obj,void* heap) {
 Clone44C20* copy=(Clone44C20*)__nw__FUlP7JKRHeapi(20,heap,0);
 if(copy) { copy->vtable=lbl_80696130;copy->target=obj->target;copy->a=obj->a;copy->b=obj->b;copy->c=obj->c; }
 return copy;
}
extern "C" void* fn_80244C90(void* obj,int deleting) {
 if(obj) { fn_802449A0(obj,0);if(deleting>0)::operator delete(obj); }
 return obj;
}
extern "C" void* fn_80244CF0(void* obj,int deleting) {
 if(obj) { fn_802449A0(obj,0);if(deleting>0)::operator delete(obj); }
 return obj;
}
extern "C" void* fn_80244D50(void* obj,int deleting) {
 if(obj) { fn_802449A0(obj,0);if(deleting>0)::operator delete(obj); }
 return obj;
}
extern "C" void* fn_80244DB0(void* obj,int deleting) {
 if(obj) { fn_802449A0(obj,0);if(deleting>0)::operator delete(obj); }
 return obj;
}
extern "C" void* fn_80244E10(void* obj,int deleting) {
 if(obj) { __dt__7NameObjFv(obj,0);if(deleting>0)::operator delete(obj); }
 return obj;
}
