#pragma once

#include "LiveActor/LiveActorGroup.hpp"
#include "Util/JMapIdInfo.hpp"

class HitSensor;

#define GROUP_NAME_LEN 0x30

class MsgSharedGroup : public LiveActorGroup {
public:
    MsgSharedGroup(const char *, s32, const JMapInfoIter &);

    virtual ~MsgSharedGroup();
    virtual void init(const JMapInfoIter &);
    virtual void movement();

    void sendMsgToGroupMember(u32, HitSensor *, const char *);

    JMapIdInfo* mIdInfo;                    // 0x20
    s32 mMsg;                               // 0x24
    HitSensor* mSensor;                     // 0x28
    const char* mSensorName;                // 0x2C
    char mGroupName[GROUP_NAME_LEN];        // 0x30
};
