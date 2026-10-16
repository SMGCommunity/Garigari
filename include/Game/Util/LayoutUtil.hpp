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
    void setTextBoxGameMessageRecursive(LayoutActor*, const char*, const char*);
    void showPane(LayoutActor*, const char*);
    void showPaneRecursive(LayoutActor*, const char*);
    void hidePane(LayoutActor*, const char*);
    void hidePaneRecursive(LayoutActor*, const char*);
    bool isHiddenPane(const LayoutActor*, const char*);
    void showScreen(LayoutActor*);
    void hideScreen(LayoutActor*);
    void setFollowPos(const TVec2f*, const LayoutActor*, const char*);
    void setFollowTypeReplace(const LayoutActor*, const char*);
    void setFollowTypeAdd(const LayoutActor*, const char*);
    void copyPaneTrans(TVec2f*, const LayoutActor*, const char*);
    void setLayoutScalePosAtPaneScaleTransIfExecCalcAnim(LayoutActor*, const LayoutActor*, const char*);
    void startAnim(LayoutActor*, const char*, u32);
    void startAnimAtFirstStep(LayoutActor*, const char*, u32);
    void startPaneAnim(LayoutActor*, const char*, const char*, u32);
    void startPaneAnimAtStep(LayoutActor*, const char*, const char*, s32, u32);
    void startPaneAnimAtFirstStep(LayoutActor*, const char*, const char*, u32);
    void startAnimReverseOneTime(LayoutActor*, const char*, u32);
    void startPaneAnimReverseOneTime(LayoutActor*, const char*, const char*, u32);
    void startAnimAndSetFrameAndStop(LayoutActor*, const char*, f32, u32);
    void setAnimFrameAndStop(LayoutActor*, f32, u32);
    void setAnimFrameAndStopAtEnd(LayoutActor*, u32);
    void setAnimFrameAndStopAdjustTextWidth(LayoutActor*, const char*, u32);
    void setAnimFrameAndStopAdjustTextHeight(LayoutActor*, const char*, u32);
    void setPaneAnimFrameAndStop(LayoutActor*, const char*, f32, u32);
    void setPaneAnimFrameAndStopAtEnd(LayoutActor*, const char*, u32);
    void setAnimFrame(LayoutActor*, f32, u32);
    void setPaneAnimFrame(LayoutActor*, const char*, f32, u32);
    void setAnimRate(LayoutActor*, f32, u32);
    void setPaneAnimRate(LayoutActor*, const char*, f32, u32);
    void stopAnim(LayoutActor*, u32);
    void stopPaneAnim(LayoutActor*, const char*, u32);
    bool isAnimStopped(const LayoutActor*, u32);
    bool isPaneAnimStopped(const LayoutActor*, const char*, u32);
    bool isStep(const LayoutActor*, s32) NO_INLINE;
    bool isFirstStep(const LayoutActor*);
    bool isLessStep(const LayoutActor*, s32);
    bool isGreaterStep(const LayoutActor*, s32);
    bool isGreaterEqualStep(const LayoutActor*, s32);
    bool isIntervalStep(const LayoutActor*, s32);
    bool isDead(const LayoutActor*);
    bool isHiddenLayout(const LayoutActor*);
    void showLayout(LayoutActor*);
    void hideLayout(LayoutActor*);
    bool isStopAnimFrame(const LayoutActor*);
    bool isExecuteCalcAnimLayout(const LayoutActor*);
    bool isExecuteDrawLayout(const LayoutActor*);
    nw4r::lyt::Pane* getRootPane(const LayoutActor*);
    void clearTextBoxMessageRecursive(LayoutActor*, const char*);
};  // namespace MR
