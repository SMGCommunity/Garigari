#include <revolution.h>
#include "Util/MtxUtil.hpp"
#include "Util/MathUtil.hpp"
struct ModelDrawView { u8 opaque[0x28]; TVec3f size; };
struct ModelHostView { u8 opaque[0x2C]; TVec3f scale; };
extern "C" {
void* fn_8023FAC0(const void*);
void fn_8023F220(const void*,TVec3f*);
bool isFollowHostScale__16ShadowControllerCFv(const void*);
ModelHostView* fn_8023F0F0(const void*);
void fn_8023F120(const void*,MtxPtr);
void fn_802414D0(const void*,TVec3f*);
f32 fn_80241600(const void*);
void fn_80007060(TPos3f*,const TPos3f*);
void fn_80007380(TPos3f*,const TPos3f*,TPos3f*);
MtxPtr fn_8001CD10();
void fn_805D05B0(MtxPtr,int);
extern const f32 lbl_807DC590,lbl_807DC594,lbl_807DC598,lbl_807DC5A0;
}
inline void modelMultiply(register Vec* size, register const Vec* scale) ALWAYS_INLINE {
    register f32 hostXY, z, xy, hostZ;
    asm {
        psq_l hostXY, 0(scale), 0, 0
        psq_l xy, 0(size), 0, 0
        lfs z, 8(size)
        ps_mul xy, xy, hostXY
        psq_st xy, 0(size), 0, 0
        lfs hostZ, 8(scale)
        fmuls hostZ, z, hostZ
        stfs hostZ, 8(size)
    }
}
inline void modelCopy(register const Vec* from, register Vec* to) ALWAYS_INLINE {
 register f32 xy,z;
 asm {
 psq_l xy,0(from),0,0
 lfs z,8(from)
 psq_st xy,0(to),0,0
 stfs z,8(to)
 }
}
extern "C" void fn_80242580(const ModelDrawView* obj) {
 void* controller=fn_8023FAC0(obj);
 TPos3f base,inverse,matrix;
 TVec3f point,direction;
 fn_802414D0(obj,&point);
 fn_8023F220(controller,&direction);
 direction.negate();
 TVec3f size; modelCopy(&obj->size,&size);
 TVec3f localDirection,x,y,z;
 f32 denominator=lbl_807DC598;
 f32 factor=lbl_807DC590/denominator;
 size.scale(factor);
 if(size.x<=lbl_807DC5A0)size.x=lbl_807DC5A0;
 if(size.y<=lbl_807DC5A0)size.y=lbl_807DC5A0;
 if(size.z<=lbl_807DC5A0)size.z=lbl_807DC5A0;
 if(isFollowHostScale__16ShadowControllerCFv(controller)) modelMultiply(&size,&fn_8023F0F0(controller)->scale);
 fn_8023F120(controller,base.mMtx);
 TVec3f zero; zero.x=lbl_807DC594;zero.y=lbl_807DC594;zero.z=lbl_807DC594;
 base.setTrans(zero);
 MR::preScaleMtx(base.mMtx,size);
 fn_80007060(&inverse,&base);
 inverse.mult(direction,localDirection);
 matrix.identity();
 MR::makeMtxUpNoSupport(&matrix,localDirection);
 fn_80007380(&matrix,&base,&matrix);
 matrix.setTrans(point);
 { f32 vz=matrix.mMtx[2][0]; f32 vy=matrix.mMtx[1][0]; f32 vx=matrix.mMtx[0][0]; x.set<f32>(vx,vy,vz); }
 { f32 vz=matrix.mMtx[2][1]; f32 vy=matrix.mMtx[1][1]; f32 vx=matrix.mMtx[0][1]; y.set<f32>(vx,vy,vz); }
 { f32 vz=matrix.mMtx[2][2]; f32 vy=matrix.mMtx[1][2]; f32 vx=matrix.mMtx[0][2]; z.set<f32>(vx,vy,vz); }
 if(!MR::normalizeOrZero(&y)) {
 JMAVECScaleAdd(&y,&x,&x,-y.dot(x));
 JMAVECScaleAdd(&y,&z,&z,-y.dot(z));
 }
 y.scale(fn_80241600(obj)/lbl_807DC598);
 matrix.mMtx[0][0]=x.x;matrix.mMtx[1][0]=x.y;matrix.mMtx[2][0]=x.z;
 matrix.mMtx[0][1]=y.x;matrix.mMtx[1][1]=y.y;matrix.mMtx[2][1]=y.z;
 matrix.mMtx[0][2]=z.x;matrix.mMtx[1][2]=z.y;matrix.mMtx[2][2]=z.z;
 PSMTXConcat(fn_8001CD10(),matrix.mMtx,matrix.mMtx);
 fn_805D05B0(matrix.mMtx,0);
}
