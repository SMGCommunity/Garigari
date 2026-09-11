#include <JGeometry/TVec.hpp>
struct Group49010 { u8 opaque[0x814]; f32 radius; TVec3f low,high; };
extern "C" { extern const f32 lbl_807DC688,lbl_807DC690; }
extern "C" void fn_80249010(Group49010* obj,TVec3f low,TVec3f high) {
 if(lbl_807DC688==obj->radius) {
  obj->radius=lbl_807DC690;obj->low.set(low);obj->high.set(high);
 } else {
  if(low.x<obj->low.x)obj->low.x=low.x;
  if(low.y<obj->low.y)obj->low.y=low.y;
  if(low.z<obj->low.z)obj->low.z=low.z;
  if(obj->high.x<high.x)obj->high.x=high.x;
  if(obj->high.y<high.y)obj->high.y=high.y;
  if(obj->high.z<high.z)obj->high.z=high.z;
 }
}
