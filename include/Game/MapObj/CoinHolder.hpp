#pragma once

#include "Game/LiveActor/LiveActorGroup.hpp"
#include <JSystem/JGeometry/TVec.hpp>

class Coin;

class CoinHostInfo {
public:
    /// @brief Creates a new `CoinHostInfo`.
    CoinHostInfo();

    /* 0x0 */ const NameObj* mHostObj;
    /* 0x4 */ s32 mDeclaredCoinCount;
    /* 0x8 */ s32 mNotRemnantCoinCount;
    /* 0xC */ s32 mCollectedCoinCount;
};

class CoinHolder : public DeriveActorGroup< Coin > {
public:
    /// @brief Creates a new `CoinHolder`.
    /// @param pName A pointer to the null-terminated name of the coin holder.
    CoinHolder(const char* pName);

    /// @brief Creates 32 new `Coin`s and registers them with the `CoinHolder`.
    /// @param rIter A reference to an iterator through the coin holder's `JMapInfo`. Goes unused.
    virtual void init(const JMapInfoIter& rIter);

    bool appearCoin(const NameObj*, const TVec3f&, const TVec3f&, s32, s32, s32, f32);
    bool hopCoin(const NameObj*, const TVec3f&, const TVec3f&);
    bool appearCoinPop(const NameObj*, const TVec3f&, s32);
    bool appearCoinPopToDirection(const NameObj*, const TVec3f&, const TVec3f&, s32);
    bool appearCoinAgainstGravity(const NameObj*, const TVec3f&, s32);
    bool appearCoinToVelocity(const NameObj*, const TVec3f&, const TVec3f&, s32);
    bool appearCoinCircle(const NameObj*, const TVec3f&, s32);
    CoinHostInfo* declare(const NameObj*, s32);
    s32 getDeclareRemnantCoinCount(const NameObj*) const;
    s32 getUncollectedCoinCount(const NameObj*) const;
    CoinHostInfo* findHostInfo(const NameObj*) const;

    /* 0x20 */ CoinHostInfo* mHostInfoArr;
    /* 0x24 */ s32 mHostInfoCount;
};

namespace MR {
    CoinHolder* createCoinHolder();
    CoinHolder* getCoinHolder();
    void addToCoinHolder(const NameObj*, Coin*);
};  // namespace MR
