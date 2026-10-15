#pragma once

#include "Game/System/LayoutHolder.hpp"
#include <JSystem/JGeometry/TVec.hpp>

namespace nw4r {
    namespace lyt {
        class Layout;
        class Pane;
        class TextBox;
    }
}

namespace LayoutCoreUtil {
    f32 getPaneAutoScale(nw4r::lyt::Pane* pPane);
    nw4r::lyt::Layout* createLayout(const char* pLayoutName, LayoutHolder* pLayoutHolder);
    const char* getPaneUserData(const nw4r::lyt::Pane* pPane, char* pOut);
    u16 setTextBoxMessage(nw4r::lyt::TextBox* pTextBox, const wchar_t* pMsg);
    void initTextBoxPane(nw4r::lyt::TextBox* pTextBox, const char* pStr, u32 allocSize);
    void reallocateTextBoxMessage(nw4r::lyt::TextBox* pTextBox, u32 allocSize);
};  // namespace LayoutCoreUtil

namespace MR {
    void convertScreenPosToLayoutPos(TVec2f*, const TVec2f&);
    void convertLayoutPosToScreenPos(TVec2f*, const TVec2f&);
    void convertPaneLocalPosToScreenPos(TVec2f*, const nw4r::lyt::Pane*, const TVec2f&);
};  // namespace MR
