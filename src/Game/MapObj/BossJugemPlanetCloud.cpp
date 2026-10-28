#include "Game/MapObj/BossJugemPlanetCloud.hpp"
#include "Game/LiveActor/Nerve.hpp"
#include "Game/Util/ActorAnimUtil.hpp"
#include "Game/Util/ActorInitUtil.hpp"
#include "Game/Util/ActorMovementUtil.hpp"
#include "Game/Util/ActorSensorUtil.hpp"
#include "Game/Util/ActorSwitchUtil.hpp"
#include "Game/Util/LiveActorUtil.hpp"

namespace NrvBossJugemPlanetCloud {
    NEW_NERVE(BossJugemPlanetCloudNrvWhite, BossJugemPlanetCloud, White);
    NEW_NERVE(BossJugemPlanetCloudNrvWhiteToGray, BossJugemPlanetCloud, WhiteToGray);
    NEW_NERVE(BossJugemPlanetCloudNrvGray, BossJugemPlanetCloud, Gray);
    NEW_NERVE(BossJugemPlanetCloudNrvGrayToWhite, BossJugemPlanetCloud, GrayToWhite);
};  // namespace NrvBossJugemPlanetCloud

BossJugemPlanetCloud::BossJugemPlanetCloud(const char* pName) : LiveActor(pName) {
}

void BossJugemPlanetCloud::init(const JMapInfoIter& rIter) {
    MR::initActor(this, rIter, false);

    MR::startAction(this, "White");

    initNerve(GET_NERVE(BossJugemPlanetCloud, BossJugemPlanetCloudNrvWhite));

    makeActorAppeared();
}

void BossJugemPlanetCloud::attackSensor(HitSensor* pSender, HitSensor* pReceiver) {
    if (isNerve(GET_NERVE(BossJugemPlanetCloud, BossJugemPlanetCloudNrvGray))) {
        if (MR::isSensorPlayerOrRide(pReceiver) || MR::isSensorEnemy(pReceiver)) {
            MR::sendMsgEnemyAttackElectric(pReceiver, pSender);
        }
    }
}

bool BossJugemPlanetCloud::receiveMsgPlayerAttack(u32 msg, HitSensor* pSender, HitSensor* pReceiver) {
    return false;
}

void BossJugemPlanetCloud::exeWhite() {
    if (MR::isOnSwitchA(this) && MR::calcDistanceToPlayer(this) < 7000.0f) {
        setNerve(GET_NERVE(BossJugemPlanetCloud, BossJugemPlanetCloudNrvWhiteToGray));
    }
}

void BossJugemPlanetCloud::exeWhiteToGray() {
    if (MR::isFirstStep(this)) {
        MR::startAction(this, "WhiteToGray");
    }

    if (MR::isActionEnd(this)) {
        setNerve(GET_NERVE(BossJugemPlanetCloud, BossJugemPlanetCloudNrvGray));
    }
}

void BossJugemPlanetCloud::exeGray() {
    if (MR::isFirstStep(this)) {
        MR::startAction(this, "Gray");
    }

    if (!MR::isOnSwitchA(this)) {
        setNerve(GET_NERVE(BossJugemPlanetCloud, BossJugemPlanetCloudNrvGrayToWhite));
    }
}

void BossJugemPlanetCloud::exeGrayToWhite() {
    if (MR::isFirstStep(this)) {
        MR::startAction(this, "GrayToWhite");
    }

    if (MR::isActionEnd(this)) {
        kill();
    }
}
