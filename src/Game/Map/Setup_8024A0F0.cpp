#include <JGeometry/TMatrix.hpp>
struct Group4A0F0 { u32 index; };
struct Item4A0F0 { u32 field0; TMtx34f matrix04,matrix34,matrix64,matrix94; void* helper;void* sensor;u8 opaque[0x14];s32 category;Group4A0F0* group; };
struct Director4A0F0 { u8 base[0x14];void** holders; };
struct Host4A0F0 { u32 field0;const char* name; };
extern "C" {
void fn_80257200(void*,void*,void*);
void fn_8024A370(void*,const void*);
void fn_8024A1C0(const TMtx34f*,TVec3f*);
Director4A0F0* fn_80249F20();
s32 fn_80058380();
Group4A0F0* fn_80248BD0(void*,s32);
Host4A0F0* getSensorHost__2MRFPC9HitSensor(void*);
void fn_80126EA0(const char*,u32);
void* fn_802572D0(void*);
void fn_80126F30(void*);
void fn_8024A800(void*,TVec3f);
void fn_8024A0F0(Item4A0F0* obj,const void* matrix,void* sensor,void* arg4,void* arg5,s32 category,void* unused) {
 fn_80257200(obj->helper,arg4,arg5);
 obj->sensor=sensor;
 fn_8024A370(obj,matrix);
 TVec3f scale;
 fn_8024A1C0(&obj->matrix34,&scale);
 void* holder=fn_80249F20()->holders[category];
 Group4A0F0* group=fn_80248BD0(holder,fn_80058380());
 obj->group=group;
 // Preserve the retail snapshot before the external host lookup.
 u32 index=static_cast<const volatile Group4A0F0*>(group)->index;
 fn_80126EA0(getSensorHost__2MRFPC9HitSensor(sensor)->name,index);
 fn_80126F30(fn_802572D0(obj->helper));
 fn_8024A800(obj,scale);
 obj->category=category;
}
}
