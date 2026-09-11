#pragma once

#include "LiveActor/LiveActor.hpp"

class TubeSlider;

// Only base classes and allocation sizes are recovered here.
class TubeSliderEnemy : public LiveActor {
public:
    TubeSliderEnemy(TubeSlider*);
    u8 mUnknown[0x2C];
};

class TubeSliderHana : public LiveActor {
public:
    TubeSliderHana(TubeSlider*);
    u8 mUnknown[0x38];
};

class TubeSliderObjCreator : public NameObj {
public:
    TubeSliderObjCreator(TubeSlider*, const char*);
    u8 mUnknown[0x8];
};
