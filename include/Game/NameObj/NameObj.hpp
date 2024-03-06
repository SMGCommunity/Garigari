#pragma once

#include <revolution.h>
#include "Game/Util.hpp"

class NameObj {
public:
    NameObj(const char *);

    virtual ~NameObj();
    virtual void init(const JMapInfoIter &rIter);
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

    const char* mName;          // _4
    vu16 mFlags;                // _8
    s16 mExecutionIdx;          // _A
    JMapLinkInfo mLinkInfo;     // _C
};

class NameObjFunction {
public:
    static void requestMovementOn(NameObj *);
    static void requsetMovementOff(NameObj *);
};