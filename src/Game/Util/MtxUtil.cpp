#include "Util/MtxUtil.hpp"
#include "Util/MathUtil.hpp"
#include "revolution/mtx/mtx.h"
#include <JGeometry.hpp>
#include <JMath.hpp>

Mtx mtrans_org = { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f };
Mtx tmpmtx_sc = { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f };
Mtx tmpmtx_rx = { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f };
Mtx tmpmtx_ry = { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f };
Mtx tmpmtx_rz = { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f };

extern "C" void fn_8003C220(TVec3f*, TVec3f*, const TVec3f&);
extern "C" void fn_80007380(TPos3f*, const TPos3f*, const TPos3f*);
extern "C" void fn_80007060(TMtx34f*, const TMtx34f*);

namespace {
    ALWAYS_INLINE void copyMatrix(__REGISTER void* pDest, __REGISTER const void* pSrc) {
#ifdef __MWERKS__
        register f32 f_5, f_4, f_3, f_2, f_1, f_0;

        __asm {
            psq_l     f_0, 0(pSrc), 0, 0
            psq_l     f_1, 8(pSrc), 0, 0
            psq_l     f_2, 0x10(pSrc), 0, 0
            psq_l     f_3, 0x18(pSrc), 0, 0
            psq_l     f_4, 0x20(pSrc), 0, 0
            psq_l     f_5, 0x28(pSrc), 0, 0
            psq_st    f_0, 0(pDest), 0, 0
            psq_st    f_1, 8(pDest), 0, 0
            psq_st    f_2, 0x10(pDest), 0, 0
            psq_st    f_3, 0x18(pDest), 0, 0
            psq_st    f_4, 0x20(pDest), 0, 0
            psq_st    f_5, 0x28(pDest), 0, 0
        }
        ;
#endif
    }

}

extern "C" u32 fn_8003FED0(const TVec3f&);
extern "C" void fn_80045980(const TRot3f*, TVec3f*);
extern "C" void fn_80023780(TVec3f*, const TVec3f*, f32);
extern "C" void fn_800297B0(TVec3f*, const TVec3f*, const TVec3f*);

struct MtxQuaternion { f32 x, y, z, w; };
extern "C" void fn_805C8CF0(MtxQuaternion*, MtxPtr);
extern "C" void fn_8053A800(const MtxQuaternion*, const MtxQuaternion*, MtxQuaternion*, f32);
extern "C" void fn_805C8EC0(const MtxQuaternion*, const MtxQuaternion*, MtxQuaternion*, f32);
extern "C" void fn_805C8310(MtxPtr, const MtxQuaternion*);

extern "C" {
    extern u8 lbl_8074E9C0[0x1020];
    f32 fn_8053A9C0(const void*, f32, f32);
    f32 fn_8000D7E0(f32);

    ALWAYS_INLINE f32 matrixAtan(f32 y, f32 x) {
        return fn_8053A9C0(lbl_8074E9C0, y, x);
    }

    void fn_80045980(const TRot3f* matrix, TVec3f* out) {
        if (matrix->mMtx[2][0] - 1.0f >= -0.000003814697265625f) {
            out->x = matrixAtan(-matrix->mMtx[0][1], matrix->mMtx[1][1]);
            out->y = -HALF_PI;
            out->z = 0.0f;
            return;
        }
        f32 one = 1.0f;
        if (matrix->mMtx[2][0] + one <= 0.000003814697265625f) {
            out->x = matrixAtan(matrix->mMtx[0][1], matrix->mMtx[1][1]);
            out->y = HALF_PI;
            out->z = 0.0f;
        } else {
            out->x = matrixAtan(matrix->mMtx[2][1], matrix->mMtx[2][2]);
            out->z = matrixAtan(matrix->mMtx[1][0], matrix->mMtx[0][0]);
            out->y = fn_8000D7E0(-matrix->mMtx[2][0]);
        }
    }
}

extern "C" bool fn_8003D520(MtxQuaternion*, const MtxQuaternion*, const TVec3f&, const TVec3f&, f32);
extern "C" void fn_80007930(const TMtx34f*, MtxQuaternion*);
extern "C" void fn_8003D7D0(MtxQuaternion*, const MtxQuaternion*, const TVec3f&, f32);
extern "C" void fn_8003D8A0(MtxQuaternion*, const MtxQuaternion*, const TVec3f&, f32);
extern "C" bool fn_8003D680(MtxQuaternion*, const MtxQuaternion*, const TVec3f&, f32);
extern "C" bool fn_8003D6F0(MtxQuaternion*, const MtxQuaternion*, const TVec3f&, f32);
extern "C" void fn_80046590(TPos3f* matrix, const MtxQuaternion& q) {
            f32 yy = 2.0f * q.y * q.y;
            f32 zz = 2.0f * q.z * q.z;
            f32 xx = 2.0f * q.x * q.x;

            f32 xy = 2.0f * q.x * q.y;
            f32 xz = 2.0f * q.x * q.z;
            f32 yz = 2.0f * q.y * q.z;

            f32 wz = 2.0f * q.w * q.z;
            f32 wx = 2.0f * q.w * q.x;
            f32 wy = 2.0f * q.w * q.y;

            matrix->mMtx[0][0] = 1.0f - yy - zz;
            matrix->mMtx[0][1] = xy - wz;
            matrix->mMtx[0][2] = xz + wy;

            matrix->mMtx[1][0] = xy + wz;
            matrix->mMtx[1][1] = 1.0f - xx - zz;
            matrix->mMtx[1][2] = yz - wx;

            matrix->mMtx[2][0] = xz - wy;
            matrix->mMtx[2][1] = yz + wx;
            matrix->mMtx[2][2] = 1.0f - xx - yy;
}

