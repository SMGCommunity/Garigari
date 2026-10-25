#include "Game/LiveActor/LiveActor.hpp"
#include "Game/Util/JMapInfo.hpp"
#include <JSystem/JGeometry/TMatrix.hpp>

class BreakModel;
class DemoObj;
class ProjmapEffectMtxSetter;

class AttackRock : public LiveActor {
public:
    AttackRock(const char* pName);

    virtual void init(const JMapInfoIter& rIter);
    virtual void makeActorAppeared();
    virtual void makeActorDead();
    virtual void control();
    virtual void calcAndSetBaseMtx();
    virtual void attackSensor(HitSensor* pSender, HitSensor* pReceiver);
    virtual bool receiveMsgPlayerAttack(u32 msg, HitSensor* pSender, HitSensor* pReceiver);
    virtual bool receiveOtherMsg(u32 msg, HitSensor* pSender, HitSensor* pReceiver);

    f32 getUnkf32();
    bool innerOrOuter();
    void setBreak();

    void exeFall();
    void exeWait();
    void exeFloat();
    void exeAttack();
    void exeBreak();

    bool isValidFollow(s32) const;

    /* 0x90 */ TMtx34f _90;
    /* 0xC0 */ TPos3f _C0;
    /* 0xF0 */ TQuat4f _F0;
    /* 0x100 */ TQuat4f _100;
    /* 0x110 */ BreakModel* mBreakModel;
    /* 0x114 */ DemoObj* mDemoObj;
    /* 0x118 */ ProjmapEffectMtxSetter* _118;
    /* 0x11C */ void* _11C;
    /* 0x120 */ void* _120;
    /* 0x124 */ s32 mFightNo;
    /* 0x128 */ bool _128;
};
