#include "Game/Screen/PostFog.hpp"
#include "Game/Screen/CopyFilterNegater.hpp"
#include "Game/Screen/ImageEffectLocalUtil.hpp"
#include "Game/Screen/ImageEffectResource.hpp"
#include "Game/Screen/ImageEffectSystemHolder.hpp"
#include "Game/Util/CameraUtil.hpp"
#include "Game/Util/Color.hpp"
#include "Game/Util/DrawUtil.hpp"
#include "Game/Util/ScreenUtil.hpp"
#include "JSystem/JUtility/JUTTexture.hpp"
#include "decomp.h"
#include "revolution/gx/GXEnum.h"

EXTERN_UNKNOWN_FUNC(f32, 8001E930, f32, f32, f32, f32, f32);

PostFog::PostFog(const char* pName) : ImageEffectBase(pName), mDepthTexture(), _1C(), mInnerRadius(), mOuterRadius(10000), mA(255), mGradientType(-1) {
    MR::connectToSceneImageEffect(this);
    MR::createImageEffectSystemHolder();
    MR::getImageEffectResource()->createFogTexture();
    mDepthTexture = MR::getImageEffectResource()->_24;
    mR = 255;
    mG = 255;
    mB = 255;
}

void PostFog::draw() const {
    if (!isSomething()) {
        return;
    }

    capture();
    ImageEffectLocalUtil::setupDrawTexture();
    ImageEffectLocalUtil::drawTexture(MR::getImageEffectResource()->_4, 2, 0, 0xFF, ImageEffectLocalUtil::TexDrawType_0, GX_TEXMAP0);
    drawFog(0, 0, MR::getFrameBufferWidth(), MR::getFrameBufferHeight(), false);
}

void PostFog::capture() const {
    CopyFilterNegater negater;
    GXSetCopyClamp(static_cast< GXFBClamp >(GX_CLAMP_TOP | GX_CLAMP_BOTTOM));
    ImageEffectLocalUtil::capture(MR::getImageEffectResource()->_4, 1, 0, GX_TF_RGB565, false, 0);
    ImageEffectLocalUtil::capture(mDepthTexture, 1, 0, GX_TF_Z16, false, 0);
}

