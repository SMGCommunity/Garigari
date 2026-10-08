#include "Util/HashUtil.hpp"
#include "locale.h"

namespace MR {
    u32 getHashCode(const char * pName) {
        u32 hashCode = 0;
        for (int i = 0; pName[i] != 0; i++) {
            hashCode = pName[i] + 31 * hashCode;
        }
        return hashCode;
    }

    u32 getHashCodeLower(const char * pName) {
        u32 hashCode = 0;
        _loc_ctype_cmpt* localePtr = _current_locale.ctype_cmpt_ptr;
        char currentChar = pName[0];
        for (int i = 0; pName[i] != 0; i++) {
            char currentChar = pName[i];

            bool r0 = true;
            if (currentChar <= 255) {
                r0 = false;
            }
            
            hashCode *= 31;

            u32 thingToAdd;
            if (r0) {
                thingToAdd = localePtr->lower_map_ptr[currentChar];
            } else {
                thingToAdd = currentChar;
            }
            hashCode += thingToAdd;
        }
        return hashCode;
    }
}
