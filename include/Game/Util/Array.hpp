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

        inline ~AssignableArray() {
            if (mArray != nullptr) {
                delete[] mArray;
            }
        }

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
