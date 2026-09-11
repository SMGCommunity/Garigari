#include <JGeometry/TMatrix.hpp>
struct Helper4A7B0 { u8 opaque[8];f32 radius; };
struct Host4A7B0 { u32 field0;const char* name; };
struct Sensor4A7B0 { u8 opaque[0x24];Host4A7B0* host; };
struct Item4A7B0 { const TMtx34f* source;u8 opaque[0xc0];Helper4A7B0* helper;Sensor4A7B0* sensor;u8 flags[0xc];f32 radius,scale;s32 category;s32* group; };
extern "C" {
void fn_8008F8E0(TMtx34f*,const TMtx34f*);
f32 fn_8024A5F0(void*,TMtx34f*);
void fn_8024A820(Item4A7B0*,f32) NO_INLINE;
extern const f32 lbl_807DC6A0;
void fn_8024A7B0(Item4A7B0* obj) {
 TMtx34f matrix;
 fn_8008F8E0(&matrix,obj->source);
 fn_8024A820(obj,fn_8024A5F0(obj,&matrix));
}
void fn_8024A800(Item4A7B0* obj,TVec3f scale) {
 fn_8024A820(obj,(scale.x+scale.y+scale.z)/lbl_807DC6A0);
}
void fn_8024A820(Item4A7B0* obj,f32 scale) {
 obj->scale=scale;obj->radius=scale*obj->helper->radius;
}
}
