#pragma once

#include <JSystem/J2DGraph/J2DOrthoGraph.hpp>
#include <revolution/gx/GXStruct.h>

class J2DOrthoGraphSimple : public J2DOrthoGraph {
public:
    J2DOrthoGraphSimple();

    virtual ~J2DOrthoGraphSimple() {
    }

    virtual void setPort();
};

namespace MR {
    void drawInit();
    void fillScreen(const GXColor&);
    void clearZBuffer();
    void loadViewMtxFor2DModel();
    void drawInitFor2DModel();
    void setupDrawForNW4RLayout(f32);
};
