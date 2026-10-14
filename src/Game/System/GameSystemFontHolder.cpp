#include "Game/System/GameSystemFontHolder.hpp"
#include "Game/System/FileLoader.hpp"
#include "Game/System/Language.hpp"
#include "Game/Util/FileUtil.hpp"
#include <JSystem/JKernel/JKRHeap.hpp>
#include <JSystem/JKernel/JKRMemArchive.hpp>
#include <cstdio>
#include <nw4r/ut/ResFont.h>

GameSystemFontHolder::GameSystemFontHolder()
    : mArchiveData(), mArchive(), mEmbeddedMessageFont(), mMessageFont(), mPictureFont(), mMenuFont64(), mNumberFont(), mMenuFont96(), mStaffFont() {
}

nw4r::ut::Font* GameSystemFontHolder::getMessageFont() const {
    if (mEmbeddedMessageFont != nullptr) {
        return mEmbeddedMessageFont;
    }

    return mMessageFont;
}

void GameSystemFontHolder::createFontFromEmbeddedData() {
    JKRArchive* pArchive = nullptr;
    JKRHeap* pHeap = nullptr;

    MR::getMountedArchiveAndHeap("ErrorMessageArchive.arc", &pArchive, &pHeap);

    char embeddedFontPath[256];
    const char* languagePrefix = MR::getCurrentLanguagePrefix();
    snprintf(embeddedFontPath, sizeof(embeddedFontPath), "LocalizeData/%s/LayoutData/EmbeddedFont.arc", languagePrefix);

    mArchiveData = static_cast< u8* >(MR::decompressFileFromArchive(pArchive, embeddedFontPath, pHeap, -32));
    mArchive = new (pHeap, 0) JKRMemArchive();
    mArchive->mountFixed(mArchiveData, JKR_MEM_BREAK_FLAG_0);
    mEmbeddedMessageFont = new (pHeap, -4) nw4r::ut::ResFont();
    mEmbeddedMessageFont->SetResource(mArchive->getResource("MessageFont26.brfnt"));
}

namespace {
    inline nw4r::ut::ResFont* createFont(JKRArchive* pArchive, const char* pName) {
        nw4r::ut::ResFont* pFont = new nw4r::ut::ResFont();
        pFont->SetResource(pArchive->getResource(pName));
        return pFont;
    }
};  // namespace

void GameSystemFontHolder::createFontFromFile() {
    JKRMemArchive* pArchive = MR::receiveArchive("/LayoutData/Font.arc");

    mMessageFont = createFont(pArchive, "/MessageFont26.brfnt");

    mPictureFont = createFont(pArchive, "/PictureFont.brfnt");

    mMenuFont64 = createFont(pArchive, "/MenuFont64.brfnt");

    mNumberFont = createFont(pArchive, "/NumberFont.brfnt");

    mMenuFont96 = createFont(pArchive, "/MenuFont96.brfnt");

    mStaffFont = createFont(pArchive, "/StaffFont18.brfnt");

    mMessageFont->SetAlternateChar('?');
    mPictureFont->SetAlternateChar('?');
    mMenuFont64->SetAlternateChar('?');
    mNumberFont->SetAlternateChar('?');
    mMenuFont96->SetAlternateChar('?');
    mStaffFont->SetAlternateChar('?');

    if (mEmbeddedMessageFont != nullptr) {
        mEmbeddedMessageFont->RemoveResource();

        delete mEmbeddedMessageFont;
        delete mArchive;
        delete[] mArchiveData;

        mEmbeddedMessageFont = nullptr;
        mArchiveData = nullptr;
    }
}
