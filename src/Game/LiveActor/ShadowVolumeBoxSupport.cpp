#include <revolution.h>
#include <JGeometry/TVec.hpp>
struct ShadowVolumeBoxView { const void* vtable; u8 opaque[0x20]; TVec3f size; TVec3f points[14]; };
extern "C" {
void* fn_80241420(void*, const char*);
extern const char lbl_80695B50[];
extern const void* lbl_80695B70[];
extern const f32 lbl_807DC548, lbl_807DC550;
MtxPtr fn_8001CD10();
void fn_805D05B0(MtxPtr, int);
void fn_805D0660(int);
void fn_805CB330();
void fn_805CAEE0(int, int);
void fn_805CB370(int, int, int, int, int);
void fn_80240840(const void*);
}
extern "C" ShadowVolumeBoxView* fn_80240740(ShadowVolumeBoxView* obj) {
 fn_80241420(obj, lbl_80695B50);
 obj->vtable = lbl_80695B70;
 obj->size.x = lbl_807DC550; obj->size.y = lbl_807DC550; obj->size.z = lbl_807DC550;
 for (u32 i=0; i<14; ++i) obj->points[i].x = obj->points[i].y = obj->points[i].z = lbl_807DC548;
 return obj;
}
extern "C" void fn_802407C0(ShadowVolumeBoxView* obj, const TVec3f& size) { obj->size.set<f32>(size); }
extern "C" void fn_802407D0(const ShadowVolumeBoxView* obj) {
 fn_805D05B0(fn_8001CD10(), 0);
 fn_805D0660(0); fn_805CB330(); fn_805CAEE0(9,1);
 fn_805CB370(0,9,1,4,0);
 fn_80240840(obj);
}
