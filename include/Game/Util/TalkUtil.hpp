#pragma once

#include <JSystem/JGeometry/TVec.hpp>

class TalkMessageCtrl;
class LiveActor;
class JMapInfoIter;

namespace MR {
    TalkMessageCtrl* createTalkCtrlDirect(LiveActor*, const char*, const TVec3f&, MtxPtr);
    bool tryTalkForceWithoutDemoAtEnd(TalkMessageCtrl*);
}
