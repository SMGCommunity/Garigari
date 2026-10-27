#include "Game/World/MiniEarthenPipe.hpp"
#include "Game/LiveActor/ModelObj.hpp"
#include "Game/Util/LiveActorUtil.hpp"
#include <decomp.h>

EXTERN_UNKNOWN_FUNC(bool, 804E8C40, const LiveActor*);
EXTERN_UNKNOWN_FUNC(bool, 804E8C50, const LiveActor*, f32, f32);
EXTERN_UNKNOWN_FUNC(bool, 804E8C80, const LiveActor*, f32, f32);

MiniEarthenPipe::MiniEarthenPipe() : ModelObj("ミニ土管", "MiniEarthenPipe", nullptr, -2, -2, -2, false) {
}

bool MiniEarthenPipe::isPointing() const {
    return fn_804E8C40(this);
}

bool MiniEarthenPipe::fn_804E3420() {
    if (MR::isDead(this)) {
        return false;
    }

    fn_804E8C50(this, 0.1f, 1.2f);
    return true;
}

void MiniEarthenPipe::control() {
    fn_804E8C80(this, 0.05f, 1.0f);
}
