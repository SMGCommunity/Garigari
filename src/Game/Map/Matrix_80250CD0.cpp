#include <JGeometry/TMatrix.hpp>
extern "C" {
f64 fn_8063D88C(f64);
f64 fn_8063DC98(f64);
void fn_80250CD0(TMtx34f* matrix, f32 x, f32 y, f32 z) {
    f32 sxsy, cxcz, cxsz;
    f32 cz = fn_8063D88C(z);
    f32 cy = fn_8063D88C(y);
    f32 cx = fn_8063D88C(x);
    f32 sz = fn_8063DC98(z);
    f32 sy = fn_8063DC98(y);
    f32 sx = fn_8063DC98(x);
    sxsy = sx * sy;
    cxcz = cx * cz;
    cxsz = cx * sz;
    matrix->mMtx[0][0] = cy * cz;
    matrix->mMtx[1][0] = cy * sz;
    matrix->mMtx[2][0] = -sy;
    matrix->mMtx[0][1] = sxsy * cz - cxsz;
    matrix->mMtx[1][1] = cxcz + sxsy * sz;
    matrix->mMtx[2][1] = sx * cy;
    matrix->mMtx[0][2] = cxcz * sy + sx * sz;
    matrix->mMtx[1][2] = cxsz * sy - sx * cz;
    matrix->mMtx[2][2] = cx * cy;
}
}
