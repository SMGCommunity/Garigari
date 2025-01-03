#pragma once

#include "JSupport/JSUList.hpp"

class JKRHeap;

class JKRDisposer {
public:
    JKRDisposer();
    virtual ~JKRDisposer();

    JKRHeap* mHeap;                 // 0x04
    JSULink<JKRDisposer> mLink;     // 0x08
};