extern "C" void fn_8003E840(f32*, TVec3f*, const TVec3f&);
extern "C" void fn_8000E260(const TRot3f*, TVec3f*);
extern "C" void fn_805C8730(MtxPtr, const Vec*, Vec*);
namespace MR {
    void makeMtxRotate(MtxPtr mtx, s16 rx, s16 ry, s16 rz) {
        f32 sinY = JMASSin(ry);
        f32 cosZ = JMASCos(rz);
        f32 sinZ = JMASSin(rz);
        f32 sinX = JMASSin(rx);
        f32 cosX = JMASCos(rx);
        f32 cosY = JMASCos(ry);
        f32 cosZsinY = cosZ * sinY;
        f32 sinZsinY = sinZ * sinY;

        mtx[2][0] = -sinY;
        mtx[0][3] = 0.0f;
        mtx[1][0] = sinZ * cosY;
        mtx[0][1] = sinX * cosZsinY - sinZ * cosX;
        mtx[2][1] = cosY * sinX;
        mtx[0][0] = cosZ * cosY;
        mtx[0][2] = cosX * cosZsinY + sinZ * sinX;
        mtx[1][1] = sinX * sinZsinY + cosZ * cosX;
        mtx[1][2] = cosX * sinZsinY - cosZ * sinX;
        mtx[2][2] = cosY * cosX;
        mtx[1][3] = 0.0f;
        mtx[2][3] = 0.0f;
    }

    void makeMtxRotate(MtxPtr mtx, f32 rx, f32 ry, f32 rz) {
        s16 angleX = (s16)(DEGREE_TO_S16 * rx);
        s16 angleY = (s16)(DEGREE_TO_S16 * ry);
        s16 angleZ = (s16)(DEGREE_TO_S16 * rz);
        makeMtxRotate(mtx, angleX, angleY, angleZ);
    }

    void makeMtxRotate(MtxPtr mtx, const TVec3f& rVec) {
        makeMtxRotate(mtx, rVec.x, rVec.y, rVec.z);
    }

    void makeMtxRotateY(MtxPtr mtx, f32 ry) {
        s16 angle = (s16)(DEGREE_TO_S16 * ry);
        f32 sinY = JMASSin(angle);
        f32 cosY = JMASCos(angle);

        mtx[0][0] = cosY;
        mtx[1][0] = 0.0f;
        mtx[2][0] = -sinY;
        mtx[0][1] = 0.0f;
        mtx[1][1] = 1.0f;
        mtx[2][1] = 0.0f;
        mtx[0][2] = sinY;
        mtx[1][2] = 0.0f;
        mtx[2][2] = cosY;
        mtx[0][3] = 0.0f;
        mtx[1][3] = 0.0f;
        mtx[2][3] = 0.0f;
    }


    void makeMtxTR(MtxPtr mtx, f32 tx, f32 ty, f32 tz, f32 rx, f32 ry, f32 rz) {
        f32 sinX = JMASinDegree(rx);
        f32 sinY = JMASinDegree(ry);
        f32 sinZ = JMASinDegree(rz);
        f32 cosX = JMACosDegree(rx);
        f32 cosY = JMACosDegree(ry);
        f32 cosZ = JMACosDegree(rz);

        mtx[0][0] = cosZ * cosY;
        mtx[1][0] = sinZ * cosY;
        mtx[2][0] = -sinY;

        mtx[0][1] = cosZ * sinY * sinX - sinZ * cosX;
        mtx[1][1] = sinZ * sinY * sinX + cosZ * cosX;
        mtx[2][1] = cosY * sinX;

        mtx[0][2] = cosZ * sinY * cosX + sinZ * sinX;
        mtx[1][2] = sinZ * sinY * cosX - cosZ * sinX;
        mtx[2][2] = cosY * cosX;

        mtx[0][3] = tx;
        mtx[1][3] = ty;
        mtx[2][3] = tz;
    }

    void makeMtxTR(MtxPtr mtx, const TVec3f& rTrans, const TVec3f& rRot) {
        makeMtxTR(mtx, rTrans.x, rTrans.y, rTrans.z, rRot.x, rRot.y, rRot.z);
    }

    void makeMtxTransRotateY(MtxPtr mtx, f32 tx, f32 ty, f32 tz, f32 ry) {
        makeMtxRotateY(mtx, ry);
        mtx[0][3] = tx;
        mtx[1][3] = ty;
        mtx[2][3] = tz;
    }

    void rotateMtxLocalX(MtxPtr mtx, f32 rad) {
        f32 cosX = JMACosRadian(rad);
        f32 sinX = JMASinRadian(rad);


        f32 result0 = cosX * mtx[0][1] + sinX * mtx[0][2];
        f32 result1 = cosX * mtx[1][1] + sinX * mtx[1][2];
        f32 result2 = cosX * mtx[2][1] + sinX * mtx[2][2];
        f32 result3 = -sinX * mtx[0][1] + cosX * mtx[0][2];
        f32 result4 = -sinX * mtx[1][1] + cosX * mtx[1][2];
        f32 result5 = -sinX * mtx[2][1] + cosX * mtx[2][2];

        mtx[0][1] = result0;
        mtx[1][1] = result1;
        mtx[2][1] = result2;
        mtx[0][2] = result3;
        mtx[1][2] = result4;
        mtx[2][2] = result5;
    }

    void rotateMtxLocalY(MtxPtr mtx, f32 rad) {
        f32 cosY = JMACosRadian(rad);
        f32 sinY = JMASinRadian(rad);


        f32 result0 = cosY * mtx[0][0] - sinY * mtx[0][2];
        f32 result1 = cosY * mtx[1][0] - sinY * mtx[1][2];
        f32 result2 = cosY * mtx[2][0] - sinY * mtx[2][2];
        f32 result3 = sinY * mtx[0][0] + cosY * mtx[0][2];
        f32 result4 = sinY * mtx[1][0] + cosY * mtx[1][2];
        f32 result5 = sinY * mtx[2][0] + cosY * mtx[2][2];

        mtx[0][0] = result0;
        mtx[1][0] = result1;
        mtx[2][0] = result2;
        mtx[0][2] = result3;
        mtx[1][2] = result4;
        mtx[2][2] = result5;
    }

    void rotateMtxLocalZ(MtxPtr mtx, f32 rad) {
        f32 cosZ = JMACosRadian(rad);
        f32 sinZ = JMASinRadian(rad);


        f32 result0 = cosZ * mtx[0][0] + sinZ * mtx[0][1];
        f32 result1 = cosZ * mtx[1][0] + sinZ * mtx[1][1];
        f32 result2 = cosZ * mtx[2][0] + sinZ * mtx[2][1];
        f32 result3 = -sinZ * mtx[0][0] + cosZ * mtx[0][1];
        f32 result4 = -sinZ * mtx[1][0] + cosZ * mtx[1][1];
        f32 result5 = -sinZ * mtx[2][0] + cosZ * mtx[2][1];

        mtx[0][0] = result0;
        mtx[1][0] = result1;
        mtx[2][0] = result2;
        mtx[0][1] = result3;
        mtx[1][1] = result4;
        mtx[2][1] = result5;
    }

