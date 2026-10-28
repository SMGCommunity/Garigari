#include "Game/NPC/MiiFaceRecipe.hpp"

#include <RFL_Icon.h>
#include <RFL_Model.h>
#include <RFL_Types.h>

MiiFaceRecipe::MiiFaceRecipe(RFLDataSource dataSource, int id, RFLResolution resolution, u32 expressionFlags)
    : mDataSource(dataSource), mDatabase(nullptr), mIndex(id), mResolution(resolution), mExpressionFlags(expressionFlags) {
}

void MiiFaceRecipe::setDatabase(RFLMiddleDB* pDatabase) {
    mDatabase = pDatabase;
}

bool MiiFaceRecipe::hasExpression(RFLExpression expression) const {
    return (mExpressionFlags & (1 << expression)) != 0;
}

u32 MiiFaceRecipe::getModelBufferSize() const {
    return RFLGetModelBufferSize(mResolution, mExpressionFlags);
}

void MiiFaceRecipe::initFaceModel(RFLCharModel* pCharModel, void* pWork) const {
    RFLInitCharModel(pCharModel, mDataSource, mDatabase, mIndex, pWork, mResolution, mExpressionFlags);
}

// NON_MATCHING
// decomp.me: https://decomp.me/scratch/KNT2F
RFLErrcode MiiFaceRecipe::makeIcon(void* pBuffer, int width, int height, _GXColor bgColor) const {
    RFLIconSetting iconSetting;

    iconSetting.width = width;
    iconSetting.height = height;
    iconSetting.bgType = RFLIconBG_Direct;
    iconSetting.bgColor = bgColor;
    iconSetting.drawXluOnly = false;

    return RFLMakeIcon(pBuffer, mDataSource, mDatabase, mIndex, RFLExp_Normal, &iconSetting);
}

RFLErrcode MiiFaceRecipe::makeIconWithFavoriteColor(void* pBuffer, int width, int height) const {
    RFLIconSetting iconSetting;

    iconSetting.width = width;
    iconSetting.height = height;
    iconSetting.bgType = RFLIconBG_Favorite;
    iconSetting.drawXluOnly = false;

    return RFLMakeIcon(pBuffer, mDataSource, mDatabase, mIndex, RFLExp_Normal, &iconSetting);
}
