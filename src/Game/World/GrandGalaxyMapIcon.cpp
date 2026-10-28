#include "Game/World/GrandGalaxyMapIcon.hpp"
#include "Game/Util/ActorInitUtil.hpp"
#include "Game/Util/EffectUtil.hpp"
#include "Game/Util/FileUtil.hpp"
#include "Game/Util/LiveActorUtil.hpp"
#include "Game/Util/MathUtil.hpp"
#include "Game/Util/ModelUtil.hpp"
#include "Game/Util/ObjUtil.hpp"
#include "Game/Util/StarPointerUtil.hpp"
#include <decomp.h>
#include <cstdio>

EXTERN_UNKNOWN_FUNC(void, 804E8B10, void*)
EXTERN_UNKNOWN_FUNC(void, 804E8C30, void*)

namespace {
    const f32 sMaxScale = 0.3f;
};

GrandGalaxyMapIcon::GrandGalaxyMapIcon(const char* pName, const char* pFileName)
    : LiveActor(pName), mOffsetX(), mOffsetY(), mSize(::sMaxScale), mBoundingRadius(1000.0f), mCanRotate(true) {
    char filePath[128];
    snprintf(filePath, sizeof(filePath), "/ObjectData/%s.arc", pFileName);

    if (!MR::isFileExist(filePath, true)) {
        pFileName = "MiniFlowerHighlandGalaxy";
    }

    if (!MR::initActor(this, pFileName, "MiniIcon", true)) {
        initEffectKeeper(0, nullptr, false);

        MR::connectToSceneWorldMapIcon(this);

        MR::initStarPointerTarget(this, 1000.0f, TVec3f(0.0f, 0.0f, 0.0f));
    }

    MR::setAllEffectDrawOrder(this, 9);

    MR::setClippingFarMax(this);
    MR::invalidateClipping(this);

    fn_804E8B10(this);

    MR::calcModelBoundingRadius(&mBoundingRadius, this);

    MR::tryStartAllAnim(this, pFileName);

    setScale(4000.0f);

    mScale.set(TVec3f(mSize));

    makeActorDead();
}

void GrandGalaxyMapIcon::fn_804E0020() {
    MR::emitEffect(this, MR::getModelResName(this));
    fn_804E8C30(this);
}

void GrandGalaxyMapIcon::control() {
    if (mCanRotate) {
        mRotation.y += 0.2f;
        mRotation.y = MR::repeatDegree(mRotation.y);
    }
}

void GrandGalaxyMapIcon::setRotation(const TVec3f& pVec) {
    mCanRotate = false;
    mRotation = pVec;
}

void GrandGalaxyMapIcon::setScale(f32 scale) {
    if (mBoundingRadius > scale) {
        mSize = ::sMaxScale * scale / mBoundingRadius;
    } else {
        mSize = ::sMaxScale;
    }

    mScale.set(TVec3f(mSize));
}