    void rotateMtxLocalXDegree(MtxPtr mtx, f32 deg) {
        rotateMtxLocalX(mtx, PI_180 * deg);
    }

    void rotateMtxLocalYDegree(MtxPtr mtx, f32 deg) {
        rotateMtxLocalY(mtx, PI_180 * deg);
    }

    void rotateMtxLocalZDegree(MtxPtr mtx, f32 deg) {
        rotateMtxLocalZ(mtx, PI_180 * deg);
    }

    void preScaleMtx(MtxPtr mtx, f32 scale) {
        preScaleMtx(mtx, scale, scale, scale);
    }

    void preScaleMtx(MtxPtr mtx, const TVec3f& rScale) {
        preScaleMtx(mtx, rScale.x, rScale.y, rScale.z);
    }

    void preScaleMtx(MtxPtr mtx, f32 sx, f32 sy, f32 sz) {
        mtx[0][0] *= sx;
        mtx[1][0] *= sx;
        mtx[2][0] *= sx;
        mtx[0][1] *= sy;
        mtx[1][1] *= sy;
        mtx[2][1] *= sy;
        mtx[0][2] *= sz;
        mtx[1][2] *= sz;
        mtx[2][2] *= sz;
    }

    void scaleMtxToLocalMtx(MtxPtr dst, MtxPtr src, MtxPtr base, const TVec3f& scale) {
        TPos3f baseCopy;
        copyMatrix(&baseCopy, base);
        TVec3f translation;
        baseCopy.setTrans(TVec3f(0.0f, 0.0f, 0.0f));
        TPos3f inverse;
        fn_80007060(&inverse, &baseCopy);
        preScaleMtx(baseCopy.mMtx, scale.x, scale.y, scale.z);
        extractMtxTrans(src, &translation);
        PSMTXConcat(inverse.mMtx, src, dst);
        PSMTXConcat(baseCopy.mMtx, dst, dst);
        setMtxTrans(dst, translation.x, translation.y, translation.z);
    }

    void scaleMtxToLocalMtx(MtxPtr dst, MtxPtr base, const TVec3f& scale) {
        scaleMtxToLocalMtx(dst, dst, base, scale);
    }

    void scaleMtxToDir(TPos3f* pDst, const TVec3f& rDir, const TVec3f& rScale) {
        TVec3f axisX, axisY;
        fn_8003C220(&axisX, &axisY, rDir);

        TPos3f tmp1;
        tmp1.identity();
        TPos3f tmp2;
        tmp2.identity();

        tmp1.setXYZDir(axisX, rDir, axisY);

        // Copy rotation part from tmp1 to tmp2
        tmp2.mMtx[0][0] = axisX.x;
        tmp2.mMtx[0][1] = axisX.y;
        tmp2.mMtx[0][2] = axisX.z;
        tmp2.mMtx[1][0] = rDir.x;
        tmp2.mMtx[1][1] = rDir.y;
        tmp2.mMtx[1][2] = rDir.z;
        tmp2.mMtx[2][0] = axisY.x;
        tmp2.mMtx[2][1] = axisY.y;
        tmp2.mMtx[2][2] = axisY.z;

        pDst->zeroTrans();
        pDst->setScale(rScale.x, rScale.y, rScale.z);
        fn_80007380(pDst, pDst, &tmp2);
        fn_80007380(pDst, &tmp1, pDst);
    }

    void makeMtxTRS(MtxPtr mtx, f32 tx, f32 ty, f32 tz, f32 rx, f32 ry, f32 rz, f32 sx, f32 sy, f32 sz) {
        f32 sinX = JMASinDegree(rx);
        f32 sinY = JMASinDegree(ry);
        f32 sinZ = JMASinDegree(rz);
        f32 cosX = JMACosDegree(rx);
        f32 cosY = JMACosDegree(ry);
        f32 cosZ = JMACosDegree(rz);
        mtx[0][3] = tx;
        mtx[1][3] = ty;
        mtx[2][3] = tz;
        mtx[0][0] = sx * (cosZ * cosY);
        mtx[1][0] = sx * (sinZ * cosY);
        mtx[2][0] = -sinY * sx;
        mtx[0][1] = sy * (cosZ * sinY * sinX - sinZ * cosX);
        mtx[1][1] = sy * (sinZ * sinY * sinX + cosZ * cosX);
        mtx[2][1] = sy * (cosY * sinX);
        mtx[2][2] = sz * (cosY * cosX);
        mtx[1][2] = sz * (sinZ * sinY * cosX - cosZ * sinX);
        mtx[0][2] = sz * (cosZ * sinY * cosX + sinZ * sinX);
    }

    void makeMtxTRS(MtxPtr mtx, const TVec3f& rTrans, const TVec3f& rRot, const TVec3f& rScale) {
        makeMtxTRS(mtx, rTrans.x, rTrans.y, rTrans.z, rRot.x, rRot.y, rRot.z, rScale.x, rScale.y, rScale.z);
    }

    void setMtxAxisXYZ(MtxPtr mtx, const TVec3f& rAxisX, const TVec3f& rAxisY, const TVec3f& rAxisZ) {
        mtx[0][0] = rAxisX.x;
        mtx[1][0] = rAxisX.y;
        mtx[2][0] = rAxisX.z;
        mtx[0][1] = rAxisY.x;
        mtx[1][1] = rAxisY.y;
        mtx[2][1] = rAxisY.z;
        mtx[0][2] = rAxisZ.x;
        mtx[1][2] = rAxisZ.y;
        mtx[2][2] = rAxisZ.z;
    }

    void flattenMtx(MtxPtr dst, MtxPtr src, const TVec3f& rNormal) {
        TVec3f axisX, axisY, axisZ;
        MR::extractMtxXDir(src, &axisX);
        MR::extractMtxYDir(src, &axisY);
        MR::extractMtxZDir(src, &axisZ);

        JMAVECScaleAdd(&rNormal, &axisX, &axisX, -rNormal.dot(axisX));
        JMAVECScaleAdd(&rNormal, &axisY, &axisY, -rNormal.dot(axisY));
        JMAVECScaleAdd(&rNormal, &axisZ, &axisZ, -rNormal.dot(axisZ));

        MR::setMtxAxisXYZ(dst, axisX, axisY, axisZ);
    }

