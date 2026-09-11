#include <revolution.h>
#include <JGeometry/TVec.hpp>
struct ShadowBoxDrawView { u8 opaque[0x18]; TVec3f size; };
extern "C" void fn_8023FBA0(ShadowBoxDrawView* obj, const TVec3f& size) {
    f32 z, y, x;
    x = size.x; y = size.y; z = size.z;
    obj->size.x = x; obj->size.y = y; obj->size.z = z;
}
