#include "nw4r/lyt/init.h"
#include <revolution/os.h>
#include <revolution/os/OSFastCast.h>

namespace {
    const char* NW4R_LYT_Version_ = "<< NW4R    - LYT \tfinal   build: Feb 11 2010 17:42:55 (0x4302_162) >>";
};

namespace nw4r {
    namespace lyt {
        void LytInit() {
            OSRegisterVersion(NW4R_LYT_Version_);
            OSInitFastCast();
        }
    };  // namespace lyt
};  // namespace nw4r
