#include "LiveActor/LiveActor.hpp"
#include "System/NerveExecutor.hpp"
#include <JGeometry/TMatrix.hpp>
namespace MR { void makeMtxTransRotateY(MtxPtr, const LiveActor*); void makeMtxTR(MtxPtr, const LiveActor*); }
struct Helper4D380 : NerveExecutor { f32 factor; };
struct Actor4D380 : LiveActor {
    u8 opaque90[4];
    LiveActor* child94;
    void* value98;
    LiveActor** entries;
    LiveActor* childA0;
    void* childA4;
    TPos3f matrixA8, matrixD8, matrix108;
    u8 opaque138[0x14];
    Helper4D380* helper14C;
    NerveExecutor* helper150;
};
extern "C" {
void fn_8024D7F0(void*);
void fn_8024D8F0(void*);
void fn_801116F0(TPos3f*, const TPos3f*);
void fn_800D3010(const TVec3f*, const TVec3f&, TVec3f*);
void fn_80054650(TVec3f*, f32);
u32 fn_8001C680(TVec3f*, const TVec3f*);
void fn_8047A4C0(void*, const TVec3f*);
extern const f32 lbl_807DC6D4, lbl_807DC6E8, lbl_807DC6EC;
extern const f32 lbl_80648B58[];
inline TVec3f add4D380(const TVec3f& a, const TVec3f& b) ALWAYS_INLINE { TVec3f result(a); fn_800D3010(&result, b, &result); return result; }
inline TVec3f constant4D380() ALWAYS_INLINE { TVec3f result; JGeometry::setTVec3f(lbl_80648B58, &result.x); return result; }
inline void translation4D380(TPos3f& matrix, const TVec3f& position) ALWAYS_INLINE {
    matrix.mMtx[0][3] = position.x;
    matrix.mMtx[1][3] = position.y;
    matrix.mMtx[2][3] = position.z;
}
void fn_8024D380(Actor4D380* obj) {
    TPos3f matrix;
    TVec3f up, position, shifted, screen;
    fn_8024D7F0(obj);
    fn_8024D8F0(obj);
    if (lbl_807DC6D4 == obj->mRotation.x && lbl_807DC6D4 == obj->mRotation.z)
        MR::makeMtxTransRotateY(matrix.mMtx, obj);
    else MR::makeMtxTR(matrix.mMtx, obj);
    { f32 z = matrix.mMtx[2][1]; f32 y = matrix.mMtx[1][1]; f32 x = matrix.mMtx[0][1]; up.set<f32>(x, y, z); }
    { f32 z = matrix.mMtx[2][3]; f32 y = matrix.mMtx[1][3]; f32 x = matrix.mMtx[0][3]; position.set<f32>(x, y, z); }
    fn_801116F0(&obj->matrixA8, &matrix);
    translation4D380(obj->matrixA8, add4D380(position, up.scaleInline(lbl_807DC6E8).scaleInline(lbl_807DC6E8)));
    fn_801116F0(&obj->matrixD8, &matrix);
    fn_801116F0(&obj->matrix108, &matrix);
    obj->helper14C->updateNerve();
    fn_80054650(&obj->child94->mScale, lbl_807DC6E8 * (f32)obj->helper14C->factor);
    for (s32 i = 0; i < 7; ++i) { f32 factor = obj->helper14C->factor; fn_80054650(&obj->entries[i]->mScale, lbl_807DC6E8 * factor); }
    fn_80054650(&obj->childA0->mScale, lbl_807DC6EC * (f32)obj->helper14C->factor);
    obj->helper150->updateNerve();
    fn_800D3010(&obj->mPosition, constant4D380(), &shifted);
    fn_8001C680(&screen, &shifted);
    fn_8047A4C0(obj->childA4, &screen);
}
}
