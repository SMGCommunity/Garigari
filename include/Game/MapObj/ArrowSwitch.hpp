#pragma once

#include "Game/LiveActor/LiveActor.hpp"

class ArrowSwitch : public LiveActor {
public:
    enum SwitchType {
        /* 0x00 */ SwitchType_QuarterPlus,
        /* 0x01 */ SwitchType_QuarterMinus,
        /* 0x02 */ SwitchType_HalfPlus,
        /* 0x03 */ SwitchType_HalfMinus,
    };

    enum Direction {
        /* 0x00 */ Direction_Up,
        /* 0x01 */ Direction_Right,
        /* 0x02 */ Direction_Down,
        /* 0x03 */ Direction_Left,
    };

    enum ActionAfterRotate {
        /* 0x00 */ ActionAfterRotate_LockAfterRotate,
        /* 0x01 */ ActionAfterRotate_StopAfterRotate,
    };

    /// @brief Creates a new `ArrowSwitch`.
    /// @param pName A pointer to the null-terminated name of the object.
    ArrowSwitch(const char*);

    virtual void init(const JMapInfoIter&);
    virtual void control();
    virtual void calcAndSetBaseMtx();
    virtual void attackSensor(HitSensor*, HitSensor*);
    virtual bool receiveMsgPush(HitSensor*, HitSensor*);
    virtual bool receiveMsgPlayerAttack(u32, HitSensor*, HitSensor*);

    bool requestPunch(HitSensor*, HitSensor*);
    void listenOnSwitch();
    void listenOffSwitch();
    bool isPlusLimit() const;
    bool isMinusLimit() const;
    s32 getOneStep() const;

    void exeWait();
    void exeRotate();
    void exeLock();
    void exeStop();

    /* 0x90 */ f32 mRotAngle;
    /* 0x94 */ s32 mRotYTargetIndex;
    /* 0x98 */ f32 mRotSpeed;
    /* 0x9C */ s32 mSwitchType;
    /* 0xA0 */ s32 mActionAfterRotate;
    /* 0xA4 */ bool mIsRotPlus;
    /* 0xA5 */ bool _A5;
    /* 0xA6 */ bool mIsPunch;
};
