#include <revolution.h>
struct VolumeModelView { const void* vtable; u8 opaque[0x20]; void* model; };
extern "C" {
void* fn_80241420(void*,const char*);
void* fn_80042D10(const char*);
void fn_80022220(void*);
extern const void* lbl_80695D48[];
}
extern "C" VolumeModelView* fn_802420C0(VolumeModelView* obj,const char* name) {
 fn_80241420(obj,name); obj->vtable=lbl_80695D48; obj->model=0; return obj;
}
extern "C" void fn_80242110(VolumeModelView* obj,const char* name) { obj->model=fn_80042D10(name); }
extern "C" void fn_80242150(const VolumeModelView* obj) { fn_80022220(obj->model); }
