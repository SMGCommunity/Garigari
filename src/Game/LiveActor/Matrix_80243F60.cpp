#include "Util/MtxUtil.hpp"
struct View43F60 {
 virtual void opaque0();
 virtual void opaque1();
 virtual void opaque2();
 virtual void opaque3();
 virtual void opaque4();
 virtual void opaque5();
 virtual void opaque6();
 virtual void opaque7();
 virtual void opaque8();
 virtual void opaque9();
 virtual void opaque10();
 virtual void opaque11();
 virtual void opaque12();
 virtual void opaque13();
 virtual MtxPtr matrix() const;
 u8 prefix[0x28];TVec3f scale;u8 tail[0x68];TVec3f amount;
};
extern "C" MtxPtr fn_8001CD10();
extern "C" void fn_805D05B0(MtxPtr,int);
extern "C" const f32 lbl_807DC5D8;
inline void subtract43F60(register Vec* a,register const Vec* b) ALWAYS_INLINE {
 register f32 ax, bx, az, bz;
 asm {
  psq_l ax,0(a),0,0
  psq_l bx,0(b),0,0
  psq_l az,8(a),1,0
  ps_sub bx,ax,bx
  psq_l bz,8(b),1,0
  ps_sub ax,az,bz
  psq_st bx,0(a),0,0
  psq_st ax,8(a),1,0
 }
}
inline void multiply43F60(register const Vec* a,register const Vec* b,register Vec* out) ALWAYS_INLINE {
 register f32 xy,other,z;
 asm {
  psq_l xy,0(a),0,0
  psq_l other,0(b),0,0
  lfs z,8(b)
  ps_mul other,xy,other
  psq_st other,0(out),0,0
  lfs other,8(a)
  fmuls z,other,z
  stfs z,8(out)
 }
}
inline TVec3f scaled43F60(const TVec3f& value, s32 index) ALWAYS_INLINE {
 TVec3f amount(value);
 amount.x*=index;amount.y*=index;amount.z*=index;
 return amount;
}
inline TVec3f difference43F60(const TVec3f& one, const TVec3f& amount) ALWAYS_INLINE {
 TVec3f remaining(one);
 subtract43F60(&remaining,&amount);
 return remaining;
}
extern "C" void fn_80243F60(const View43F60* obj,s32 index) {
 Mtx matrix;
 TVec3f scale;
 MtxPtr camera=fn_8001CD10();
 PSMTXConcat(camera,obj->matrix(),matrix);
 TVec3f remaining=difference43F60(TVec3f(lbl_807DC5D8),scaled43F60(obj->amount,index));
 multiply43F60(&obj->scale,&remaining,&scale);
 MR::preScaleMtx(matrix,scale);fn_805D05B0(matrix,0);
}