    void flattenMtx(MtxPtr mtx, const TVec3f& rNormal) {
        flattenMtx(mtx, mtx, rNormal);
    }

    void blendMtxRotate(MtxPtr mtxA, MtxPtr mtxB, f32 blend, MtxPtr dst) {
        MtxQuaternion quatA, quatB, quatR;
        fn_805C8CF0(&quatA, mtxA);
        fn_805C8CF0(&quatB, mtxB);
        fn_8053A800(&quatA, &quatB, &quatR, blend);
        fn_805C8310(dst, &quatR);
    }

    void blendMtxRotateSlerp(MtxPtr mtxA, MtxPtr mtxB, f32 blend, MtxPtr dst) {
        MtxQuaternion quatA, quatB, quatR;
        fn_805C8CF0(&quatA, mtxA);
        fn_805C8CF0(&quatB, mtxB);
        fn_805C8EC0(&quatA, &quatB, &quatR, blend);
        fn_805C8310(dst, &quatR);
    }

    void blendMtx(MtxPtr mtxA, MtxPtr mtxB, f32 blend, MtxPtr dst) {
        TVec3f transA, transB, transR;
        extractMtxTrans(mtxA, &transA);
        extractMtxTrans(mtxB, &transB);
        TVec3f sum, scaledA, scaledB;
        fn_80023780(&scaledB, &transB, blend);
        fn_80023780(&scaledA, &transA, 1.0f - blend);
        fn_800297B0(&sum, &scaledA, &scaledB);
        transR = sum;
        MtxQuaternion quatR, quatB, quatA;
        fn_805C8CF0(&quatA, mtxA);
        fn_805C8CF0(&quatB, mtxB);
        fn_8053A800(&quatA, &quatB, &quatR, blend);
        fn_805C8310(dst, &quatR);
        setMtxTrans(dst, transR.x, transR.y, transR.z);
    }

    void makeMtxWithoutScale(TPos3f* pDst, const TPos3f& rSrc) {
        TVec3f trans;
        rSrc.getTrans(trans);

        TVec3f axisX, axisY, axisZ;
        rSrc.getXYZDir(axisX, axisY, axisZ);

        pDst->setTrans(trans);

        MR::normalize(&axisX);
        MR::normalize(&axisY);
        MR::normalize(&axisZ);

        pDst->setXYZDir(axisX, axisY, axisZ);
    }

    void makeRTFromMtxPtr(TVec3f* trans, TVec3f* rotation, MtxPtr src, bool toDegree) {
        const TPos3f& matrix = *(const TPos3f*)src;
        if (trans) {
            matrix.getTrans(*trans);
        }
        if (rotation) {
            fn_80045980(&matrix, rotation);
            if (toDegree) {
                TVec3f degrees;
                fn_80023780(&degrees, rotation, 180.0f / PI);
                rotation->set<f32>(degrees);
            }
        }
    }

    void makeMtxSideUp(TPos3f* dst, const TVec3f& side, const TVec3f& up) {
        TVec3f axisZ, axisY, axisX;
        normalize(&axisX, side);
        PSVECCrossProduct(&axisX, &up, &axisZ);
        normalize(&axisZ);
        PSVECCrossProduct(&axisZ, &axisX, &axisY);
        dst->setXYZDir(axisX, axisY, axisZ);
    }

    void makeMtxSideUpPos(TPos3f* dst, const TVec3f& side, const TVec3f& up, const TVec3f& position) {
        TVec3f axisX, axisY, axisZ;
        normalize(&axisX, side);
        PSVECCrossProduct(&axisX, &up, &axisZ);
        normalize(&axisZ);
        PSVECCrossProduct(&axisZ, &axisX, &axisY);
        dst->setXYZDir(axisX, axisY, axisZ);
        dst->setTrans(position);
    }

    void makeMtxSideFront(TPos3f* dst, const TVec3f& side, const TVec3f& front) {
        TVec3f axisZ, axisY, axisX;
        normalize(&axisX, side);
        PSVECCrossProduct(&front, &axisX, &axisY);
        normalize(&axisY);
        PSVECCrossProduct(&axisX, &axisY, &axisZ);
        dst->setXYZDir(axisX, axisY, axisZ);
    }

    void makeMtxUpSide(TPos3f* dst, const TVec3f& up, const TVec3f& side) {
        TVec3f axisZ, axisY, axisX;
        normalize(&axisY, up);
        PSVECCrossProduct(&side, &axisY, &axisZ);
        normalize(&axisZ);
        PSVECCrossProduct(&axisY, &axisZ, &axisX);
        dst->setXYZDir(axisX, axisY, axisZ);
    }

    void makeMtxUpSidePos(TPos3f* dst, const TVec3f& up, const TVec3f& side, const TVec3f& position) {
        TVec3f axisX, axisY, axisZ;
        normalize(&axisY, up);
        PSVECCrossProduct(&side, &axisY, &axisZ);
        normalize(&axisZ);
        PSVECCrossProduct(&axisY, &axisZ, &axisX);
        dst->setXYZDir(axisX, axisY, axisZ);
        dst->setTrans(position);
    }

    void makeMtxUpFront(TPos3f* dst, const TVec3f& up, const TVec3f& front) {
        TVec3f axisZ, axisY, axisX;
        normalize(&axisY, up);
        PSVECCrossProduct(&axisY, &front, &axisX);
        normalize(&axisX);
        PSVECCrossProduct(&axisX, &axisY, &axisZ);
        dst->setXYZDir(axisX, axisY, axisZ);
    }

    void makeMtxUpFrontPos(TPos3f* dst, const TVec3f& up, const TVec3f& front, const TVec3f& position) {
        TVec3f axisX, axisY, axisZ;
        normalize(&axisY, up);
        PSVECCrossProduct(&axisY, &front, &axisX);
        normalize(&axisX);
        PSVECCrossProduct(&axisX, &axisY, &axisZ);
        dst->setXYZDir(axisX, axisY, axisZ);
        dst->setTrans(position);
    }

    void makeMtxFrontSidePos(TPos3f* dst, const TVec3f& front, const TVec3f& side, const TVec3f& position) {
        TVec3f axisX, axisY, axisZ;
        normalize(&axisZ, front);
        PSVECCrossProduct(&axisZ, &side, &axisY);
        normalize(&axisY);
        PSVECCrossProduct(&axisY, &axisZ, &axisX);
        dst->setXYZDir(axisX, axisY, axisZ);
        dst->setTrans(position);
    }

