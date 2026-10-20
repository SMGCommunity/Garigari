#pragma once

#include <revolution.h>

class LiveActor;
class ActorLightInfo;
class AreaLightInfo;

class ActorLightCtrl {
public:
    ActorLightCtrl(LiveActor*);

    bool operator=(const ActorLightInfo&);

    void init(int, bool);
    void update(bool);
    void loadLight() const;
    void reset();
    void copy(const ActorLightCtrl*);
    void setLightType(s32);
    void isSameLight(const ActorLightCtrl*) const;
    void getActorLight() const;
    void tryFindNewAreaLight(bool);
    void updateLightBlend();
    void resetCurrentLightInfo();
    void getTargetActorLight(const AreaLightInfo*) const;
};
