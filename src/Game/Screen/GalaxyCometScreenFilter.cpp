#include "Game/Screen/GalaxyCometScreenFilter.hpp"
#include "Game/Scene/SceneFunction.hpp"
#include "Game/Util/LayoutUtil.hpp"
#include "Game/Util/ObjUtil.hpp"

GalaxyCometScreenFilter::GalaxyCometScreenFilter() : LayoutActor("コメット用画面塗り潰し", true) {
    MR::connectToScene(this, MR::MovementType_Layout, MR::CalcAnimType_Layout, MR::DrawBufferType_None, MR::DrawType_CometScreenFilter);
    initLayoutManager("CometScreenFilter", 1);
    appear();
}

void GalaxyCometScreenFilter::setCometType(bool isGreenComet) {
    MR::startAnim(this, "Color", 0);

    s32 frame = isGreenComet;
    MR::setAnimFrameAndStop(this, frame, 0);
}
