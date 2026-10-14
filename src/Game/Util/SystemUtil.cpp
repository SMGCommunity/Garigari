#include "Game/Util/SystemUtil.hpp"
#include "Game/System/GameSystem.hpp"
#include "Game/System/GameSystemFontHolder.hpp"
#include "Game/Util/SingletonHolder.hpp"
#include <revolution/types.h>
#include <nw4r/ut/ResFont.h>

nw4r::ut::Font* MR::getFontOnCurrentLanguage() {
    return SingletonHolder< GameSystem >::get()->mFontHolder->getMessageFont();
}

nw4r::ut::Font* MR::getPictureFontNW4R() {
    return SingletonHolder< GameSystem >::get()->mFontHolder->mPictureFont;
}

nw4r::ut::Font* MR::getMenuFontNW4R() {
    return SingletonHolder< GameSystem >::get()->mFontHolder->mMenuFont64;
}

nw4r::ut::Font* MR::getNumberFontNW4R() {
    return SingletonHolder< GameSystem >::get()->mFontHolder->mNumberFont;
}

nw4r::ut::Font* MR::getMenuFont96NW4R() {
    return SingletonHolder< GameSystem >::get()->mFontHolder->mMenuFont96;
}

nw4r::ut::Font* MR::getStaffFontNW4R() {
    return SingletonHolder< GameSystem >::get()->mFontHolder->mStaffFont;
}

bool MR::hasPictureFontNW4R() {
    return SingletonHolder< GameSystem >::get()->mFontHolder->mPictureFont != nullptr;
}
