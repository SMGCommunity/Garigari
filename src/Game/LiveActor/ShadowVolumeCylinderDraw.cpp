#include <revolution.h>
#include "Util/MtxUtil.hpp"
struct CylinderDrawView { u8 opaque[0x28]; f32 radius; };
struct CylinderHostView { u8 opaque[0x2C]; f32 scale; };
extern "C" {
void* fn_8023FAC0(const void*);
void fn_802414D0(const void*,TVec3f*);
void fn_8023F220(const void*,TVec3f*);
bool isFollowHostScale__16ShadowControllerCFv(const void*);
CylinderHostView* fn_8023F0F0(const void*);
f32 fn_80241600(const void*);
MtxPtr fn_8001CD10();
void fn_805D05B0(MtxPtr,int);
extern const f32 lbl_807DC558;
}
extern "C" void fn_80241250(const CylinderDrawView* obj) {
 void* controller=fn_8023FAC0(obj);
 TPos3f matrix;
 TVec3f point,direction;
 fn_802414D0(obj,&point); fn_8023F220(controller,&direction);
 TVec3f up; JMathInlineVEC::PSVECNegate(&direction,&up);
 MR::makeMtxUpNoSupportPos(&matrix,up,point);
 f32 radius=obj->radius/lbl_807DC558;
 if(isFollowHostScale__16ShadowControllerCFv(controller)) radius*=fn_8023F0F0(controller)->scale;
 f32 length=fn_80241600(obj)/lbl_807DC558;
 TVec3f scale; scale.x=radius; scale.y=length; scale.z=radius;
 MR::preScaleMtx(matrix.mMtx,scale);
 PSMTXConcat(fn_8001CD10(),matrix.mMtx,matrix.mMtx);
 fn_805D05B0(matrix.mMtx,0);
}
