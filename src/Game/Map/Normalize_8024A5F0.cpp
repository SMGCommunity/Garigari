#include <JGeometry/TMatrix.hpp>
struct Item4A5F0 { u8 opaque[0xd0];bool flagD0,flagD1; };
extern "C" {
void fn_8024A1C0(const TMtx34f*,TVec3f*);
bool isNearZero__2MRFff(f32,f32);
extern const f32 lbl_807DC698,lbl_807DC6A0,lbl_807DC6A8;
f32 fn_8024A5F0(Item4A5F0* obj,TMtx34f* matrix) {
 TVec3f scale;
 fn_8024A1C0(matrix,&scale);
 TVec3f delta;
 f32 dz=scale.z-scale.x;
 f32 dy=scale.y-scale.z;
 delta.x=scale.x-scale.y;delta.y=dy;delta.z=dz;
 if(isNearZero__2MRFff(delta.x,lbl_807DC6A8)&&isNearZero__2MRFff(delta.y,lbl_807DC6A8)&&isNearZero__2MRFff(delta.z,lbl_807DC6A8))return scale.x;
 TVec3f factor;
 f32 result=lbl_807DC698;
 if(obj->flagD1) {
  factor.set<f32>(result/scale.x,result/scale.y,result/scale.z);
  result=lbl_807DC698;
 } else if(obj->flagD0) {
  result=(scale.x+scale.y+scale.z)/lbl_807DC6A0;
  factor.set<f32>(result/scale.x,result/scale.y,result/scale.z);
 }
 matrix->mMtx[0][0]*=factor.x;matrix->mMtx[1][0]*=factor.x;matrix->mMtx[2][0]*=factor.x;
 matrix->mMtx[0][1]*=factor.y;matrix->mMtx[1][1]*=factor.y;matrix->mMtx[2][1]*=factor.y;
 matrix->mMtx[0][2]*=factor.z;matrix->mMtx[1][2]*=factor.z;matrix->mMtx[2][2]*=factor.z;
 return result;
}
}
