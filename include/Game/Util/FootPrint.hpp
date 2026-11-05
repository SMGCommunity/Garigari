#pragma once

#include "Game/NameObj/NameObj.hpp"
#include <JSystem/JGeometry/TVec.hpp>

class ResTIMG;
class JUTTexture;
class LiveActor;

class FootPrintInfo {
public:
    FootPrintInfo();

    /* 0x00 */ TVec3f mPos;
    /* 0x0C */ TVec3f _C;
    /* 0x18 */ TVec3f _18;

    /// @brief Frames left before becoming invalid. Also controls the footprint's alpha.
    /* 0x24 */ s32 mTimeLeft;

    /// @brief Invalid prints will no longer be updated nor drawn.
    /* 0x28 */ bool mIsValid;

    /* 0x29 */ bool _29;
};

class FootPrint : public NameObj {
public:
    FootPrint(const char*, s32);
    FootPrint(const char*, s32, s32);

    virtual void movement();
    virtual void draw() const;

    void setTexture(ResTIMG*);
    bool addPrint(const TVec3f&, const TVec3f&, const TVec3f&, bool);
    void clear();
    void initMember(s32, s32);
    void clearForce();
    TVec3f* getPrintPos(u32) const;
    void invalidate(u32);
    bool isValid(u32) const;

    /* 0x14 */ JUTTexture* mTexture;

    /// @brief Array of footprints.
    /* 0x18 */ FootPrintInfo* mPrints;

    /* 0x1C */ TVec3f mLastPrintPos;

    /// @brief Size of the mPrints array.
    /* 0x28 */ s32 mPrintMaxNum;

    /// @brief Amount of active footprints (counting invalid ones). Caps at mPrintMaxNum.
    /* 0x2C */ s32 mPrintNum;

    /// @brief The index used when adding a new footprint. Will wrap around and overwrite the oldest footprints.
    /* 0x30 */ s32 mRotatingPrintIndex;

    /* 0x34 */ f32 mSideOffset;
    /* 0x38 */ f32 mSideSize;
    /* 0x3C */ f32 mFrontSize;

    /// @brief The minimum distance for a new print to be registered.
    /* 0x40 */ f32 mMinDistance;

    /* 0x44 */ bool mIsCleared;
};

namespace MR {
    FootPrint* createFootPrintFromArc(const LiveActor*);
    void addFootPrint(FootPrint*, const LiveActor*, const TVec3f&, const TVec3f&, bool, f32);
    void addFootPrint(FootPrint*, const LiveActor*, const TVec3f&, bool, f32);
    void addFootPrint(FootPrint*, const LiveActor*, const char*, bool, f32);
};