    void makeMtxFrontUp(TPos3f* dst, const TVec3f& front, const TVec3f& up) {
        TVec3f axisZ, axisY, axisX;
        normalize(&axisZ, front);
        PSVECCrossProduct(&up, &axisZ, &axisX);
        normalize(&axisX);
        PSVECCrossProduct(&axisZ, &axisX, &axisY);
        dst->setXYZDir(axisX, axisY, axisZ);
    }

    void makeMtxFrontUpPos(TPos3f* dst, const TVec3f& front, const TVec3f& up, const TVec3f& position) {
        TVec3f axisX, axisY, axisZ;
        normalize(&axisZ, front);
        PSVECCrossProduct(&up, &axisZ, &axisX);
        normalize(&axisX);
        PSVECCrossProduct(&axisZ, &axisX, &axisY);
        dst->setXYZDir(axisX, axisY, axisZ);
        dst->setTrans(position);
    }

    void makeMtxUpNoSupport(TPos3f* pDst, const TVec3f& rUp) {
        TVec3f support;
        if (fn_8003FED0(rUp) == 2) {
            support.set<f32>(0.0f, 1.0f, 0.0f);
        } else {
            support.set<f32>(0.0f, 0.0f, 1.0f);
        }

        TVec3f axisX, axisY, axisZ;
        MR::normalize(&axisY, rUp);

        PSVECCrossProduct(&axisY, &support, &axisX);
        MR::normalize(&axisX);

        PSVECCrossProduct(&axisX, &axisY, &axisZ);

        pDst->setXYZDir(axisX, axisY, axisZ);
    }

    void makeMtxUpNoSupportPos(TPos3f* pDst, const TVec3f& rUp, const TVec3f& rPos) {
        TVec3f support;
        if (fn_8003FED0(rUp) == 2) {
            support.set< f32 >(0.0f, 1.0f, 0.0f);
        } else {
            support.set< f32 >(0.0f, 0.0f, 1.0f);
        }

        MR::makeMtxUpFrontPos(pDst, rUp, support, rPos);
    }

    void makeMtxFrontNoSupport(TPos3f* pDst, const TVec3f& rFront) {
        TVec3f support;
        if (fn_8003FED0(rFront) == 1) {
            support.set<f32>(1.0f, 0.0f, 0.0f);
        } else {
            support.set<f32>(0.0f, 1.0f, 0.0f);
        }

        TVec3f axisX, axisY, axisZ;
        MR::normalize(&axisZ, rFront);

        PSVECCrossProduct(&support, &axisZ, &axisX);
        MR::normalize(&axisX);

        PSVECCrossProduct(&axisZ, &axisX, &axisY);

        pDst->setXYZDir(axisX, axisY, axisZ);
    }

    void makeMtxFrontNoSupportPos(TPos3f* pDst, const TVec3f& rFront, const TVec3f& rPos) {
        TVec3f support;
        if (fn_8003FED0(rFront) == 1) {
            support.set< f32 >(1.0f, 0.0f, 0.0f);
        } else {
            support.set< f32 >(0.0f, 1.0f, 0.0f);
        }

        MR::makeMtxFrontUpPos(pDst, rFront, support, rPos);
    }

    void turnMtxToXDirRate(TPos3f* matrix, const TVec3f& direction, f32 amount) {
        MtxQuaternion rotation;
        fn_80007930(matrix, &rotation);
        fn_8003D7D0(&rotation, &rotation, direction, amount);
        fn_80046590(matrix, rotation);
    }

    void turnMtxToXDirDegree(TPos3f* matrix, const TVec3f& direction, f32 amount) {
        MtxQuaternion rotation;
        fn_80007930(matrix, &rotation);
        fn_8003D680(&rotation, &rotation, direction, PI_180 * amount);
        fn_80046590(matrix, rotation);
    }

    void turnMtxToYDirRate(TPos3f* matrix, const TVec3f& direction, f32 amount) {
        MtxQuaternion rotation;
        fn_80007930(matrix, &rotation);
        fn_8003D8A0(&rotation, &rotation, direction, amount);
        fn_80046590(matrix, rotation);
    }

    void turnMtxToYDirDegree(TPos3f* matrix, const TVec3f& direction, f32 amount) {
        MtxQuaternion rotation;
        fn_80007930(matrix, &rotation);
        fn_8003D6F0(&rotation, &rotation, direction, PI_180 * amount);
        fn_80046590(matrix, rotation);
    }

    void turnMtxToLocalDirDegree(TPos3f* pMtx, const TVec3f& rLocalAxis, const TVec3f& rDir, f32 degree) {

        f32 y0 = rLocalAxis.y * pMtx->mMtx[0][1];
        f32 y1 = rLocalAxis.y * pMtx->mMtx[1][1];
        f32 y2 = rLocalAxis.y * pMtx->mMtx[2][1];
        f32 x0 = rLocalAxis.x * pMtx->mMtx[0][0];
        f32 x1 = rLocalAxis.x * pMtx->mMtx[1][0];
        f32 x2 = rLocalAxis.x * pMtx->mMtx[2][0];
        f32 z0 = rLocalAxis.z * pMtx->mMtx[0][2];
        f32 z1 = rLocalAxis.z * pMtx->mMtx[1][2];
        f32 z2 = rLocalAxis.z * pMtx->mMtx[2][2];
        f32 worldX = z0 + (x0 + y0);
        f32 worldY = z1 + (x1 + y1);
        f32 worldZ = z2 + (x2 + y2);

        TVec3f worldAxis;
        worldAxis.set< f32 >(worldX, worldY, worldZ);

        MtxQuaternion quat;
        fn_80007930(pMtx, &quat);
        fn_8003D520(&quat, &quat, worldAxis, rDir, PI_180 * degree);
        fn_80046590(pMtx, quat);
    }

    void makeMtxMoment(TPos3f* pMtx, const TVec3f& rMoment) {
        pMtx->identity();

        if (!rMoment.isZero()) {
            TVec3f dir(rMoment);
            f32 mag;
            fn_8003E840(&mag, &dir, dir);
            pMtx->makeRotate(dir, mag);
        }
    }

    template<>
    f32 sqrt<f32>(register f32 value) {
        f32 product;
        register f32 result = value;
        if (value > 0.0f) {
            asm { frsqrte result, value }
            product = result * value;
            result = -(product * result - 3.0f);
            result *= product;
            result *= 0.5f;
        }
        return result;
    }

