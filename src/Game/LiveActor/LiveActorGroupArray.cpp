#include "LiveActor/LiveActorGroupArray.hpp"
#include "LiveActor/LiveActor.hpp"
#include "LiveActor/HitSensor.hpp"
#include "Util.hpp"
#include "Util/JMapIdInfo.hpp"
#include <cstdio>

// nonmatching
MsgSharedGroup::MsgSharedGroup(const char *pName, s32 maxActor, const JMapInfoIter &rIter) : LiveActorGroup(pName, maxActor) {
    mIdInfo = nullptr;
    mMsg = -1;
    mSensor = nullptr;
    mSensorName = nullptr;
    MR::copyString(mGroupName, pName, GROUP_NAME_LEN);
    setName(mGroupName);

    mIdInfo = new JMapIdInfo(MR::createJMapIdInfoFromClippingGroupId(rIter));
}

void MsgSharedGroup::init(const JMapInfoIter &rIter) {
    MR::connectToScene(this, 6, -1, -1, -1);
}

void MsgSharedGroup::movement() {
    NameObj::movement();

    if (mMsg != 0xFFFFFFFF) {
        for (s32 i = 0; i < mObjectCount; i++) {
            HitSensor* sensor = getActor(i)->getSensor(mSensorName);
            sensor->receiveMessage(mMsg, mSensor);
        }

        mMsg = -1;
    }
}

void MsgSharedGroup::sendMsgToGroupMember(u32 msg, HitSensor *pSensor, const char *pName) {
    mMsg = msg;
    mSensor = pSensor;
    mSensorName = pName;
}

LiveActorGroupArray::LiveActorGroupArray(const char *pName): NameObj(pName) {
    mNumUsedGroups = 0;
}

void LiveActorGroupArray::init(const JMapInfoIter &) {

}

MsgSharedGroup* LiveActorGroupArray::tryCreateGroupForLiveActor(LiveActor *pActor, const JMapInfoIter &rIter, const char *pGroupName, s32 max) {
    s32 groupID = -1;
    MR::getJMapInfoGroupID(rIter, &groupID);

    if (pGroupName == nullptr) {
        char buf[32];
        snprintf(buf, sizeof(buf), "group%02d", groupID);
        pGroupName = buf;
    }

    MsgSharedGroup* group = findGroup(rIter);

    if (group == nullptr) {
        group = createGroup(rIter, pGroupName, max);
    }

    group->registerActor(pActor);
    return group;
}

MsgSharedGroup* LiveActorGroupArray::getLiveActorGroup(const LiveActor *pActor) const {
    return findGroup(pActor);
}

MsgSharedGroup* LiveActorGroupArray::createGroup(const JMapInfoIter &rIter, const char *pGroupName, s32 max) {
    MsgSharedGroup* group = new MsgSharedGroup(pGroupName, max, rIter);
    group->initWithoutIter();
    s32 curGroups = mNumUsedGroups;
    mNumUsedGroups = curGroups + 1;
    mGroups[curGroups] = group;
    return group;
}

// findGroup__19LiveActorGroupArrayCFRC12JMapInfoIter
// findGroup__19LiveActorGroupArrayCFPC9LiveActor

MsgSharedGroup::~MsgSharedGroup() {

}

LiveActorGroupArray::~LiveActorGroupArray() {
    
}
