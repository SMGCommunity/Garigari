#pragma once

#include <revolution/types.h>

class J3DModel;
class MirrorReflectionMtxSetter;
class ResourceHolder;

class DisplayListMaker {
public:
    DisplayListMaker(J3DModel*, const ResourceHolder*);

    MirrorReflectionMtxSetter* addMirrorReflectionMtxSetter();
};
