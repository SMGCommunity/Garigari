#pragma once

#include <revolution.h>
#include "Game/Util/JMapInfo.hpp"

class JMapLinkInfo {
public:
    inline JMapLinkInfo() {

    }

    JMapLinkInfo(const JMapInfoIter &, bool);

    void reset();
    void setLinkedInfo(const JMapInfoIter &);
    bool isValid() const;
    void invalidate();
    void setLinkInfo(const JMapInfoIter &);

    s16 mLinkID;        // _0
    s16 mZoneID;        // _2
    s16 mContext;       // _4
};