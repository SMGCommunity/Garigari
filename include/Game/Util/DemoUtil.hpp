#pragma once

class NameObj;
class LiveActor;

namespace MR {
    void registerDemoSimpleCastAll(NameObj*);
    void registerDemoSimpleCastAll(LiveActor*);
    bool tryStartDemo(LiveActor*, const char*);
    void endDemo(NameObj*, const char*);
};  // namespace MR
