#pragma once

#include <JSystem/JGeometry/TVec.hpp>
#include <JSystem/JUtility/JUTVideo.hpp>
#include <revolution/types.h>

struct ResTIMG;

namespace MR {
    s32 getScreenWidth();
    inline s32 getScreenHeight() NO_INLINE {
        return JUTVideo::getManager()->getEfbHeight();
    }
    const ResTIMG* getScreenResTIMG();
};  // namespace MR
