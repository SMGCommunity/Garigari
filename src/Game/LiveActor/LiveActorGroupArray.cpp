#include "LiveActor/LiveActorGroupArray.hpp"
#include "LiveActor/LiveActor.hpp"
#include "LiveActor/HitSensor.hpp"
#include "Util.hpp"
#include "Util/JMapIdInfo.hpp"
#include <cstdio>

namespace {
    struct MatchGroupId {
        ALWAYS_INLINE bool operator()(MsgSharedGroup* group, const JMapIdInfo& id) const {
            bool matches = false;
            if (group->mIdInfo->_0 == id._0 && group->mIdInfo->mZoneID == id.mZoneID)
                matches = true;
            return matches;
        }
    };
    struct ContainsActor {
        ALWAYS_INLINE bool operator()(MsgSharedGroup* group, const LiveActor* actor) const {
            for (s32 i = 0; i < group->mObjectCount; ++i)
                if (group->getActor(i) == actor)
                    return true;
            return false;
        }
    };
    template<typename Operation, typename Argument>
    struct BoundGroupPredicate {
        Operation operation;
        Argument argument;
        BoundGroupPredicate(Operation op, Argument arg) : operation(op), argument(arg) {}
        ALWAYS_INLINE bool operator()(MsgSharedGroup* group) const { return operation(group, argument); }
    };
    template<typename Predicate>
    ALWAYS_INLINE inline MsgSharedGroup* const* findMatchingGroup(MsgSharedGroup* const* first, MsgSharedGroup* const* last, Predicate predicate) {
        while (first != last && !predicate(*first))
            ++first;
        return first;
    }
}

MsgSharedGroup::MsgSharedGroup(const char *pName, s32 maxActor, const JMapInfoIter &rIter) : LiveActorGroup(pName, maxActor) {
    mIdInfo = nullptr;
    mMsg = -1;
    mSensor = nullptr;
    mSensorName = nullptr;
    MR::copyString(mGroupName, pName, GROUP_NAME_LEN);
    setName(mGroupName);

    JMapIdInfo* id = new JMapIdInfo;
    if (id) {
        const JMapIdInfo value = MR::createJMapIdInfoFromGroupId(rIter);
        id->_0 = value._0;
        id->mZoneID = value.mZoneID;
    }
    mIdInfo = id;
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

MsgSharedGroup* LiveActorGroupArray::findGroup(const JMapInfoIter& iter) const {
    MsgSharedGroup* const* current = findMatchingGroup(mGroups, mGroups + mNumUsedGroups, BoundGroupPredicate<MatchGroupId, const JMapIdInfo&>(MatchGroupId(), MR::createJMapIdInfoFromGroupId(iter)));
    return current != mGroups + mNumUsedGroups ? *current : nullptr;
}

MsgSharedGroup* LiveActorGroupArray::findGroup(const LiveActor* actor) const {
    MsgSharedGroup* const* current = findMatchingGroup(mGroups, mGroups + mNumUsedGroups, BoundGroupPredicate<ContainsActor, const LiveActor*>(ContainsActor(), actor));
    return current != mGroups + mNumUsedGroups ? *current : nullptr;
}

MsgSharedGroup::~MsgSharedGroup() {

}

LiveActorGroupArray::~LiveActorGroupArray() {
    
}
