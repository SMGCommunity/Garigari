#pragma once

#include <revolution.h>
#include "Util/JMapLinkInfo.hpp"

class NameObj {
public:
    NameObj(const char *);

    virtual ~NameObj();
    virtual void init(const JMapInfoIter &);
    virtual void initAfterPlacement();
    virtual void movement();
    virtual void draw() const;
    virtual void calcAnim();
    virtual void calcViewAndEntry();
    virtual void startMovement();
    virtual void endMovement();

    void initWithoutIter();
    void setName(const char *);
    void setLinkedInfo(const JMapInfoIter &);
    void executeMovement();
    void requestSuspend();
    void requestResume();
    void syncWithFlags();

    const char* mName;          // 0x04
    vu16 mFlags;                // 0x08
    s16 mExecutorIdx;           // 0x0A
    JMapLinkInfo mLinkInfo;     // 0x0C
};

namespace NameObjFunction {
    void requestMovementOn(NameObj *);
    void requestMovementOff(NameObj *);
};
