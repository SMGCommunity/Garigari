#include "Game/MapObj/CoinHolder.hpp"
#include "Game/MapObj/Coin.hpp"
#include "Game/Scene/SceneObjHolder.hpp"
#include "Game/Util/EventUtil.hpp"
#include "Game/Util/GravityUtil.hpp"
#include "Game/Util/MathUtil.hpp"
#include "Game/Util/SoundUtil.hpp"

namespace {
    const s32 sCoinNumMax = 512;
    const f32 sCoinVelVertical = 25.0f;
    const s32 sCreateCoinNum = 32;
    const f32 sRandomizeVel = 4.0f;
    const f32 sRandomizeVelAgainstGravity = 8.0f;
    const f32 sCircleVelHRatio = 0.25f;
    const f32 sCircleVelLength = 30.0f;
};  // namespace

CoinHolder::CoinHolder(const char* pName) : DeriveActorGroup< Coin >(pName, ::sCoinNumMax), mHostInfoArr(), mHostInfoCount() {
    mHostInfoArr = new CoinHostInfo[::sCoinNumMax];
}

CoinHostInfo::CoinHostInfo() : mHostObj(), mDeclaredCoinCount(), mNotRemnantCoinCount(), mCollectedCoinCount() {
}

void CoinHolder::init(const JMapInfoIter& rIter) {
    for (s32 i = 0; i < ::sCreateCoinNum; i++) {
        Coin* coin = new Coin("コイン(共用)");
        coin->initWithoutIter();
        registerActor(coin);
    }
}

bool CoinHolder::appearCoin(const NameObj* pObj, const TVec3f& rPosition, const TVec3f& rVelocity, s32 count, s32 life, s32 cannotTime,
                            f32 randomize) {
    CoinHostInfo* pInfo = findHostInfo(pObj);

    if (pInfo == nullptr) {
        return false;
    }

    bool isAppear = false;
    for (s32 i = 0; i < count; i++) {
        if (pInfo->mNotRemnantCoinCount >= pInfo->mDeclaredCoinCount) {
            break;
        }

        Coin* deadMember = getDeadMember();

        if (deadMember == nullptr) {
            break;
        }

        TVec3f velocity(rVelocity);

        if (!MR::isNearZero(randomize)) {
            MR::addRandomVector(&velocity, velocity, randomize);
        }

        deadMember->setHostInfo(pInfo);
        deadMember->appearMove(rPosition, velocity, life, cannotTime);
        isAppear = true;
    }

    if (!MR::isGalaxyDarkCometAppearInCurrentStage() && isAppear) {
        if (MR::hasME()) {
            MR::startSystemME("ME_COIN_APPEAR_S");
        } else {
            MR::startSystemSE("SE_SY_COIN_APPEAR_S");
        }
    }

    return isAppear;
}

bool CoinHolder::hopCoin(const NameObj* pObj, const TVec3f& rPosition, const TVec3f& rHopDir) {
    CoinHostInfo* pInfo = findHostInfo(pObj);

    if (pInfo->mNotRemnantCoinCount >= pInfo->mDeclaredCoinCount) {
        return false;
    }

    Coin* deadMember = getDeadMember();

    if (deadMember != nullptr) {
        deadMember->setHostInfo(pInfo);
        deadMember->appearHop(rPosition, rHopDir);
        return true;
    }

    return false;
}

bool CoinHolder::appearCoinPop(const NameObj* pObj, const TVec3f& rPosition, s32 count) {
    TVec3f gravity;
    MR::calcGravityVector(this, rPosition, &gravity, nullptr, 0);
    TVec3f velocity = -gravity * ::sCoinVelVertical;
    return appearCoin(pObj, rPosition, velocity, count, -1, -1, count == 1 ? 0.0f : ::sRandomizeVel);
}

