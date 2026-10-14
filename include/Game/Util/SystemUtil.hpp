#pragma once

#include <revolution/types.h>

namespace nw4r {
    namespace ut {
        class Font;
    };
};  // namespace nw4r

namespace MR {
    nw4r::ut::Font* getFontOnCurrentLanguage();
    nw4r::ut::Font* getPictureFontNW4R();
    nw4r::ut::Font* getMenuFontNW4R();
    nw4r::ut::Font* getNumberFontNW4R();
    nw4r::ut::Font* getMenuFont96NW4R();
    nw4r::ut::Font* getStaffFontNW4R();
    bool hasPictureFontNW4R();
}
