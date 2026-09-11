#include <JGeometry/TVec.hpp>
struct Item48F20 { u8 opaque[0xd8]; f32 radius; };
struct Group48F20 { u8 opaque[0x818]; TVec3f low,high; };
extern "C" {
TVec3f fn_80248010(const Item48F20*);
bool fn_8003DE90(f32,f32,f32);
void fn_80248D60(Group48F20*);
}
extern "C" void fn_80248F20(Group48F20* obj,const Item48F20* item) {
 f32 radius=item->radius;
 TVec3f center=fn_80248010(item);
 TVec3f low(obj->low),high(obj->high);
 low.x+=radius;low.y+=radius;low.z+=radius;
 high.x-=radius;high.y-=radius;high.z-=radius;
 if(!fn_8003DE90(center.x,low.x,high.x) || !fn_8003DE90(center.y,low.y,high.y) || !fn_8003DE90(center.z,low.z,high.z))fn_80248D60(obj);
}