    MtxPtr tmpMtxTrans(const TVec3f& translation) {
        setMtxTrans(mtrans_org, translation.x, translation.y, translation.z);
        return mtrans_org;
    }

    bool isRotAxisY(MtxPtr a, MtxPtr b) {
        TVec3f axisA, axisB;
        fn_8000E260((const TRot3f*)a, &axisA);
        fn_8000E260((const TRot3f*)b, &axisB);
        bool result = false;
        if (JGeometry::TUtil<f32>::epsilonEquals(axisA.x, axisB.x, 0.000003814697265625f)
            && JGeometry::TUtil<f32>::epsilonEquals(axisA.y, axisB.y, 0.000003814697265625f)
            && JGeometry::TUtil<f32>::epsilonEquals(axisA.z, axisB.z, 0.000003814697265625f)) {
            result = true;
        }
        return result;
    }

    void calcMtxRotAxis(TVec3f* out, MtxPtr a, MtxPtr b) {
        TVec3f localY(0.0f, 1.0f, 0.0f);
        Mtx inverse;
        PSMTXInverse(a, inverse);
        TVec3f axisA, axisB, cross;
        fn_805C8730(inverse, &localY, &axisA);
        fn_805C8730(b, &axisA, &axisB);
        PSVECCrossProduct(&localY, &axisB, &cross);
        if (normalizeOrZero(&cross)) {
            *out = localY;
        } else {
            *out = cross;
        }
    }

    void setMtxTrans(MtxPtr mtx, f32 x, f32 y, f32 z) {
        mtx[0][3] = x;
        mtx[1][3] = y;
        mtx[2][3] = z;
    }

    void addTransMtx(MtxPtr mtx, const TVec3f &rTrans) {
        mtx[0][3] += rTrans.x;
        mtx[1][3] += rTrans.y;
        mtx[2][3] += rTrans.z;
    }

    void addTransMtxLocal(MtxPtr mtx, const TVec3f &rVec) {
        MR::addTransMtxLocalX(mtx, rVec.x);
        MR::addTransMtxLocalY(mtx, rVec.y);
        MR::addTransMtxLocalZ(mtx, rVec.z);
    }
    
    void addTransMtxLocalX(MtxPtr mtx, f32 x) {
        mtx[0][3] += mtx[0][0] * x;
        mtx[1][3] += mtx[1][0] * x;
        mtx[2][3] += mtx[2][0] * x;
    }

    void addTransMtxLocalY(MtxPtr mtx, f32 y) {
        mtx[0][3] += mtx[0][1] * y;
        mtx[1][3] += mtx[1][1] * y;
        mtx[2][3] += mtx[2][1] * y;
    }

    void addTransMtxLocalZ(MtxPtr mtx, f32 z) {
        mtx[0][3] += mtx[0][2] * z;
        mtx[1][3] += mtx[1][2] * z;
        mtx[2][3] += mtx[2][2] * z;
    }

    void extractMtxXDir(MtxPtr mtx, TVec3f *pDir) {
        pDir->x = mtx[0][0];
        pDir->y = mtx[1][0];
        pDir->z = mtx[2][0];
    }

    void extractMtxYDir(MtxPtr mtx, TVec3f *pDir) {
        pDir->x = mtx[0][1];
        pDir->y = mtx[1][1];
        pDir->z = mtx[2][1];
    }

    void extractMtxZDir(MtxPtr mtx, TVec3f *pDir) {
        pDir->x = mtx[0][2];
        pDir->y = mtx[1][2];
        pDir->z = mtx[2][2];
    }

    void extractMtxXYZDir(MtxPtr mtx, TVec3f *pX, TVec3f *pY, TVec3f *pZ) {
        MR::extractMtxXDir(mtx, pX);
        MR::extractMtxYDir(mtx, pY);
        MR::extractMtxZDir(mtx, pZ);
    }

    void extractMtxTrans(MtxPtr mtx, TVec3f *pTrans) {
        pTrans->x = mtx[0][3];
        pTrans->y = mtx[1][3];
        pTrans->z = mtx[2][3];
    }

    /*
    f32 sqrt(f32 val) {
        if (val < 0.0f) {
            return val;
        }

        #ifdef __MWERKS__
        f64 sq = __frsqrte(val);
        #else
        f32 sq = 0.0f; 
        #endif

        return ((-(((sq * val) * sq) - 3.0f) * (sq * val)) * 0.5f);
    }*/

    bool isSameMtx(MtxPtr a, MtxPtr b) {
        f32* a2 = (f32*)a;
        f32* b2 = (f32*)b;
        for (u32 i = 0; i < 12; a2++, b2++, i++) {
            if (*a2 != *b2) {
                return false;
            }
        }
        return true; 
    }

    bool isSameMtxRot(MtxPtr a, MtxPtr b) {
        f32* a2 = (f32*)a;
        f32* b2 = (f32*)b;
        for (u32 i = 0; i < 12; a2++, b2++, i++) {
            if ((i % 4) == 3) {
                continue;
            }
            if (*a2 != *b2) {
                return false;
            }
        }
        return true; 
    }

    MtxPtr tmpMtxScale(f32 x, f32 y, f32 z) {
        tmpmtx_sc[0][0] = x;
        tmpmtx_sc[1][1] = y;
        tmpmtx_sc[2][2] = z;
        return tmpmtx_sc;
    }

    MtxPtr tmpMtxRotXRad(f32 angle) {
        f32 cos = JMACosRadian(angle);
        f32 sin = JMASinRadian(angle);
        tmpmtx_rx[1][1] = cos;
        tmpmtx_rx[2][1] = sin;
        tmpmtx_rx[1][2] = -sin;
        tmpmtx_rx[2][2] = cos;
        return tmpmtx_rx;
    }

    MtxPtr tmpMtxRotYRad(f32 angle) {
        f32 cos = JMACosRadian(angle);
        f32 sin = JMASinRadian(angle);
        tmpmtx_ry[0][0] = cos;
        tmpmtx_ry[0][2] = sin;
        tmpmtx_ry[2][0] = -sin;
        tmpmtx_ry[2][2] = cos;
        return tmpmtx_ry;
    }

