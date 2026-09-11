#include <revolution.h>
#include <JGeometry/TVec.hpp>
struct ShadowView42490 { u8 opaque[0x28]; TVec3f size; };
extern "C" void fn_80242820(ShadowView42490* obj,const TVec3f& size) {
 JGeometry::setTVec3f(&size.x,&obj->size.x);
}
extern "C" void* fn_80095A40(void*, int);
// Inline base cleanup preserves the retail destructor's second null guard.
inline void destroyVolumeBase(void* obj) {
    if (obj) fn_80095A40(obj, 0);
}
extern "C" void* fn_80242840(void* obj, int deleting) {
    if (obj) {
        destroyVolumeBase(obj);
        if (deleting > 0) ::operator delete(obj);
    }
    return obj;
}
struct ShadowView428A0 { const void* vtable; u8 opaque[0x20]; void* arg; void* value; f32 x,y,z; };
extern "C" {
void* fn_80241420(void*,const char*);
extern const char lbl_80695E58[];
extern const void* lbl_80695E78[];
extern const f32 lbl_807DC5AC,lbl_807DC5A8,lbl_807DC5B0;
}
extern "C" ShadowView428A0* fn_802428A0(ShadowView428A0* obj,void* arg) {
 fn_80241420(obj,lbl_80695E58);
 obj->vtable=lbl_80695E78;
 obj->arg=arg;obj->value=0;
 obj->x=lbl_807DC5AC;obj->y=lbl_807DC5A8;obj->z=lbl_807DC5B0;
 return obj;
}
