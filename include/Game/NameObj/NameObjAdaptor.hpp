#pragma once

#include "Game/NameObj/NameObj.hpp"
#include "Game/Util.hpp"

class NameObjAdaptor : public NameObj {
public:
    NameObjAdaptor(const char *);

    virtual ~NameObjAdaptor();
    virtual void movement();
    virtual void draw() const;
    virtual void calcAnim();
    virtual void calcViewAndEntry();

    void connectToMovement(const MR::FunctorBase &);
    void connectToCalcAnim(const MR::FunctorBase &);
    void connectToDraw(const MR::FunctorBase &);

    MR::FunctorBase* mMovementFunc;     // _14
    MR::FunctorBase* mCalcAnimFunc;     // _18
    MR::FunctorBase* mCalcViewFunc;     // _1C
    MR::FunctorBase* mDrawAnimFunc;     // _20
};