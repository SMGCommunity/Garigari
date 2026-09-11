#include <JGeometry/TMatrix.hpp>
struct Item4B890 { u8 opaque[0x34];TMtx34f current,inverse,previous; };
extern "C" void fn_8024B890(Item4B890* obj,TVec3f* output,const TVec3f& point) {
 TMtx34f inverse;
 TVec3f local(point);
 PSMTXInverse(obj->previous.mMtx,inverse.mMtx);
 inverse.mult(local,local);
 obj->current.mult(local,local);
 local.sub(point);
 *output=local;
}
