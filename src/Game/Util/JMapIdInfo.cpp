#include "Game/Util/JMapIdInfo.hpp"
#include "Game/Util/JMapInfo.hpp"
#include "Game/Util/JMapUtil.hpp"
#include "Game/Util/SceneUtil.hpp"

JMapIdInfo::JMapIdInfo(s32 val_0, const JMapInfoIter& rIter) : mZoneID(-1) {
    _0 = val_0;
    mZoneID = MR::getPlacedZoneId(rIter);
}

JMapIdInfo::JMapIdInfo(s32 val_0, s32 zoneID) : _0(val_0), mZoneID(zoneID) {}

void JMapIdInfo::initialize(s32 val_0, const JMapInfoIter& rIter) {
    _0 = val_0;
    mZoneID = MR::getPlacedZoneId(rIter);
}

JMapIdInfo MR::createJMapIdInfoFromGroupId(const JMapInfoIter &rIter) {
    // FIXME
    // decomp.me: https://decomp.me/scratch/4hpy2

    s32 groupId = -1;
    MR::getJMapInfoGroupID(rIter, &groupId);
    return JMapIdInfo(groupId, rIter);
}

JMapIdInfo MR::createJMapIdInfoFromClippingGroupId(const JMapInfoIter &rIter) {
    // FIXME
    // decomp.me: https://decomp.me/scratch/gHLSg
    
    s32 clippingGroupId = -1;
    MR::getJMapInfoClippingGroupID(rIter, &clippingGroupId);
    return JMapIdInfo(clippingGroupId, rIter);
}
