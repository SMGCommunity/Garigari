#include "LiveActor/LiveActorGroupArray.hpp"
#include "LiveActor/LiveActor.hpp"
#include "LiveActor/HitSensor.hpp"
#include "Util.hpp"
#include "Util/JMapIdInfo.hpp"

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
