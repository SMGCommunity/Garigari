#pragma once

#include <revolution/gx/GXStruct.h>
#include <revolution/types.h>
#include <RFL_MiddleDatabase.h>
#include <RFL_Model.h>
#include <RFL_Types.h>

class MiiFaceRecipe {
public:
    MiiFaceRecipe(RFLDataSource, int, RFLResolution, u32);

    void setDatabase(RFLMiddleDB*);
    bool hasExpression(RFLExpression) const;
    u32 getModelBufferSize() const;
    void initFaceModel(RFLCharModel*, void*) const;
    RFLErrcode makeIcon(void*, int, int, _GXColor) const;
    RFLErrcode makeIconWithFavoriteColor(void*, int, int) const;

    /* 0x00 */ RFLDataSource mDataSource;
    /* 0x04 */ RFLMiddleDB* mDatabase;
    /* 0x08 */ s16 mIndex;
    /* 0x0C */ RFLResolution mResolution;
    /* 0x10 */ u32 mExpressionFlags;
};
