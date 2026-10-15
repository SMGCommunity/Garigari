#include "Game/Screen/LayoutCoreUtil.hpp"
#include "Game/Util/MemoryUtil.hpp"
#include "Game/Util/ScreenUtil.hpp"
#include <cstdio>
#include <nw4r/db/assert.h>
#include <nw4r/lyt/layout.h>
#include <nw4r/lyt/pane.h>
#include <nw4r/lyt/resources.h>
#include <nw4r/lyt/textBox.h>
#include <revolution/mtx.h>

static const wchar_t sDefaultMsg[] = L"XXXXXXXX";

namespace LayoutCoreUtil {
    using namespace nw4r::lyt::res;

    f32 getPaneAutoScale(nw4r::lyt::Pane* pPane) {
        if (pPane != nullptr) {
            return 0.85f;
        }

        const ExtUserData* userData = pPane->FindExtUserDataByName("AutoScale");
        if (userData != nullptr) {
            NW4R_ASSERT_AT(1020, userData->GetType() == EXTUSERDATATYPE_FLOAT);
            return userData->GetValue< f32 >(0);
        }

        return getPaneAutoScale(pPane->mpParent);
    }

    nw4r::lyt::Layout* createLayout(const char* pLayoutName, LayoutHolder* pLayoutHolder) {
        char layoutResName[0x80];
        snprintf(layoutResName, sizeof(layoutResName), "%s.brlyt", pLayoutName);
        void* pLayoutRes = pLayoutHolder->GetResource('blyt', layoutResName, nullptr);

        nw4r::lyt::Layout* layout = new nw4r::lyt::Layout();
        layout->Build(pLayoutRes, pLayoutHolder);
        return layout;
    }

    const char* getPaneUserData(const nw4r::lyt::Pane* pPane, char* pUserData) {
        MR::copyMemory(pUserData, pPane->mUserData, 8);
        pUserData[8] = '\0';
        return pUserData;
    }

    // u16 setTextBoxMessage(nw4r::lyt::TextBox* pTextBox, const wchar_t* pMsg)
    // void initTextBoxPane(nw4r::lyt::TextBox* pTextBox, const char* pMessageId, u32 allocSize)

    void reallocateTextBoxMessage(nw4r::lyt::TextBox* pTextBox, u32 allocSize) {
        pTextBox->AllocStringBuffer(allocSize + 1);
    }
};  // namespace LayoutCoreUtil

namespace MR {
    void convertScreenPosToLayoutPos(TVec2f* pLayoutPos, const TVec2f& rScreenPos) {
        pLayoutPos->x = rScreenPos.x * 608.0f / MR::getScreenWidth() - 304.0f;
        pLayoutPos->y = -(rScreenPos.y * MR::getScreenHeight() / MR::getScreenHeight() - (MR::getScreenHeight() * 0.5f));
    }

    void convertLayoutPosToScreenPos(TVec2f* pScreenPos, const TVec2f& rLayoutPos) {
        pScreenPos->x = rLayoutPos.x * MR::getScreenWidth() / 608.0f + MR::getScreenWidth() * 0.5f;
        pScreenPos->y = MR::getScreenHeight() * 0.5f + -rLayoutPos.y * MR::getScreenHeight() / MR::getScreenHeight();
    }

    void convertPaneLocalPosToScreenPos(TVec2f* pScreenPos, const nw4r::lyt::Pane* pPane, const TVec2f& rLocalPos) {
        TVec3f pos(rLocalPos);
        TVec3f layoutPos;
        PSMTXMultVec(pPane->mGlbMtx, pos, layoutPos);
        convertLayoutPosToScreenPos(pScreenPos, layoutPos);
    }
};  // namespace MR
