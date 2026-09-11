#include <revolution.h>
struct ShadowVolumeDrawerView { const void* vtable; u8 opaque[0x14]; f32 start, end; u8 cut; };
extern "C" {
void* fn_8023FA70(void*, const char*);
void* fn_8023FAC0(const void*);
void* createSceneObj__2MRFi(int);
void connectToScene__2MRFP7NameObjiiii(void*, int,int,int,int);
void fn_80241520(const void*, void*, const void*);
extern const void* lbl_80695C30[];
extern const f32 lbl_807DC560;
}
extern "C" ShadowVolumeDrawerView* fn_80241420(ShadowVolumeDrawerView* obj, const char* name) {
 fn_8023FA70(obj,name); obj->vtable=lbl_80695C30;
 obj->start=lbl_807DC560; obj->end=lbl_807DC560; obj->cut=0;
 createSceneObj__2MRFi(0x4E); connectToScene__2MRFP7NameObjiiii(obj,-1,-1,-1,0x2B); return obj;
}
extern "C" void fn_80241490(ShadowVolumeDrawerView* obj, f32 value) { obj->start=value; }
extern "C" void fn_802414A0(ShadowVolumeDrawerView* obj, f32 value) { obj->end=value; }
extern "C" void fn_802414B0(ShadowVolumeDrawerView* obj) { obj->cut=1; }
extern "C" void fn_802414C0(ShadowVolumeDrawerView* obj) { obj->cut=0; }
extern "C" void fn_802414D0(const ShadowVolumeDrawerView* obj, void* point) { fn_80241520(obj,point,fn_8023FAC0(obj)); }
