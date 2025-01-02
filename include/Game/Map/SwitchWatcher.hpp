#pragma once

#include "NameObj/NameObj.hpp"

class StageSwitchCtrl;

class SwitchEventListener {
public:
    inline SwitchEventListener() {}

    virtual void refresh(bool isOnEvent);
    virtual void listenSwitchOnEvent() = 0;
    virtual void listenSwitchOffEvent() = 0;
};

class SwitchWatcher : public NameObj {
public:
    SwitchWatcher(const StageSwitchCtrl *);

    virtual ~SwitchWatcher();
    virtual void movement();

    void checkSwitch(SwitchEventListener *, u32, bool);
    bool isSameSwitch(const StageSwitchCtrl *) const NO_INLINE;
    void addSwitchListener(SwitchEventListener *, u32);

    u32 mCheck;                                     // 0x14
    const StageSwitchCtrl* mSwitchCtrl;             // 0x18
    SwitchEventListener* mListener_A;               // 0x1C
    SwitchEventListener* mListener_B;               // 0x20
    SwitchEventListener* mListener_Appear;          // 0x24
};

class SwitchWatcherHolder : public NameObj {
public:
    SwitchWatcherHolder();

    virtual ~SwitchWatcherHolder();
    virtual void movement();

    void joinSwitchEventListenerA(const StageSwitchCtrl *, SwitchEventListener *);
    void joinSwitchEventListenerB(const StageSwitchCtrl *, SwitchEventListener *);
    void joinSwitchEventListenerAppear(const StageSwitchCtrl *, SwitchEventListener *);
    SwitchWatcher* findSwitchWatcher(const StageSwitchCtrl *);
    void joinSwitchEventListener(const StageSwitchCtrl *, u32, SwitchEventListener *);
    void addSwitchWatcher(SwitchWatcher *);

    SwitchWatcher* mWatchers[0x100];        // 0x14
    s32 mWatcherCount;                      // 0x414
};

namespace MR {
    SwitchWatcherHolder* getSwitchWatcherHolder();
    void requestMovementOnSwitchWatcher();
};
