#pragma once

#include "Game/NameObj/NameObj.hpp"
#include "Game/Util/Array.hpp"
#include "Game/Util/JMapInfo.hpp"
#include <JSystem/JGeometry/TMatrix.hpp>

class AreaForm;
class StageSwitchCtrl;

class AreaObj : public NameObj {
public:
    AreaObj(const char*);
    AreaObj(int, const char*);

    virtual void init(const JMapInfoIter&);

    virtual bool isInVolume(const TVec3f&) const;

    virtual s32 getAreaPriority() const {
        return mPriority;
    }

    virtual const char* getManagerName() const {
        return mName;
    }

    void initForm(const JMapInfoIter& rIter);

    void onSwitchA();
    void offSwitchA();
    bool isOnSwitchA() const;
    bool isOnSwitchB() const;
    bool isValidSwitchA() const;
    bool isValidSwitchB() const;
    bool isNotHemisphere() const;
    void setFollowMtx(const TPos3f*);
    TPos3f* getFollowMtx() const;

    void validate() {
        mIsValid = true;
    }

    void invalidate() {
        mIsValid = false;
    }

    bool isValid() const {
        return mIsValid && _1D;
    }

    template < typename T >
    T* getForm() const {
        return static_cast< T* >(mForm);
    }

    /* 0x14 */ AreaForm* mForm;
    /* 0x18 */ int mFormType;
    /* 0x1C */ bool mIsValid;
    /* 0x1D */ bool _1D;
    /* 0x20 */ s32 mObjArg0;
    /* 0x24 */ s32 mObjArg1;
    /* 0x28 */ s32 mObjArg2;
    /* 0x2C */ s32 mObjArg3;
    /* 0x30 */ s32 mObjArg4;
    /* 0x34 */ s32 mObjArg5;
    /* 0x38 */ s32 mObjArg6;
    /* 0x3C */ s32 mObjArg7;
    /* 0x40 */ s32 mPriority;
    /* 0x44 */ StageSwitchCtrl* mSwitchCtrl;
};

class AreaObjMgr : public NameObj {
public:
    AreaObjMgr(s32, const char*);

    void entry(AreaObj*);
    AreaObj* find_in(const TVec3f&) const;
    void requestMovementOnAll();

    AreaObj* getAreaObj(int index) {
        return mArray[index];
    }

    s32 getNumAreaObj() const {
        return mArray.size();
    }

    /* 0x14 */ MR::Vector< MR::AssignableArray< AreaObj* > > mArray;
    /* 0x20 */ s32 _20;
};
