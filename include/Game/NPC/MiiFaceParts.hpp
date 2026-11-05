#pragma once

#include "Game/LiveActor/LiveActor.hpp"
#include "Game/NPC/MiiFaceRecipe.hpp"
#include <JSystem/JGeometry/TMatrix.hpp>

class FixedPosition;

class MiiFaceParts : public LiveActor {
public:
    MiiFaceParts(const char* pName, const MiiFaceRecipe& rRecipe);

    ~MiiFaceParts();

    virtual void init(const JMapInfoIter& rIter);
    virtual void calcAnim();
    virtual void calcViewAndEntry();

    void drawOpa(const RFLDrawCoreSetting* pSetting) const;
    void drawXlu(const RFLDrawCoreSetting* pSetting) const;
    void initFixedPosition(MtxPtr pMtx, const TVec3f& rLocalTrans, const TVec3f& rLocalRotate);
    bool changeExpressionNormal();
    bool changeExpressionBlink();
    void changeFaceModel(const MiiFaceRecipe& rRecipe);
    void initFaceModel();
    bool tryChangeExpression(u32 expression);

    /* 0x90 */ RFLCharModel* mCharModel;
    /* 0x94 */ void* mBuffer;
    /* 0x98 */ MiiFaceRecipe* mRecipe;
    /* 0x9C */ TPos3f _9C;
    /* 0xCC */ MtxPtr _CC;
    /* 0xD0 */ FixedPosition* mFixedPosition;
    /* 0xD4 */ bool _D4;
    /* 0xD5 */ bool _D5;
};
