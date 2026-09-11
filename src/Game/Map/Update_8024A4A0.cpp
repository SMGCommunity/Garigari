#include <JGeometry/TMatrix.hpp>
struct Item4A4A0 { void* source;TMtx34f matrix04,matrix34,matrix64,matrix94;u8 opaque[0xa];bool flagCE,flagCF;u8 flags[4];s32 count;f32 radius,scale;u8 opaqueE0[8];f32 x,y,z; };
extern "C" {
bool isSameMtx__2MRFPA4_fPA4_f(MtxPtr,MtxPtr);
bool isNearZero__2MRFff(f32,f32);
f32 fn_8024A5F0(void*,TMtx34f*);
void fn_8024A820(void*,f32);
void fn_8008F8E0(TMtx34f*,const TMtx34f*);
extern const f32 lbl_807DC6A8;
inline bool enabled4A4A0(Item4A4A0* obj) ALWAYS_INLINE { return obj->flagCE||obj->flagCF; }
void fn_8024A4A0(Item4A4A0* obj) {
 if(!enabled4A4A0(obj)) {
  if(isSameMtx__2MRFPA4_fPA4_f(obj->matrix04.mMtx,obj->matrix34.mMtx))++obj->count;
  return;
 }
 if(isSameMtx__2MRFPA4_fPA4_f(obj->matrix04.mMtx,obj->matrix34.mMtx))++obj->count;
 else {
  if(obj->flagCF)obj->count=1;else obj->count=0;
  f32 scale=fn_8024A5F0(obj,&obj->matrix04);
  f32 delta=scale-obj->scale;
  obj->x=scale;obj->y=scale;obj->z=scale;
  if(!isNearZero__2MRFff(delta,lbl_807DC6A8))fn_8024A820(obj,scale);
 }
 obj->flagCF=false;
 if(obj->count<2) {
  fn_8008F8E0(&obj->matrix94,&obj->matrix34);
  fn_8008F8E0(&obj->matrix34,&obj->matrix04);
  PSMTXInverse(obj->matrix34.mMtx,obj->matrix64.mMtx);
 }
}
}
