#include <revolution.h>
struct ShadowView42160 { const void* vtable; u8 opaque[0x24]; f32 x,y,z; };
extern "C" {
void* fn_802420C0(void*,const char*);
void fn_80242110(void*,const char*);
void* fn_8023FAC0(const void*);
bool fn_8023F380(const void*);
bool fn_8023F3B0(const void*);
extern const char lbl_80695D80[],lbl_80695D98[];
extern const void* lbl_80695DB0[];
extern const f32 lbl_807DC580,lbl_807DC584;
}
extern "C" ShadowView42160* fn_80242160(ShadowView42160* obj) {
 fn_802420C0(obj,lbl_80695D80);
 obj->vtable=lbl_80695DB0;
 obj->x=lbl_807DC580; obj->y=lbl_807DC580; obj->z=lbl_807DC584;
 fn_80242110(obj,lbl_80695D98);
 return obj;
}
extern "C" bool fn_802421D0(const void* obj) {
 void* controller=fn_8023FAC0(obj);
 return fn_8023F380(controller) && fn_8023F3B0(controller);
}
