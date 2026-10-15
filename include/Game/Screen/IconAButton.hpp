#pragma once

#include "Game/Screen/LayoutActor.hpp"

class IconAButton : public LayoutActor {
public:
    IconAButton(bool, bool);

    virtual void init(const JMapInfoIter&);
    virtual void control();

    void setFollowActorPane(LayoutActor*, const char*);
    bool isOpen();
    void open();
    void openWithTalk();
    void openWithRead();
    void openWithoutMessage();
    void term();
    void exeOpen();
    void exeWait();
    void exeTerm();
    void updateFollowPos();

    /* 0x2C */ TVec2f mFollowPos;
    /* 0x30 */ LayoutActor* mFollowActor;
    /* 0x34 */ char mFollowPaneName[24];
};
