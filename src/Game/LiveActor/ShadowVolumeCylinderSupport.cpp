#include <revolution.h>
struct CylinderView { const void* vtable; u8 opaque[0x24]; f32 radius; };
extern "C" {
void* fn_802420C0(void*,const char*);
void fn_80242110(void*,const char*);
void* fn_80095A40(void*,int);
extern const char lbl_80695BA8[], lbl_80695BC0[];
extern const void* lbl_80695BD8[];
extern const f32 lbl_807DC558;
}
extern "C" CylinderView* fn_80241180(CylinderView* obj) {
 fn_802420C0(obj,lbl_80695BA8); obj->vtable=lbl_80695BD8;
 obj->radius=lbl_807DC558; fn_80242110(obj,lbl_80695BC0); return obj;
}
extern "C" void* fn_802411E0(void* obj,int deleting) {
 if(obj){ fn_80095A40(obj,0); if(deleting>0) ::operator delete(obj); } return obj;
}
extern "C" void fn_80241240(CylinderView* obj,f32 radius) { obj->radius=radius; }
