#include <revolution.h>
struct Clone43080 { const void* vtable; void* target; u32 a,b,c; };
extern "C" {
void* __nw__FUlP7JKRHeapi(u32,void*,int);
extern const void* lbl_80695F28[];
}
extern "C" Clone43080* fn_80243080(const Clone43080* obj,void* heap) {
 Clone43080* copy=(Clone43080*)__nw__FUlP7JKRHeapi(20,heap,0);
 if(copy) { copy->vtable=lbl_80695F28;copy->target=obj->target;copy->a=obj->a;copy->b=obj->b;copy->c=obj->c; }
 return copy;
}
