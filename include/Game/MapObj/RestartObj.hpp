#pragma once

#include "Game/LiveActor/LiveActor.hpp"

class JMapIdInfo;
class MapObjConnector;
class YoshiLockOnTarget;

/// @brief A checkpoint flag that is used to change the player's respawn point once touched or attacked by them. The respawn point and the flag itself
/// need to be in the same zone. The object attaches to nearby collision.
class RestartObj : public LiveActor {
public:
    /// @brief Creates a new `RestartObj`.
    /// @param pName A pointer to the null-terminated name of the object.
    RestartObj(const char* pName);

    virtual void init(const JMapInfoIter& rIter);
    virtual void initAfterPlacement();
    virtual void calcAndSetBaseMtx();
    virtual void updateHitSensor(HitSensor* pSensor);
    virtual void attackSensor(HitSensor* pSender, HitSensor* pReceiver);
    virtual bool receiveMsgPlayerAttack(u32 msg, HitSensor* pSender, HitSensor* pReceiver);
    virtual bool receiveOtherMsg(u32 msg, HitSensor* pSender, HitSensor* pReceiver);

    void changeTexture(bool isGet);

    void exeBefore();
    void exeGet();
    void exeAfter();
    void exeShake();
    void exeShakeAfter();

    /* 0x90 */ JMapIdInfo* mIdInfo;
    /* 0x94 */ MapObjConnector* mConnector;
    /* 0x98 */ YoshiLockOnTarget* mYoshiTarget;
};
