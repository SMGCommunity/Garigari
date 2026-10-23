#pragma once

#include <revolution.h>

class JMapInfoIter;

class JMapLinkInfo {
public:
    JMapLinkInfo();
    JMapLinkInfo(const JMapInfoIter&, bool);

    bool operator==(const JMapLinkInfo& rOther) const {
        if (!isValid() || !rOther.isValid()) {
            return false;
        }

        return mFollowId == rOther.mFollowId && mZoneId == rOther.mZoneId && mContext == rOther.mContext;
    }

    void setLinkedInfo(const JMapInfoIter&);
    bool isValid() const;
    void invalidate();
    void setLinkInfo(const JMapInfoIter&);

    /* 0x00 */ s16 mFollowId;
    /* 0x02 */ s16 mZoneId;
    /* 0x04 */ s16 mContext;
};
