#pragma once

#include <revolution/gx/GXStruct.h>

namespace MR {
    void drawInit();
    void fillScreen(const GXColor&);
    void clearZBuffer();
    void drawInitFor2DModel();
    void setupDrawForNW4RLayout(f32);
};
