#include "Util/MathUtil.hpp"
#include <revolution.h>
#include <cmath>

namespace {
    f32* gAcosTable;
};

namespace MR {
    void initAcosTable() {
        gAcosTable = new f32[0x100];
        u32 i = 0;

        do {
            f64 v7 = 0.02 * (i / 255.0) + 0.98;
            if (v7 > 1.0) {
                v7 = 1.0;
            }
            gAcosTable[i++] = acos(v7);
        } while (i < 0x100);
    }
};
