#include "Game/Screen/ImageEffectResource.hpp"
#include "Game/System/ResourceHolder.hpp"
#include "Game/Util/MemoryUtil.hpp"
#include "Game/Util/ObjUtil.hpp"
#include "Game/Util/SceneUtil.hpp"
#include "Game/Util/ScreenUtil.hpp"
#include "revolution/gx/GXEnum.h"
#include <JSystem/JKernel/JKRSolidHeap.hpp>
#include <JSystem/JUtility/JUTTexture.hpp>
#include <cstdio>
#include <decomp.h>

EXTERN_UNKNOWN_FUNC(void*, 8004BFA0, ResourceHolder*, const char*)

// FIXME: `MR::CurrentHeapRestorer` dtor argument placement
JUTTexture* ImageEffectResource::createTexture(f32 scale, GXTexFmt format, GXTexWrapMode wrap, GXTexFilter filter) {
    JUTTexture* texture;

    MR::CurrentHeapRestorer heapRestorer(MR::getSceneHeapGDDR3());

    texture = new JUTTexture(scale * (s32)MR::getFrameBufferWidth(), scale * (s32)MR::getFrameBufferHeight(), format);
    texture->mWrapS = wrap;
    texture->mWrapT = wrap;
    texture->mMinType = filter;
    texture->mMagType = filter;

    return texture;
}

// FIXME: string load
ImageEffectResource::ImageEffectResource() : _0(), _4(), _8(), _C(), _10(), _14(), _18(), _1C(), _20(), _24(), mFogGradTexture(), mFogGradNum(), mFogGradArc(), _34(GX_TF_RGBA8) {
    if (MR::isEqualStageName("AndoYoshiStage")) {
        _34 = GX_TF_RGB565;
    }
}

void ImageEffectResource::createBloomTexture() {
    if (_0 == nullptr) {
        _0 = createTexture(1.0f, _34, GX_CLAMP, GX_LINEAR);
    }

    if (_4 == nullptr) {
        _4 = createTexture(0.5f, GX_TF_RGB565, GX_CLAMP, GX_LINEAR);
    }

    if (_C == nullptr) {
        _C = createTexture(0.25f, GX_TF_RGB565, GX_CLAMP, GX_LINEAR);
    }

    if (_10 == nullptr) {
        _10 = createTexture(0.25f, GX_TF_RGB565, GX_CLAMP, GX_LINEAR);
    }

    if (_14 == nullptr) {
        _14 = createTexture(0.125f, GX_TF_RGB565, GX_CLAMP, GX_LINEAR);
    }

    if (_18 == nullptr) {
        _18 = createTexture(0.125f, GX_TF_RGB565, GX_CLAMP, GX_LINEAR);
    }

    if (_1C == nullptr) {
        _1C = createTexture(0.25f, GX_TF_I8, GX_CLAMP, GX_LINEAR);
    }

    if (_20 == nullptr) {
        _20 = createTexture(0.25f, GX_TF_RGB565, GX_CLAMP, GX_LINEAR);
    }
}

void ImageEffectResource::createBlurTexture() {
    if (_0 == nullptr) {
        _0 = createTexture(1.0f, _34, GX_CLAMP, GX_LINEAR);
    }

    if (_8 == nullptr) {
        _8 = createTexture(0.5f, GX_TF_I8, GX_CLAMP, GX_LINEAR);
    }
}

void ImageEffectResource::createDOFTexture() {
    if (_0 == nullptr) {
        _0 = createTexture(1.0f, _34, GX_CLAMP, GX_LINEAR);
    }

    if (_4 == nullptr) {
        _4 = createTexture(0.5f, GX_TF_RGB565, GX_CLAMP, GX_LINEAR);
    }

    if (_C == nullptr) {
        _C = createTexture(0.25f, GX_TF_RGB565, GX_CLAMP, GX_LINEAR);
    }

    if (_10 == nullptr) {
        _10 = createTexture(0.25f, GX_TF_RGB565, GX_CLAMP, GX_LINEAR);
    }

    if (_24 == nullptr) {
        _24 = createTexture(1.0f, GX_TF_IA8, GX_CLAMP, GX_NEAR);
    }

    loadGradientTexture();
}

void ImageEffectResource::createFogTexture() {
    if (_4 == nullptr) {
        _4 = createTexture(0.5f, GX_TF_RGB565, GX_CLAMP, GX_LINEAR);
    }

    if (_24 == nullptr) {
        _24 = createTexture(1.0f, GX_TF_IA8, GX_CLAMP, GX_NEAR);
    }

    loadGradientTexture();
}

void ImageEffectResource::loadGradientTexture() {
    if (mFogGradArc != nullptr) {
        return;
    }

    mFogGradArc = MR::createAndAddResourceHolder("PostFog.arc");
    mFogGradNum = 0;

    while (true) {
        if (!MR::isExistFileInArc(mFogGradArc, "GradType%d.bti", mFogGradNum)) {
            break;
        }

        mFogGradNum++;
    }

    mFogGradTexture = new JUTTexture*[mFogGradNum];

    for (s32 i = 0; i < mFogGradNum; i++) {
        char resourceName[0x100];
        snprintf(resourceName, sizeof(resourceName), "GradType%d.bti", i);

        mFogGradTexture[i] = new JUTTexture(static_cast< const ResTIMG* >(fn_8004BFA0(mFogGradArc, resourceName)), 0);
        mFogGradTexture[i]->mWrapS = GX_CLAMP;
        mFogGradTexture[i]->mWrapT = GX_CLAMP;
        mFogGradTexture[i]->mMinType = GX_LINEAR;
        mFogGradTexture[i]->mMagType = GX_LINEAR;
        mFogGradTexture[i]->init();
    }
}
