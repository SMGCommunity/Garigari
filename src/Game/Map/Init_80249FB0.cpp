#include <JGeometry/TMatrix.hpp>
struct Item49FB0 {
 void* field0;
 TMtx34f matrix04,matrix34,matrix64,matrix94;
 void* helper;void* fieldC8;
 u8 flagCC,flagCD,flagCE,flagCF,flagD0,flagD1;
 u32 fieldD4;f32 radius,fieldDC;s32 category;void* group;
};
struct Director49FB0 { u8 base[0x14];void** holders; };
extern "C" {
extern const f32 lbl_807DC6A4,lbl_807DC698;
void* fn_802571A0(void*);
Director49FB0* fn_80249F20();
bool fn_80248CF0(void*,void*);
void fn_8024A2D0(void*);
void fn_8024A270(void*);
void* fn_80248BD0(void*,s32);
Item49FB0* fn_80249FB0(Item49FB0* obj) {
 obj->field0=0;obj->fieldC8=0;obj->flagCC=0;obj->flagCE=1;
 obj->flagCF=0;obj->flagD0=0;obj->flagD1=0;obj->fieldD4=0;
 obj->radius=lbl_807DC6A4;obj->fieldDC=lbl_807DC698;obj->category=-1;obj->group=0;
 void* helper=::operator new(12);
 if(helper)helper=fn_802571A0(helper);
 obj->helper=helper;
 obj->matrix94.identity();obj->matrix34.identity();obj->matrix04.identity();
 PSMTXInverse(obj->matrix34.mMtx,obj->matrix64.mMtx);
 return obj;
}
void fn_8024A060(Item49FB0* obj) {
 s32 category=obj->category;
 void* holder=fn_80249F20()->holders[category];
 if(fn_80248CF0(obj->group,obj))fn_8024A2D0(obj);
 obj->group=fn_80248BD0(holder,0);
 if(obj->flagCC)fn_8024A270(obj);
}
}