bool CoinHolder::appearCoinPopToDirection(const NameObj* pObj, const TVec3f& rPosition, const TVec3f& rDirection, s32 count) {
    TVec3f normalizedDir;
    MR::normalize(&normalizedDir, rDirection);
    f32 randomize = count == 1 ? 0.0f : ::sRandomizeVel;
    TVec3f velocity(normalizedDir);
    velocity.scale(::sCoinVelVertical);
    return appearCoin(pObj, rPosition, velocity, count, -1, -1, randomize);
}

bool CoinHolder::appearCoinAgainstGravity(const NameObj* pObj, const TVec3f& rPosition, s32 count) {
    TVec3f gravity;
    MR::calcGravityVector(this, rPosition, &gravity, nullptr, 0);
    TVec3f velocity = -gravity * ::sCoinVelVertical;
    return appearCoin(pObj, rPosition, velocity, count, -1, -1, ::sRandomizeVelAgainstGravity);
}

bool CoinHolder::appearCoinToVelocity(const NameObj* pObj, const TVec3f& rPosition, const TVec3f& rVelocity, s32 count) {
    return appearCoin(pObj, rPosition, rVelocity, count, -1, -1, count == 1 ? 0.0f : ::sRandomizeVel);
}

bool CoinHolder::appearCoinCircle(const NameObj* pObj, const TVec3f& rPosition, s32 count) {
    if (count == 1) {
        return appearCoinPop(pObj, rPosition, count);
    }

    bool isAppear = false;
    TVec3f gravity;
    MR::calcGravityVector(this, rPosition, &gravity, nullptr, 0);
    TVec3f axis;
    MR::makeAxisVerticalZX(&axis, gravity);

    for (s32 i = 0; i < count; i++) {
        f32 angle = 360.0f / count;

        TVec3f horizontal;
        MR::rotateVecDegree(&horizontal, axis, gravity, i * angle);
        horizontal.setLength(::sCircleVelHRatio);
        TVec3f velocity(horizontal - gravity);
        velocity.setLength(::sCircleVelLength);

        isAppear |= appearCoin(pObj, rPosition, velocity, 1, -1, -1, 0.0f);
    }

    return isAppear;
}

CoinHostInfo* CoinHolder::declare(const NameObj* pObj, s32 count) {
    if (count <= 0) {
        return nullptr;
    }

    CoinHostInfo* pInfo = findHostInfo(pObj);

    if (pInfo == nullptr) {
        pInfo = &mHostInfoArr[mHostInfoCount];
        pInfo->mHostObj = pObj;
        mHostInfoCount++;
    }

    pInfo->mDeclaredCoinCount += count;
    return pInfo;
}

s32 CoinHolder::getDeclareRemnantCoinCount(const NameObj* pObj) const {
    CoinHostInfo* pInfo = findHostInfo(pObj);

    if (MR::isGalaxyDarkCometAppearInCurrentStage()) {
        return 0;
    }

    return pInfo->mDeclaredCoinCount - pInfo->mNotRemnantCoinCount;
}

s32 CoinHolder::getUncollectedCoinCount(const NameObj* pObj) const {
    CoinHostInfo* pInfo = findHostInfo(pObj);
    return pInfo->mDeclaredCoinCount - pInfo->mCollectedCoinCount;
}

CoinHostInfo* CoinHolder::findHostInfo(const NameObj* pObj) const {
    for (s32 i = 0; i < mHostInfoCount; i++) {
        if (mHostInfoArr[i].mHostObj == pObj) {
            return &mHostInfoArr[i];
        }
    }

    return nullptr;
}

CoinHolder* MR::createCoinHolder() {
    MR::createSceneObj(SceneObj_CoinRotater);
    return static_cast< CoinHolder* >(MR::createSceneObj(SceneObj_CoinHolder));
}

CoinHolder* MR::getCoinHolder() {
    return static_cast< CoinHolder* >(MR::getSceneObjHolder()->getObj(SceneObj_CoinHolder));
}

void MR::addToCoinHolder(const NameObj* pObj, Coin* pCoin) {
    MR::getCoinHolder();
    pCoin->setHostInfo(MR::getCoinHolder()->declare(pObj, 1));
}
