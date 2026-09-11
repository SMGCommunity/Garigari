#include <revolution.h>
struct View42C60 { u8 opaque[0x24]; void* host; };
struct View42CD0 { const void* vtable; u8 opaque[0x24]; f32 radius; };
extern "C" {
u32 fn_80031520(const void*);
void* fn_80095A40(void*,int);
void* fn_802420C0(void*,const char*);
void fn_80242110(void*,const char*);
extern const char lbl_80695EB0[],lbl_80695EC8[];
extern const void* lbl_80695EE0[];
extern const f32 lbl_807DC5C4;
}
extern "C" u32 fn_80242C60(const View42C60* obj) { return fn_80031520(obj->host); }
extern "C" void* fn_80242C70(void* obj,int deleting) {
 if(obj) { fn_80095A40(obj,0); if(deleting>0)::operator delete(obj); }
 return obj;
}
extern "C" View42CD0* fn_80242CD0(View42CD0* obj) {
 fn_802420C0(obj,lbl_80695EB0);obj->vtable=lbl_80695EE0;obj->radius=lbl_807DC5C4;
 fn_80242110(obj,lbl_80695EC8);return obj;
}
