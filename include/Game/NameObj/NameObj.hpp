#pragma once

#include "Game/Util/JMapLinkInfo.hpp"
#include <revolution.h>

class NameObj {
public:
    NameObj(const char*);

    virtual ~NameObj();
    virtual void init(const JMapInfoIter&);
    virtual void initAfterPlacement();
    virtual void movement();
    virtual void draw() const;
    virtual void calcAnim();
    virtual void calcViewAndEntry();
    virtual void startMovement();
    virtual void endMovement();

    void initWithoutIter();
    void setName(const char*);
    void setLinkedInfo(const JMapInfoIter&);
    void executeMovement();
    void requestSuspend();
    void requestResume();
    void syncWithFlags();

    const char* getName() const {
        return mName;
    }

    /* 0x04 */ const char* mName;
    /* 0x08 */ vu16 mFlags;
    /* 0x0A */ s16 mExecutorIdx;
    /* 0x0C */ JMapLinkInfo mLinkInfo;
};

namespace NameObjFunction {
    void requestMovementOn(NameObj*);
    void requestMovementOff(NameObj*);
};  // namespace NameObjFunction