// TODO: regswaps
void PostFog::drawFog(s16 left, s16 top, s16 right, s16 bottom, bool a5) const {
    Mtx44 projectionMtx;
    C_MTXOrtho(projectionMtx, 0.0f, MR::getFrameBufferHeight(), 0.0f, MR::getFrameBufferWidth(), -10000.0f, 10000.0f);
    GXSetProjection(projectionMtx, GX_ORTHOGRAPHIC);
    MR::loadViewMtxFor2DModel();

    GXClearVtxDesc();
    GXSetVtxAttrFmt(GX_VTXFMT1, GX_VA_POS, GX_POS_XYZ, GX_S16, 0);
    GXSetVtxAttrFmt(GX_VTXFMT1, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT1, GX_VA_TEX1, GX_TEX_ST, GX_F32, 0);
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX1, GX_DIRECT);

    TMtx34f mtx;
    mtx.identity();
    GXLoadPosMtxImm(mtx, 0);
    GXSetCurrentMtx(0);

    GXSetCullMode(GX_CULL_NONE);
    GXSetClipMode(GX_CLIP_ENABLE);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, 0, GX_DF_NONE, GX_AF_NONE);
    GXSetChanMatColor(GX_COLOR0A0, Color8(mR, mG, mB, 255));
    GXSetChanAmbColor(GX_COLOR0A0, Color8(0, 0, 0, 255));
    GXSetFog(GX_FOG_NONE, 0.0f, 0.0f, 0.0f, 0.0f, Color8(0, 0, 0, 0));
    GXSetColorUpdate(GX_TRUE);
    GXSetAlphaUpdate(GX_FALSE);
    GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
    GXSetZCompLoc(GX_TRUE);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_OR, GX_ALWAYS, 0);
    GXSetDither(GX_TRUE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);

    f32 v1;
    f32 v2;

    if (mOuterRadius > mInnerRadius) {
        v1 = mInnerRadius / 10000.0f;
        v2 = mOuterRadius / 10000.0f;
    } else {
        v2 = mInnerRadius / 10000.0f;
        v1 = mOuterRadius / 10000.0f;
    }

    v1 = 1.0f - (1.0f - v1) * (1.0f - v1);
    v2 = 1.0f - (1.0f - v2) * (1.0f - v2);

    if (MR::getNearZ() != 100.0f) {
        v1 = fn_8001E930(v1, 100.0f, 800000.0f, MR::getNearZ(), MR::getFarZ());
        v2 = fn_8001E930(v2, 100.0f, 800000.0f, MR::getNearZ(), MR::getFarZ());
        if (v2 - v1 < 0.001953f) {
            v1 = v2 - 0.001953f;
        }
    }

    f32 v3;

    if (v2 - v1 != 0.0f) {
        v3 = 1.0f / (v2 - v1);
    } else {
        v3 = 1.0f;
    }

    f32 v4 = -v3 * v1;

    GXSetNumTexGens(2);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX1, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetTexCoordScaleManually(GX_TEXCOORD0, GX_FALSE, 0, 0);
    GXSetTexCoordBias(GX_TEXCOORD0, GX_FALSE, GX_FALSE);
    GXSetNumTevStages(1);
    GXSetNumIndStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
    GXSetTevSwapModeTable(GX_TEV_SWAP0, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
    GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_RASC, GX_CC_ONE, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_KONST, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevIndirect(GX_TEVSTAGE0, GX_INDTEXSTAGE0, GX_ITF_8, GX_ITB_NONE, GX_ITM_0, GX_ITW_OFF, GX_ITW_0, GX_FALSE, GX_FALSE, GX_ITBA_OFF);
    GXSetIndTexOrder(GX_INDTEXSTAGE0, GX_TEXCOORD0, GX_TEXMAP0);

    s8 exp = 0;

    while (v3 > 0.99902344f && exp < 46) {
        v3 *= 0.5f;
        exp++;
    }

    while (0.0f < v3 && v3 < 0.5f && exp > -17) {
        v3 *= 2.0f;
        exp--;
    }

    Mtx23 indMtx = {};
    indMtx[0][0] = v3 * 0.00390625f;
    indMtx[0][1] = v3;
    GXSetIndTexMtx(GX_ITM_0, indMtx, exp - 1);
    GXSetIndTexCoordScale(GX_INDTEXSTAGE0, GX_ITS_1, GX_ITS_1);

    GXSetTevKAlphaSel(GX_TEVSTAGE0, GX_TEV_KASEL_K0_A);
    u8 v6 = mA * getIntensity();
    GXSetTevKColor(GX_KCOLOR0, Color8(v6, v6, v6, v6));

    if (a5) {
        GXSetBlendMode(GX_BM_NONE, GX_BL_ONE, GX_BL_ZERO, GX_LO_CLEAR);
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_ZERO);
    }

    mDepthTexture->load(GX_TEXMAP0);
    getGradientTexture()->load(GX_TEXMAP1);

    GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT1, 4);
    {
        GXPosition3s16(left, bottom, 0);
        GXTexCoord2f32(0.0f, 1.0f);
        GXTexCoord2f32(v4, v4);
        GXPosition3s16(left, top, 0);
        GXTexCoord2f32(0.0f, 0.0f);
        GXTexCoord2f32(v4, v4);
        GXPosition3s16(right, bottom, 0);
        GXTexCoord2f32(1.0f, 1.0f);
        GXTexCoord2f32(v4, v4);
        GXPosition3s16(right, top, 0);
        GXTexCoord2f32(1.0f, 0.0f);
        GXTexCoord2f32(v4, v4);
    }
    GXEnd();

    GXSetNumTevStages(1);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXSetNumIndStages(0);
    GXSetTevDirect(GX_TEVSTAGE0);
    GXSetTevDirect(GX_TEVSTAGE1);
    GXSetTevDirect(GX_TEVSTAGE2);
    GXSetTevDirect(GX_TEVSTAGE3);

    ImageEffectLocalUtil::setupDrawTexture();
}

JUTTexture* PostFog::getGradientTexture() const {
    s32 type = mGradientType;

    if (type < 0) {
        return MR::getImageEffectResource()->mFogGradTexture[0];
    }

    return MR::getImageEffectResource()->mFogGradTexture[type];
}
