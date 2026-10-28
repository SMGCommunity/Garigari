#pragma once

#include "Game/LiveActor/LiveActor.hpp"

class StarPieceSpotEruption : public LiveActor {
public:
    StarPieceSpotEruption(const char* pName);

    virtual void init(const JMapInfoIter& rIter);

    void exeEruption();
    void exeRest();

    void emit();

    /* 0x90 */ f32 mEmitHeight;
    /* 0x94 */ f32 mEmitRadius;
};
