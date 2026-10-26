#include "Game/LiveActor/LiveActor.hpp"
#include "Game/Util/JMapInfo.hpp"

class MapObjConnector;

class ManholeCover : public LiveActor {
public:
    ManholeCover(const char*);

    virtual void init(const JMapInfoIter& rIter);
    virtual void initAfterPlacement();
    virtual void control();
    virtual void calcAndSetBaseMtx();
    virtual bool receiveMsgPlayerAttack(u32 msg, HitSensor* pSender, HitSensor* pReceiver);
    virtual bool receiveOtherMsg(u32 msg, HitSensor* pSender, HitSensor* pReceiver);

    void exeWait();
    void exeOpen();
    void exeRattle();

    /* 0x90 */ MapObjConnector* mConnector;
    /* 0x94 */ bool _94;
    /* 0x95 */ bool _95;
};
