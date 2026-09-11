#include "Map/SwitchWatcher.hpp"
#include "Map/StageSwitch.hpp"
#include "Scene/SceneObjHolder.hpp"
#include "Util/ObjUtil.hpp"

#define Listener_A      1
#define Listener_B      2    
#define Listener_Appear 4

SwitchWatcherHolder::SwitchWatcherHolder() : NameObj("SwitchWatcherHolder") {
    mWatcherCount = 0;
    MR::connectToScene(this, 0x19, -1, -1, -1);
}

namespace {
    struct WatcherMovement {
        void (SwitchWatcher::*method)();
        explicit WatcherMovement(void (SwitchWatcher::*value)()) : method(value) {}
        void operator()(SwitchWatcher* watcher) const { (watcher->*method)(); }
    };
    inline WatcherMovement forEachWatcher(SwitchWatcher** begin, SwitchWatcher** end, WatcherMovement operation) {
        for (; begin != end; ++begin) operation(*begin);
        return operation;
    }
}

void SwitchWatcherHolder::movement() {
    forEachWatcher(mWatchers, mWatchers + mWatcherCount, WatcherMovement(&SwitchWatcher::movement));
}

void SwitchWatcherHolder::joinSwitchEventListenerA(const StageSwitchCtrl *pCtrl, SwitchEventListener *pListener) {
    joinSwitchEventListener(pCtrl, Listener_A, pListener);
}

void SwitchWatcherHolder::joinSwitchEventListenerB(const StageSwitchCtrl *pCtrl, SwitchEventListener *pListener) {
    joinSwitchEventListener(pCtrl, Listener_B, pListener);
}

void SwitchWatcherHolder::joinSwitchEventListenerAppear(const StageSwitchCtrl *pCtrl, SwitchEventListener *pListener) {
    joinSwitchEventListener(pCtrl, Listener_Appear, pListener);
}

SwitchWatcher* SwitchWatcherHolder::findSwitchWatcher(const StageSwitchCtrl *pCtrl) {
    for (SwitchWatcher** cur = &mWatchers[0]; cur != &mWatchers[mWatcherCount]; cur++) {
        if ((*cur)->isSameSwitch(pCtrl)) {
            return *cur;
        }
    }

    return nullptr;
}

void SwitchWatcherHolder::joinSwitchEventListener(const StageSwitchCtrl *pCtrl, u32 type, SwitchEventListener *pEventListener) {
    SwitchWatcher* sw = findSwitchWatcher(pCtrl);

    if (sw == nullptr) {
        sw = new SwitchWatcher(pCtrl);
        addSwitchWatcher(sw);
    }

    sw->addSwitchListener(pEventListener, type);
}

void SwitchWatcherHolder::addSwitchWatcher(SwitchWatcher *pWatcher) {
    s32 count = mWatcherCount++;
    mWatchers[count] = pWatcher;
}

namespace MR {
    SwitchWatcherHolder* getSwitchWatcherHolder() {
        return MR::getSceneObj<SwitchWatcherHolder*>(SceneObj_SwitchWatcherHolder);
    }

    void requestMovementOnSwitchWatcher() {
        MR::requestMovementOn(getSwitchWatcherHolder());
    }
};

SwitchWatcherHolder::~SwitchWatcherHolder() {
    
}
