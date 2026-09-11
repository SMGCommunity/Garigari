#pragma once

#include <revolution.h>

namespace MR {
    template<class T>
    class AssignableArray {
    public:
        inline AssignableArray() {
            mArray = nullptr;
            mMaxItems = 0;
        }

#ifdef MR_ASSIGNABLE_ARRAY_DEFER_DESTRUCTOR
        ~AssignableArray();
#else
        inline ~AssignableArray() {
            if (mArray != nullptr) {
                delete[] mArray;
            }
        }
#endif

        inline T operator[](int idx) {
            return mArray[idx];
        }

        inline void init(s32 count) {
            mArray = new T[count];
            mMaxItems = count;
        }
        
        T* mArray;
        s32 mMaxItems;
    };
};
