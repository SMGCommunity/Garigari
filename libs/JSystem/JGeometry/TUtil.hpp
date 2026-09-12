#pragma once

#include <revolution/types.h>

namespace JGeometry {
    template < typename T >
    class TUtil {
    public:
        static int epsilonEquals(T a1, T a2, T a3) {
            int ret = 0;

            a1 -= a2;

            if (-a3 <= a1 && a1 <= a3) {
                ret = 1;
            }

            return ret;
        }
    };
};  // namespace JGeometry
