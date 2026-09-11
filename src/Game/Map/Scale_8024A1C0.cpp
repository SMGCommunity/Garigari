#include <JGeometry/TMatrix.hpp>
extern "C" f32 fn_80007B60(f32);
inline f32 column4A1C0(const TMtx34f* matrix,int column) ALWAYS_INLINE {
 f32 y=matrix->mMtx[1][column];
 f32 x=matrix->mMtx[0][column];
 f32 z=matrix->mMtx[2][column];
 return fn_80007B60(x*x+y*y+z*z);
}
extern "C" void fn_8024A1C0(const TMtx34f* matrix,TVec3f* out) {
 out->x=column4A1C0(matrix,0);
 out->y=column4A1C0(matrix,1);
 out->z=column4A1C0(matrix,2);
}
