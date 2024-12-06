#pragma once

#include <revolution.h>

class JMapInfoIter;

class JMapLinkInfo {
public:
    JMapLinkInfo();
    JMapLinkInfo(const JMapInfoIter &, bool);

    void setLinkedInfo(const JMapInfoIter &);
    bool isValid() const;
    void invalidate();
    void setLinkInfo(const JMapInfoIter &);

    s16 mFollowID;      // 0x00
    s16 mZoneID;        // 0x02
    s16 mContext;       // 0x04
};
