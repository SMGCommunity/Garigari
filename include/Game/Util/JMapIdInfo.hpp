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

    JMapIdInfo(s32, const JMapInfoIter &);

    void operator=(const JMapIdInfo &rhs) {
        _0 = rhs._0;
        mZoneID = rhs.mZoneID;
    }
    
    int getZoneID() const {
        return mZoneID;
    }

    s32 _0;
    int mZoneID;        // 0x04
};

namespace MR {
    JMapIdInfo& createJMapIdInfoFromGroupId(const JMapInfoIter &);
    JMapIdInfo& createJMapIdInfoFromClippingGroupId(const JMapInfoIter &);
};
