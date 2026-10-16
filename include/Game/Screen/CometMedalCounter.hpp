#pragma once

#include "Game/Screen/LayoutActor.hpp"

class CounterLayoutAppearer;

class CometMedalCounter : public LayoutActor {
public:
    CometMedalCounter();

    virtual void init(const JMapInfoIter&);
    virtual void appear();
    virtual void control();
    virtual void forceAppear(bool);

    void disappear();

    void exeHidden();
    void exeAppear();
    void exeDisappear();
    void exeWait();
    void exeFlash();

    bool isAppearInCurrentScenario() const;
    bool isWait() const;

    /* 0x2C */ u32 _2C; // unknown type
    /* 0x30 */ CounterLayoutAppearer* mAppearer;
    /* 0x34 */ f32 _34;
    /* 0x38 */ f32 _38;
    /* 0x3C */ bool mIsCollected;
    /* 0x3C */ bool mIsHidden;
};
