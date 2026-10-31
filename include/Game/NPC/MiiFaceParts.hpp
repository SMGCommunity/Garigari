#pragma once

#include "Game/LiveActor/LiveActor.hpp"
#include "Game/NPC/MiiFaceRecipe.hpp"
#include "Game/Util/JMapInfo.hpp"
#include <JSystem/JGeometry/TVec.hpp>
#include <revolution/mtx.h>
#include <revolution/types.h>
#include <RFL_Model.h>

class FixedPosition;

class MiiFaceParts : public LiveActor {
public:
    MiiFaceParts(const char*, const MiiFaceRecipe&);

    ~MiiFaceParts();

    virtual void init(const JMapInfoIter&);
    virtual void calcAnim();
    virtual void calcViewAndEntry();

    void drawOpa(const RFLDrawCoreSetting*);
    void drawXlu(const RFLDrawCoreSetting*);
    void initFixedPosition(MtxPtr, const TVec3f&, const TVec3f&);
    void changeExpressionNormal();
    void changeExpressionBlink();
    void changeFaceModel(const MiiFaceRecipe&);
    void initFaceModel();
    void tryChangeExpression(u32);

    /* 0x90 */ RFLCharModel* _90;
    /* 0x94 */ void* _94;
    /* 0x98 */ MiiFaceRecipe* mRecipe;

    // TODO: replace these later, probably
    /* 0x9C */ u32 _9C;
    /* 0xA0 */ u64 _A0;
    /* 0xA8 */ u64 _A8;
    /* 0xB0 */ u64 _B0;
    /* 0xB8 */ u64 _B8;
    /* 0xC0 */ u64 _C0;
    /* 0xC8 */ u64 _C8;

    /* 0xD0 */ FixedPosition* _D0;
    /* 0xD4 */ bool _D4;
    /* 0xD5 */ bool _D5;
};
