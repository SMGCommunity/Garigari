#pragma once

class LiveActor;

namespace MR {
    bool isDead(const LiveActor *);
    bool isHiddenModel(const LiveActor *);
    void showModel(LiveActor *);
};
