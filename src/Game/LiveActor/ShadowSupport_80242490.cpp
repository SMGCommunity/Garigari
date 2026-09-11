#include <revolution.h>
#include <JGeometry/TVec.hpp>
struct ShadowView42490 { u8 opaque[0x28]; TVec3f size; };
extern "C" void fn_80242490(ShadowView42490* obj,const TVec3f& size) {
 JGeometry::setTVec3f(&size.x,&obj->size.x);
}
extern "C" void* fn_80095A40(void*, int);
// Inline base cleanup preserves the retail destructor's second null guard.
inline void destroyVolumeBase(void* obj) {
    if (obj) fn_80095A40(obj, 0);
}
extern "C" void* fn_802424B0(void* obj, int deleting) {
    if (obj) {
        destroyVolumeBase(obj);
        if (deleting > 0) ::operator delete(obj);
    }
    return obj;
}
struct ShadowView42160 { const void* vtable; u8 opaque[0x24]; f32 x,y,z; };
extern "C" {
void* fn_802420C0(void*,const char*);
void fn_80242110(void*,const char*);
void* fn_8023FAC0(const void*);
bool fn_8023F380(const void*);
bool fn_8023F3B0(const void*);
extern const char lbl_80695DE8[],lbl_80695E04[];
extern const void* lbl_80695E20[];
extern const f32 lbl_807DC598,lbl_807DC59C;
}
extern "C" ShadowView42160* fn_80242510(ShadowView42160* obj) {
 fn_802420C0(obj,lbl_80695DE8);
 obj->vtable=lbl_80695E20;
 obj->x=lbl_807DC598; obj->y=lbl_807DC598; obj->z=lbl_807DC59C;
 fn_80242110(obj,lbl_80695E04);
 return obj;
}
