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

class LiveActorGroupArray : public NameObj {
public:
    LiveActorGroupArray(const char *);

    virtual ~LiveActorGroupArray();
    virtual void init(const JMapInfoIter &);

    MsgSharedGroup* tryCreateGroupForLiveActor(LiveActor *, const JMapInfoIter &, const char *, s32);
    MsgSharedGroup* getLiveActorGroup(const LiveActor *) const;
    MsgSharedGroup* createGroup(const JMapInfoIter &, const char *, s32);
    MsgSharedGroup* findGroup(const JMapInfoIter &) const;
    MsgSharedGroup* findGroup(const LiveActor *) const;

    MsgSharedGroup* mGroups[0x20];      // 0x14
    s32 mNumUsedGroups;                 // 0x94
};