    MtxPtr tmpMtxRotZRad(f32 angle) {
        f32 cos = JMACosRadian(angle);
        f32 sin = JMASinRadian(angle);
        tmpmtx_rz[0][0] = cos;
        tmpmtx_rz[1][0] = sin;
        tmpmtx_rz[0][1] = -sin;
        tmpmtx_rz[1][1] = cos;
        return tmpmtx_rz;
    }

    MtxPtr tmpMtxRotXDeg(f32 angle) {
        f32 cos = JMACosDegree(angle);
        f32 sin = JMASinDegree(angle);
        tmpmtx_rx[1][1] = cos;
        tmpmtx_rx[2][1] = sin;
        tmpmtx_rx[1][2] = -sin;
        tmpmtx_rx[2][2] = cos;
        return tmpmtx_rx;
    }

    MtxPtr tmpMtxRotYDeg(f32 angle) {
        f32 cos = JMACosDegree(angle);
        f32 sin = JMASinDegree(angle);
        tmpmtx_ry[0][0] = cos;
        tmpmtx_ry[0][2] = sin;
        tmpmtx_ry[2][0] = -sin;
        tmpmtx_ry[2][2] = cos;
        return tmpmtx_ry;
    }

    MtxPtr tmpMtxRotZDeg(f32 angle) {
        f32 cos = JMACosDegree(angle);
        f32 sin = JMASinDegree(angle);
        tmpmtx_rz[0][0] = cos;
        tmpmtx_rz[1][0] = sin;
        tmpmtx_rz[0][1] = -sin;
        tmpmtx_rz[1][1] = cos;
        return tmpmtx_rz;
    }

    void orderRotateMtx(s16 idx, const TVec3f &rSrc, MtxPtr mtx) {
        MtxPtr xRot = MR::tmpMtxRotXRad(rSrc.x);
        MtxPtr yRot = MR::tmpMtxRotYRad(rSrc.y);
        MtxPtr zRot = MR::tmpMtxRotZRad(rSrc.z);

        MtxPtr v9 = yRot;
        MtxPtr v10;
        MtxPtr v12;

        switch (idx) {
            case 0:
                v12 = v9;
                v10 = xRot;
                v9 = zRot;
                break;
            case 1:
                v10 = xRot;
                v12 = zRot;
                break;
            case 2:
               v10 = v9;
                v12 = xRot;
                v9 = zRot;
                break;
            case 3:
                 v10 = v9;
                v12 = zRot;
                v9 = xRot;
                break;
            case 4:
                v10 = zRot;
                v12 = xRot;
                v9 = zRot;
                break;
            case 5:
                v12 = v9;
                v10 = zRot;
                v9 = xRot;
                break;
        }
        
        PSMTXConcat(v12, v10, mtx);
        PSMTXConcat(v9, mtx, mtx);
    }

    void inverseConcatMtx(MtxPtr a1, MtxPtr a2, TMtx34f *pMtx) {
        Mtx mtx;
        PSMTXInverse(a1, mtx);
        PSMTXConcat(mtx, a2, *pMtx);
    }
};

extern "C" {
    f32 PSVECMag(const Vec*);
    void fn_805C8AC0(const Vec*, Vec*);
    f64 fn_8063DC98(f64);
    f64 fn_8063D88C(f64);
}
namespace JGeometry {
    template<>
    void TPosition3<TMatrix34<SMatrix34C<f32> > >::makeRotate(const TVec3f& axis, f32 angle) {
        zeroTrans();
        TVec3f vec;
        vec.set<f32>(axis);
        PSVECMag(&vec);
        fn_805C8AC0(&vec, &vec);
        f32 s = fn_8063DC98(angle);
        f32 z, y, x, c;
        c = fn_8063D88C(angle);
        f32 zz, yy, xx, negc;
        negc = 1.0f - c;
        x = vec.x; y = vec.y; z = vec.z;
        xx = x * x; yy = y * y; zz = z * z;
        this->mMtx[0][0] = c + negc * xx;
        this->mMtx[0][1] = negc * x * y - s * z;
        this->mMtx[0][2] = negc * x * z + s * y;
        this->mMtx[1][0] = negc * x * y + s * z;
        this->mMtx[1][1] = c + negc * yy;
        this->mMtx[1][2] = negc * y * z - s * x;
        this->mMtx[2][0] = negc * x * z - s * y;
        this->mMtx[2][1] = negc * y * z + s * x;
        this->mMtx[2][2] = c + negc * zz;
    }
}

namespace JGeometry {
    bool TVec3<f32>::isZero() const {
        register const Vec* src = this;
        register f32 xy, z;
        asm {
            psq_l xy, 0(src), 0, 0
            lfs z, 8(src)
            ps_mul xy, xy, xy
            ps_madd z, z, z, xy
            ps_sum0 z, z, xy, xy
        }
        return z <= 0.000003814697265625f;
    }
}

// Concatenate after clearing the right matrix's translation, then restore it in dst.
extern "C" void fn_80046A70(MtxPtr dst, MtxPtr left, MtxPtr right) {
    TVec3f translation(right[0][3], right[1][3], right[2][3]);
    right[0][3] = 0.0f;
    right[1][3] = 0.0f;
    right[2][3] = 0.0f;
    PSMTXConcat(left, right, dst);
    dst[0][3] = translation.x;
    dst[1][3] = translation.y;
    dst[2][3] = translation.z;
}

extern "C" f32 fn_80007B60(f32);
extern "C" f32 fn_80045970(register f32 value) {
    asm { fres value, value }
    return value;
}

extern "C" void fn_800457F0(TVec3f* trans, TVec3f* rotation, TVec3f* scaleOut, const TPos3f* src, bool toDegree) {
    TPos3f inverseScale, normalized;
    TVec3f scale;
    {
        f32 yy = src->mMtx[1][0];
        f32 xx = src->mMtx[0][0];
        f32 zz = src->mMtx[2][0];
        yy *= yy;
        xx *= xx;
        zz *= zz;
        scale.x = fn_80007B60(xx + yy + zz);
    }
    {
        f32 yy = src->mMtx[1][1];
        f32 xx = src->mMtx[0][1];
        f32 zz = src->mMtx[2][1];
        yy *= yy;
        xx *= xx;
        zz *= zz;
        scale.y = fn_80007B60(xx + yy + zz);
    }
    {
        f32 yy = src->mMtx[1][2];
        f32 xx = src->mMtx[0][2];
        f32 zz = src->mMtx[2][2];
        yy *= yy;
        xx *= xx;
        zz *= zz;
        scale.z = fn_80007B60(xx + yy + zz);
    }
    inverseScale.identity();
    f32 invX, invY, invZ;
    invZ = fn_80045970(scale.z);
    invY = fn_80045970(scale.y);
    invX = fn_80045970(scale.x);
    inverseScale.setScale(invX, invY, invZ);
    fn_80007380(&normalized, src, &inverseScale);
    if (trans) normalized.getTrans(*trans);
    if (rotation) {
        fn_80045980(&normalized, rotation);
        if (toDegree) {
            TVec3f degrees;
            fn_80023780(&degrees, rotation, 180.0f / PI);
            rotation->set<f32>(degrees);
        }
    }
    if (scaleOut) scaleOut->set<f32>(scale);
}

