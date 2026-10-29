#pragma once

#include <revolution/gx.h>

class JUTTexture;
class ResourceHolder;

class ImageEffectResource {
public:
    /// @brief Creates a new `ImageEffectResource`.
    ImageEffectResource();

    void createBloomTexture();
    void createBlurTexture();
    void createDOFTexture();
    void createFogTexture();
    JUTTexture* createTexture(f32, GXTexFmt);

    /* 0x00 */ JUTTexture* _0;
    /* 0x04 */ JUTTexture* _4;
    /* 0x08 */ JUTTexture* _8;
    /* 0x0C */ JUTTexture* _C;
    /* 0x10 */ JUTTexture* _10;
    /* 0x14 */ JUTTexture* _14;
    /* 0x18 */ JUTTexture* _18;
    /* 0x1C */ JUTTexture* _1C;
    /* 0x20 */ JUTTexture* _20;
    /* 0x24 */ JUTTexture* _24;
    /* 0x28 */ JUTTexture** _28;
    /* 0x2C */ u32 _2C;
    /* 0x30 */ ResourceHolder* _30;
    /* 0x34 */ u32 _34;
};
