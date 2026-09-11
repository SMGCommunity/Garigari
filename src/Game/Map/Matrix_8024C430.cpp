#include "LiveActor/LiveActor.hpp"
#include <JGeometry/TMatrix.hpp>
namespace MR { void normalize(TVec3f*); void setBaseTRMtx(LiveActor*,const TPos3f&); }
inline void copyVector(TVec3f& dst,const TVec3f& src) ALWAYS_INLINE { JGeometry::setTVec3f(&src.x,&dst.x); }
extern "C" {
TVec3f fn_8001CF90();
TVec3f fn_8001D070();
bool fn_8003F1A0(const TVec3f*,f32);
extern f32 lbl_807DC6CC;
void fn_8024C430(LiveActor* actor) {
 TPos3f matrix;
 TVec3f difference;
 copyVector(difference,fn_8001CF90());
 JMathInlineVEC::PSVECSubtract(&difference,&actor->mPosition,&difference);
 if(fn_8003F1A0(&difference,lbl_807DC6CC)) return;
 MR::normalize(&difference);
 TVec3f up=fn_8001D070();
 TVec3f right;
 PSVECCrossProduct(&up,&difference,&right);
 if(fn_8003F1A0(&right,lbl_807DC6CC)) return;
 MR::normalize(&right);
 PSVECCrossProduct(&difference,&right,&up);
 matrix.setXYZDirInline(right,up,difference);
 matrix.mMtx[0][3]=actor->mPosition.x;
 matrix.mMtx[1][3]=actor->mPosition.y;
 matrix.mMtx[2][3]=actor->mPosition.z;
 MR::setBaseTRMtx(actor,matrix);
}
}
