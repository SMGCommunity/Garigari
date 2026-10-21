#pragma once

#include "Game/Util/BothDirList.hpp"
#include "Game/Util/Color.hpp"
#include <JSystem/JUtility/JUTXfb.hpp>
#include <revolution.h>

typedef void (*PreRenderCallback)();

class MainLoopFrameworkAlarm : public OSAlarm {
public:
    MainLoopFrameworkAlarm() : mLink(this) {
    }

    /* 0x30 */ u32 _30;
    /* 0x34 */ MR::BothDirLink< MainLoopFrameworkAlarm > mLink;

    static MR::BothDirList< MainLoopFrameworkAlarm > sList;
};

class MainLoopFramework {
public:
    void setClearColor(Color8 color) {
        mClearColor = color;
    }

    MainLoopFramework(void* pXfb1, void* pXfb2, void* pXfb3, bool useAlpha) : mClearColor(0xffffffff) {
        ctor_subroutine(useAlpha);
        JUTXfb::createManager(pXfb1, pXfb2, pXfb3);
    }

    ~MainLoopFramework();

    static MainLoopFramework* getManager() {
        return sManager;
    }

    static MainLoopFramework* createManager(const GXRenderModeObj*, void*, void*, void*, bool);
    void ctor_subroutine(bool);
    void prepareCopyDisp();
    void drawendXfb_single();
    void exchangeXfb_double();
    void exchangeXfb_triple();
    void copyXfb_triple();
    void preGX();
    void endGX();
    void waitForRetrace();
    void beginRender();
    void endRender();
    void endFrame();
    void waitBlanking(int);
    void setTickRateFromFrame(u16);
    void clearEfb(GXColor);
    void clearEfb(int, int, int, int, GXColor);
    void calcCombinationRatio();
    static u32 frameToTick(f32);
    static void setForOSResetSystem();

    static void setUseVFilterOff() NO_INLINE {
        getManager()->mUseVFilter = false;
    }

    static void setUseAlphaOff() NO_INLINE {
        getManager()->mUseAlpha = false;
    }

    static void setUseVFilterOn() NO_INLINE {
        getManager()->mUseVFilter = true;
    }
    
    static void setUseAlphaOn() NO_INLINE {
        getManager()->mUseAlpha = true;
    }

    /* 0x00 */ Color8 mClearColor;
    /* 0x04 */ u32 mClearZ;
    /* 0x08 */ u16 mDispCopyGamma;
    /* 0x0A */ u16 mCopyClamp;
    /* 0x0C */ u32 _C;
    /* 0x10 */ u16 mRetraceCount;
    /* 0x14 */ u32 mTickDuration;
    /* 0x18 */ bool mUseAlpha;
    /* 0x19 */ bool mUseVFilter;
    /* 0x1A */ u8 _1A;
    /* 0x1B */ u8 _1B;
    /* 0x1C */ f32 mCombinationRatio;
    /* 0x20 */ OSTick mTick;
    /* 0x24 */ s32 mLastFrameTime;
    /* 0x28 */ s32 mLastVideoTickDelta;
    /* 0x2C */ s32 mRenderInterval;
    /* 0x30 */ s32 mRenderCounter;
    /* 0x34 */ u8 mDoRenderFrame;
    /* 0x35 */ u8 _35;
    /* 0x36 */ u8 _36;
    /* 0x37 */ u8 _37;
    /* 0x38 */ PreRenderCallback mPreRenderCallback;
    /* 0x3C */ s16 mSingleBufferIndex;
    /* 0x3E */ u8 _3E;
    /* 0x3F */ bool _3F;

    static MainLoopFramework* sManager;
};
