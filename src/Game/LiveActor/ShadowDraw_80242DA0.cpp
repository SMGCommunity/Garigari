#include <revolution.h>
#include "Util/MtxUtil.hpp"
struct View42DA0 { u8 opaque[0x28]; f32 radius; };
struct Host42DA0 { u8 opaque[0x2C]; f32 scale; };
extern "C" {
void* fn_8023FAC0(const void*);
bool isFollowHostScale__16ShadowControllerCFv(const void*);
Host42DA0* fn_8023F0F0(const void*);
void fn_8023F260(const void*,TVec3f*);
MtxPtr fn_8001CD10();
void fn_805D05B0(MtxPtr,int);
extern const f32 lbl_807DC5C0,lbl_807DC5C4;
}
extern "C" void fn_80242DA0(const View42DA0* obj) {
 void* controller=fn_8023FAC0(obj);
 f32 radius=obj->radius/lbl_807DC5C4;
 if(isFollowHostScale__16ShadowControllerCFv(controller))radius*=fn_8023F0F0(controller)->scale;
 TPos3f matrix;matrix.identity();
 matrix.mMtx[0][0]=radius;matrix.mMtx[0][1]=lbl_807DC5C0;matrix.mMtx[0][2]=lbl_807DC5C0;
 matrix.mMtx[1][0]=lbl_807DC5C0;matrix.mMtx[1][1]=radius;matrix.mMtx[1][2]=lbl_807DC5C0;
 matrix.mMtx[2][0]=lbl_807DC5C0;matrix.mMtx[2][1]=lbl_807DC5C0;matrix.mMtx[2][2]=radius;
 TVec3f point;fn_8023F260(controller,&point);
 matrix.mMtx[0][3]=point.x;matrix.mMtx[1][3]=point.y;matrix.mMtx[2][3]=point.z;
 PSMTXConcat(fn_8001CD10(),matrix.mMtx,matrix.mMtx);fn_805D05B0(matrix.mMtx,0);
}
