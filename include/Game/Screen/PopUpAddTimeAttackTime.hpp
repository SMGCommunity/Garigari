#pragma once

#include "Game/Screen/LayoutActor.hpp"

class PopUpAddTimeAttackTime : public LayoutActor {
public:
    PopUpAddTimeAttackTime(const char* pName, f32);

    virtual void init(const JMapInfoIter&);
    virtual void appear();
    virtual void control();

    void show(const wchar_t* pName);
    void setTextBoxArgNumber(s32);
    bool tryHide();
    void calcPos();

    void exeHide();
    void exeDisplay();

    /* 0x2C */ TVec2f _2C;
    /* 0x34 */ f32 _34;
};