extern "C" void fn_805C8280(MtxPtr, f32, f32, f32);

ALWAYS_INLINE f32 matrixSafeReciprocal(f32 value) {
    return MR::isNearZero(value, 0.001f) ? 0.0f : 1.0f / value;
}

// Extract a diagonal scale matrix and remove that scale from the source basis.
extern "C" void fn_80046D50(MtxPtr rotation, MtxPtr scale, MtxPtr src) {
    Mtx inverseScale;
    TVec3f lengthsSquared;
    lengthsSquared.x = src[0][0] * src[0][0] + src[1][0] * src[1][0] + src[2][0] * src[2][0];
    lengthsSquared.y = src[0][1] * src[0][1] + src[1][1] * src[1][1] + src[2][1] * src[2][1];
    lengthsSquared.z = src[0][2] * src[0][2] + src[1][2] * src[1][2] + src[2][2] * src[2][2];
    fn_805C8280(scale, MR::sqrt<f32>(lengthsSquared.x), MR::sqrt<f32>(lengthsSquared.y), MR::sqrt<f32>(lengthsSquared.z));
    f32 invZ = matrixSafeReciprocal(scale[2][2]);
    f32 invY = matrixSafeReciprocal(scale[1][1]);
    f32 invX = matrixSafeReciprocal(scale[0][0]);
    fn_805C8280(inverseScale, invX, invY, invZ);
    PSMTXConcat(src, inverseScale, rotation);
}

extern "C" f32 fn_8000D7A0(f32);
extern "C" void fn_80046300(TPos3f* pMtx) {
        TVec3f axisZ, axisY, axisX;

        pMtx->getXYZDir(axisX, axisY, axisZ);

        Vec* zAxis;
        Vec* yAxis;
        yAxis = reinterpret_cast<Vec*>(&axisY);
        zAxis = reinterpret_cast<Vec*>(&axisZ);
        PSVECCrossProduct(yAxis, zAxis, &axisX);
        PSVECCrossProduct(zAxis, &axisX, yAxis);

        PSVECMag(&axisX);
        fn_805C8AC0(&axisX, &axisX);
        PSVECMag(yAxis);
        fn_805C8AC0(yAxis, yAxis);

        pMtx->setXYZDir(axisX, *(TVec3f*)yAxis, *(TVec3f*)zAxis);

        TVec3f zDir;
        f32 z = pMtx->mMtx[2][2], y = pMtx->mMtx[1][2], x = pMtx->mMtx[0][2];
        zDir.set< f32 >(x, y, z);

        f32 magAll = pMtx->mMtx[1][0] * pMtx->mMtx[1][0] + pMtx->mMtx[0][0] * pMtx->mMtx[0][0] + pMtx->mMtx[2][0] * pMtx->mMtx[2][0] +
                     pMtx->mMtx[0][1] * pMtx->mMtx[0][1] + pMtx->mMtx[1][1] * pMtx->mMtx[1][1] + pMtx->mMtx[2][1] * pMtx->mMtx[2][1] +
                     pMtx->mMtx[0][2] * pMtx->mMtx[0][2] + pMtx->mMtx[1][2] * pMtx->mMtx[1][2] + pMtx->mMtx[2][2] * pMtx->mMtx[2][2];

        fn_80007B60(magAll);

        if (pMtx) {
            f32 magX = pMtx->mMtx[1][0] * pMtx->mMtx[1][0] + pMtx->mMtx[0][0] * pMtx->mMtx[0][0] + pMtx->mMtx[2][0] * pMtx->mMtx[2][0];
            f32 invSqrtX = fn_8000D7A0(magX);
            f32 scaledX0 = invSqrtX * pMtx->mMtx[0][0];
            f32 scaledX1 = invSqrtX * pMtx->mMtx[1][0];
            f32 scaledX2 = invSqrtX * pMtx->mMtx[2][0];
            pMtx->mMtx[0][0] = scaledX0;
            pMtx->mMtx[1][0] = scaledX1;
            pMtx->mMtx[2][0] = scaledX2;


            f32 magY = pMtx->mMtx[1][1] * pMtx->mMtx[1][1] + pMtx->mMtx[0][1] * pMtx->mMtx[0][1] + pMtx->mMtx[2][1] * pMtx->mMtx[2][1];
            f32 invSqrtY = fn_8000D7A0(magY);
            f32 scaledY0 = invSqrtY * pMtx->mMtx[0][1];
            f32 scaledY1 = invSqrtY * pMtx->mMtx[1][1];
            f32 scaledY2 = invSqrtY * pMtx->mMtx[2][1];
            pMtx->mMtx[0][1] = scaledY0;
            pMtx->mMtx[1][1] = scaledY1;
            pMtx->mMtx[2][1] = scaledY2;


            f32 magZ = pMtx->mMtx[1][2] * pMtx->mMtx[1][2] + pMtx->mMtx[0][2] * pMtx->mMtx[0][2] + pMtx->mMtx[2][2] * pMtx->mMtx[2][2];
            f32 invSqrtZ = fn_8000D7A0(magZ);
            f32 scaledZ0 = invSqrtZ * pMtx->mMtx[0][2];
            f32 scaledZ1 = invSqrtZ * pMtx->mMtx[1][2];
            f32 scaledZ2 = invSqrtZ * pMtx->mMtx[2][2];
            pMtx->mMtx[0][2] = scaledZ0;
            pMtx->mMtx[1][2] = scaledZ1;
            pMtx->mMtx[2][2] = scaledZ2;

        }

        pMtx->mMtx[0][2] = zDir.x;
        pMtx->mMtx[1][2] = zDir.y;
        pMtx->mMtx[2][2] = zDir.z;
    }

