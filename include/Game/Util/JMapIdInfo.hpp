#pragma once

#include <revolution.h>

class JMapInfoIter;

class JMapIdInfo {
public:
    JMapIdInfo() { }

    
    JMapIdInfo(const JMapIdInfo &rInfo) __attribute__((forceinline)) {
        _0 = rInfo._0;
        mZoneID = rInfo.mZoneID;
    }

    void operator=(const JMapIdInfo &rhs) {
        _0 = rhs._0;
        mZoneID = rhs.mZoneID;
    }

    s32 _0;
    s32 mZoneID;        // 0x04
};

namespace MR {
    JMapIdInfo& createJMapIdInfoFromGroupId(const JMapInfoIter &);
    JMapIdInfo& createJMapIdInfoFromClippingGroupId(const JMapInfoIter &);
};
