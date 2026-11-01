#include "Game/Screen/ActorLayout.hpp"
#include "Game/LiveActor/LiveActor.hpp"
#include "Game/Screen/SimpleLayout.hpp"
#include "Game/Util/CameraUtil.hpp"
#include "Game/Util/LayoutUtil.hpp"
#include "Game/Util/LiveActorUtil.hpp"

ActorLayout::ActorLayout(LiveActor* pHostActor, const char* pName, const char* pLayoutName, const TVec3f& rOffset, u32 a3, int drawType)
    : SimpleLayout(pName, pLayoutName, a3, drawType), mHostActor(pHostActor), mOffset(rOffset) {
}

void ActorLayout::control() {
    if (isHostHidden()) {
        MR::hideLayout(this);
        return;
    }
    TVec2f screenPosition;

    MR::calcScreenPosition(&screenPosition, mHostActor->mPosition + mOffset);

    setTrans(screenPosition);

    MR::showLayout(this);
}

bool ActorLayout::isHostHidden() const {
    if (MR::isDead(mHostActor)) {
        return true;
    }

    if (MR::isClipped(mHostActor)) {
        return true;
    }

    return MR::isNoEntryDrawBuffer(mHostActor);
}
