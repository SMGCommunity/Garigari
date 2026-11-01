#pragma once

#include "Game/Screen/ImageEffectBase.hpp"

class JUTTexture;

class PostFog : public ImageEffectBase {
public:
    PostFog(const char* pName);

    virtual void draw() const;

    void capture() const;
    void drawFog(s16 left, s16 top, s16 right, s16 bottom, bool) const;
    JUTTexture* getGradientTexture() const;

    /* 0x18 */ JUTTexture* mDepthTexture;
    /* 0x1C */ u32 _1C;  // Unknown
    /* 0x20 */ s32 mInnerRadius;
    /* 0x24 */ s32 mOuterRadius;
    /* 0x28 */ u8 mA;
    /* 0x29 */ u8 mR;
    /* 0x2A */ u8 mG;
    /* 0x2B */ u8 mB;
    /* 0x2C */ s32 mGradientType;
};
