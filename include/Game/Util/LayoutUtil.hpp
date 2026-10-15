#pragma once

#include "Game/Screen/LayoutCoreUtil.hpp"
#include <revolution.h>

class LayoutActor;
class LayoutHolder;

namespace nw4r {
    namespace lyt {
        class DrawInfo;
        class Pane;
        class TexMap;
        class TextBox;
    };  // namespace lyt

    namespace ut {
        class Font;
        class Rect;
    };  // namespace ut
};  // namespace nw4r

namespace MR {
    LayoutHolder* createAndAddLayoutHolder(const char*);
    LayoutHolder* createAndAddLayoutHolderRawData(const char*);
    void copyPaneTrans(TVec2f*, const LayoutActor*, const char*);
    bool isDead(const LayoutActor*);
    bool isStopAnimFrame(const LayoutActor*);
    bool isExecuteCalcAnimLayout(const LayoutActor*);
    bool isExecuteDrawLayout(const LayoutActor*);
    nw4r::lyt::Pane* getRootPane(const LayoutActor*);
};  // namespace MR
